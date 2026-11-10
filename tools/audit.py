"""Read-only evidence audit; writes a fresh audit result, never predictions."""
from pathlib import Path
import datetime
import hashlib
import json
import re
import subprocess

ROOT=Path(__file__).resolve().parents[1]
def git(*args):
    return subprocess.check_output(['git',*args],cwd=ROOT,text=True).strip()
def canonical(data): return data.replace(b'\r\n',b'\n')

def audit():
    checks=[]
    def check(name,condition,detail):
        checks.append({'requirement':name,'status':'PASS' if condition else 'FAIL','evidence':detail})
        if not condition: raise RuntimeError(name+': '+detail)
    records={}
    for p in ROOT.glob('Task*/outputs/*_verification.json'):
        d=json.loads(p.read_text()); records[(d['source'],d['optimization'])]=d
    sources=sorted(ROOT.glob('Task*/*.cpp'))
    valid=[]
    for p in sources:
        rel=p.relative_to(ROOT).as_posix()
        record=records.get((rel,'-O0'))
        check(rel+' compilation record',record is not None,rel+' has a verification JSON')
        check(rel+' source unchanged',hashlib.sha256(p.read_bytes()).hexdigest()==record['sha256'],'SHA256 matches actual compiled source')
        if record['expected_diagnostic']:
            check(rel+' expected diagnostic',record['status'].startswith('PASS'),record['status'])
        else:
            valid.append(rel)
            check(rel+' executed',record.get('run_exit')==0 and record['status']=='PASS','Successful exit, no unexpected warnings/stderr')
    predictions=[('c2a6ade','Task01/outputs/predicted_output.txt','Task01/outputs/predict_output_verification.json'),
                 ('c9dd5c2','Task03/outputs/predicted_output.txt','Task03/outputs/initial_execution/main_verification.json'),
                 ('cbc5040','Task05/outputs/predicted_output.txt','Task05/outputs/predict_output_verification.json'),
                 ('a8e1a25','Task07/outputs/redesign_prediction.md','Task07/outputs/benchmark_O0_verification.json')]
    for commit,path,recordPath in predictions:
        original=subprocess.check_output(['git','show',commit+':'+path],cwd=ROOT)
        check(path+' immutable',canonical(original)==canonical((ROOT/path).read_bytes()),'Matches pre-execution commit '+commit)
        before=int(git('show','-s','--format=%ct',commit))
        after=datetime.datetime.fromisoformat(json.loads((ROOT/recordPath).read_text())['timestamp_utc']).timestamp()
        check(path+' chronological order',before<=after,commit+' precedes recorded execution')
        check(path+' commit ancestor',subprocess.run(['git','merge-base','--is-ancestor',commit,'HEAD'],cwd=ROOT).returncode==0,'Prediction commit is an ancestor of current work')
    for task in [1,5]:
        check(f'Q{task} supplied prediction preserved',canonical((ROOT/f'Task{task:02}/predict_output.cpp').read_bytes())==canonical((ROOT/f'Reference/Q{task}_prediction_original.txt').read_bytes()),'Source text matches PDF extraction')
    for task in [1,5,6]:
        original=(ROOT/f'Reference/Q{task}_TODO_original.txt').read_text()
        completed=(ROOT/f'Task{task:02}/complete_code.cpp').read_text()
        if task==1:
            expected=re.sub(r'    // TODO 1:.*?reference\)\s*','    fee -= fee * percent / 100;\n',original,flags=re.S)
        elif task==5:
            expected=re.sub(r'        // TODO 1:[^\n]*(?:\n        //[^\n]*)*\n[ \t]*\n','        if (issued < CAPACITY) seat = ++issued;\n',original,flags=re.S)
            expected=re.sub(r'        // TODO 2:[^\n]*\n[ \t]*\n','        return issued;\n',expected)
        else:
            expected=re.sub(r'    // TODO 1:.*?//   the two times in minutes\s*','    int delta = (a.h * 60 + a.m) - (b.h * 60 + b.m);\n    return delta < 0 ? -delta : delta;\n',original,flags=re.S)
            expected=re.sub(r'    // TODO 2: Return true if a is earlier in the day than b\s*','    return a.h * 60 + a.m < b.h * 60 + b.m;\n',expected)
        check(f'Q{task} TODO-only editing',expected==completed,'Only TODO regions replaced; surrounding supplied text retained')
    online=list(ROOT.glob('Task*/outputs/*_programiz.json'))
    for p in online:
        d=json.loads(p.read_text()); src=ROOT/d['source'];stem=src.stem
        check(d['source']+' online provenance',hashlib.sha256(src.read_bytes()).hexdigest()==d['sha256'],'Online source hash matches current file')
        actual=(src.parent/'outputs'/f'{stem}_actual.txt').read_text()
        observed=(src.parent/'outputs'/f'{stem}_programiz.txt').read_text()
        check(d['source']+' online output',observed.startswith(actual),'Actual Programiz result begins with all expected stdout characters')
        check(d['source']+' screenshot',(src.parent/'screenshots'/f'{stem}_programiz.jpg').is_file(),'Genuine browser capture saved with actual execution')
    tracked=git('ls-files').splitlines()
    check('no binaries or secrets tracked',not any(p.endswith(('.exe','.o','.obj','.zip')) or p.startswith('build/') for p in tracked),'git ls-files contains no build products/toolchain archives')
    for task in range(1,8):
        check(f'Q{task} documentation',all((ROOT/f'Task{task:02}'/n).is_file() for n in ['explanation.md','test_cases.md']),'Explanation and executed test table exist')
    result={'timestamp_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'valid_source_count':len(valid),
            'build_run_configurations':sum(d.get('run_exit')==0 for d in records.values()),
            'diagnostic_only_sources':2,'programiz_programs':len(online),
            'current_screenshot_count':len(list(ROOT.glob('Task*/screenshots/*.jpg'))),
            'historical_screenshot_count':len(list(ROOT.glob('Task*/outputs/initial_execution/screenshots/*.jpg'))),
            'checks':checks}
    (ROOT/'Reference/final_audit.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf-8')
    print(json.dumps({k:v for k,v in result.items() if k!='checks'},indent=2))
    print('Evidence audit checks:',len(checks),'PASS')
    return result
if __name__=='__main__': audit()
