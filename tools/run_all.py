"""Reproduce local builds/tests. Does not change committed prediction files."""
from verify import ROOT, execute
for folder in sorted(ROOT.glob('Task[0-9][0-9]')):
    for source in sorted(folder.glob('*.cpp')):
        diagnostic = 'warning' if source.name=='unsafe_local.cpp' else 'error' if source.name=='ambiguity.cpp' else None
        prediction=None
        if source.name=='predict_output.cpp': prediction='outputs/predicted_output.txt'
        elif source.name=='complete_code.cpp': prediction='outputs/complete_expected.txt'
        elif folder.name=='Task03' and source.name=='validation.cpp': prediction='outputs/predicted_output.txt'
        for opt in (['-O0','-O2'] if source.name=='benchmark.cpp' else ['-O0']):
            execute(folder.name,source.name,opt,diagnostic,prediction)
