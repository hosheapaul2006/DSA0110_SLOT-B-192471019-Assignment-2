"""Build/run orchestration only. All assignment solutions and tests are C++17."""
import argparse
import datetime
import hashlib
import json
import os
from pathlib import Path
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[1]
DEFAULT_CXX = ROOT.parent / '.tools/mingw64/bin/g++.exe'

def execute(task, source, optimize='-O0', diagnostic=None, prediction=None, extra=None):
    folder = ROOT / task
    output = folder / 'outputs'
    output.mkdir(parents=True, exist_ok=True)
    build = ROOT / 'build' / task
    build.mkdir(parents=True, exist_ok=True)
    stem = Path(source).stem + (('_' + optimize[1:]) if source == 'benchmark.cpp' else '')
    cxx = Path(os.environ.get('CXX', str(DEFAULT_CXX)))
    env = os.environ.copy()
    env['PATH'] = str(cxx.parent) + os.pathsep + env.get('PATH', '')
    exe = build / (stem + '.exe')
    command = [str(cxx), '-std=c++17', '-Wall', '-Wextra', '-Wpedantic', optimize, str(folder/source), '-o', str(exe)]
    if diagnostic == 'warning':
        command += ['-Wreturn-local-addr']
    if extra:
        command += extra
    result = subprocess.run(command, capture_output=True, env=env, timeout=180)
    (output/(stem + '_compiler.txt')).write_bytes(result.stdout + result.stderr)
    record = {'source': task+'/'+source, 'sha256': hashlib.sha256((folder/source).read_bytes()).hexdigest(),
              'timestamp_utc': datetime.datetime.now(datetime.timezone.utc).isoformat(),
              'compile_command': command, 'compile_exit': result.returncode,
              'optimization': optimize, 'expected_diagnostic': diagnostic}
    if diagnostic == 'error':
        assert result.returncode != 0 and b'ambiguous' in result.stderr.lower(), result.stderr.decode(errors='replace')
        record['status'] = 'PASS: expected ambiguity diagnostic'
    elif diagnostic == 'warning':
        assert result.returncode == 0 and b'warning:' in result.stderr and b'local' in result.stderr
        record['status'] = 'PASS: warning captured; unsafe program NOT executed'
    else:
        assert result.returncode == 0, result.stderr.decode(errors='replace')
        assert not result.stderr, result.stderr.decode(errors='replace')
        run = subprocess.run([str(exe)], capture_output=True, env=env, timeout=180)
        (output/(stem + '_actual.txt')).write_bytes(run.stdout)
        (output/(stem + '_stderr.txt')).write_bytes(run.stderr)
        assert run.returncode == 0 and not run.stderr, (run.returncode,run.stderr)
        record.update(run_command=[str(exe)], run_exit=run.returncode)
        if prediction:
            # C++ text streams use CRLF on Windows; compare characters after
            # newline decoding, preserving every other space and character.
            expected = (folder/prediction).read_text(encoding='utf-8')
            actual = run.stdout.decode('utf-8').replace('\r\n','\n')
            assert actual == expected, (repr(expected), repr(actual))
            record['prediction_comparison'] = 'PASS: identical characters with platform newline normalization only'
        record['status'] = 'PASS'
    (output/(stem + '_verification.json')).write_text(json.dumps(record, indent=2)+'\n',encoding='utf-8')
    print(task, source, optimize, record['status'])
    return record

if __name__ == '__main__':
    parser=argparse.ArgumentParser()
    parser.add_argument('task'); parser.add_argument('source')
    parser.add_argument('--opt',default='-O0'); parser.add_argument('--diagnostic', choices=['error','warning'])
    parser.add_argument('--prediction')
    args=parser.parse_args()
    execute(args.task,args.source,args.opt,args.diagnostic,args.prediction)
