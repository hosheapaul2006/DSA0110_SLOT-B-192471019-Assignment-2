# DSA0110 - Assignment 2 (CO2)

**Student:** D Hoshea Paul  
**Register number:** 192471019  
**Course / slot:** DSA0110 / B  
**Language:** C++17 exclusively for assignment solutions and tests

Repository: [DSA0110 Assignment 2](https://github.com/hosheapaul2006/DSA0110_SLOT-B-192471019-Assignment-2)

Problem statement: [original 15-page assignment PDF](Reference/ASSIGNMENT%202.pdf).
Report: [PDF](Report/Assignment2_Report.pdf) | [Markdown](Report/Assignment2_Report.md).
Review [the full checklist](ASSIGNMENT_CHECKLIST.md), [viva preparation](VIVA_PREPARATION.md)
and [submission materials/status](SUBMISSION_PREPARATION.md).

## Environment

Actual local compiler: `g++.exe (MinGW-W64 x86_64-ucrt-posix-seh, built by Brecht Sanders, r3) 14.2.0`.
Full `g++ --version` output is in [Reference/compiler_version.txt](Reference/compiler_version.txt).
Tests ran on Windows with portable GCC from the official [WinLibs distribution](https://winlibs.com/).
The existing Dev-C++ GCC could not start; no system compiler or persistent PATH was changed.
Programiz was used separately for genuine online executions/screenshots. Its GUI does not
establish the local compiler version or reproduce the explicitly flagged benchmark builds.

## Compile and run

From the repository root, with a working g++ on PATH:

```powershell
New-Item -ItemType Directory -Force build | Out-Null
g++ --version
g++ -std=c++17 -Wall -Wextra -Wpedantic -O0 Task01/main.cpp -o build/Task01.exe
.\build\Task01.exe
```

Repeat with the source and executable names below. All supplied inputs are embedded
in the corresponding C++ main functions; no stdin or external input file is required.
The exact tested absolute commands, source hashes, UTC timestamps and exit codes
are preserved in each task's `outputs/*_verification.json`.

| Task | Console demonstration | Additional valid sources |
|---|---|---|
| Q1 | Task01/main.cpp | complete_code.cpp, predict_output.cpp, validation.cpp |
| Q2 | Task02/main.cpp | validation.cpp |
| Q3 | Task03/main.cpp | validation.cpp |
| Q4 | Task04/main.cpp | validation.cpp, baseline_growth.cpp |
| Q5 | Task05/main.cpp | complete_code.cpp, predict_output.cpp, validation.cpp |
| Q6 | Task06/main.cpp | complete_code.cpp, validation.cpp, benchmark.cpp |
| Q7 | Task07/programiz_demo.cpp | original.cpp, redesigned.cpp, validation_demo.cpp, benchmark.cpp |

Q7 original.cpp/redesigned.cpp use the adjacent headers; g++ finds quoted local
includes automatically. programiz_demo.cpp is self-contained for the online editor.
Console demonstrations show coursework output. Separate validation programs print
test labels; tables and JSON record verification outcomes.

The portable compiler used in this workspace can be invoked in PowerShell as:

```powershell
$cxx = 'C:\Projects\SLOT B\.tools\mingw64\bin\g++.exe'
$env:PATH = (Split-Path $cxx) + ';' + $env:PATH
& $cxx -std=c++17 -Wall -Wextra -Wpedantic -O0 Task04/main.cpp -o build/Task04.exe
.\build\Task04.exe
```

This PATH change applies only to that shell. The downloaded toolchain and compiled
executables are not repository deliverables.

For each benchmark task (Task06 and Task07), compile/run separately:

```powershell
g++ -std=c++17 -Wall -Wextra -Wpedantic -O0 Task06/benchmark.cpp -o build/Q6_O0.exe
.\build\Q6_O0.exe
g++ -std=c++17 -Wall -Wextra -Wpedantic -O2 Task06/benchmark.cpp -o build/Q6_O2.exe
.\build\Q6_O2.exe
g++ -std=c++17 -Wall -Wextra -Wpedantic -O0 Task07/benchmark.cpp -o build/Q7_O0.exe
.\build\Q7_O0.exe
g++ -std=c++17 -Wall -Wextra -Wpedantic -O2 Task07/benchmark.cpp -o build/Q7_O2.exe
.\build\Q7_O2.exe
```

Expected diagnostic examples:

```powershell
g++ -std=c++17 -Wall -Wextra -Wpedantic -Wreturn-local-addr -O0 Task02/unsafe_local.cpp -o build/unsafe_local.exe
# Compile only. Never execute the unsafe example.
g++ -std=c++17 -Wall -Wextra -Wpedantic -O0 Task03/ambiguity.cpp -o build/ambiguity.exe
# Expected compilation failure: two ambiguous calls.
```

Optional orchestration (Python is only a build/test runner, not an assignment solution):

```powershell
$env:CXX = 'C:\Projects\SLOT B\.tools\mingw64\bin\g++.exe' # or your actual g++.exe
python tools/run_all.py
```

Rerunning replaces current measured output files with new genuine results and may
dirty the working tree; it never edits the original predictions. Reported medians
describe the committed dataset; recompute the summaries if publishing a new dataset.

## Contents and outcomes

```text
Reference/          Original PDF, supplied exercise text, compiler, prediction history
Task01..Task06/     main.cpp, validation.cpp, supplied exercises where applicable
  outputs/         Actual stdout/stderr, predictions, diagnostics, verification JSON
  screenshots/     Genuine current Programiz viewport/full-page captures
Task07/            Original and circular history, validation, benchmark, comparison
Report/            Assignment2_Report.md and Assignment2_Report.pdf
tools/             Reproduction and documentation orchestration
```

| Task | Summary | Verified local outcome |
|---|---|---|
| Q1 | Value/reference/pointer fees, defaults and reference return | Correct caller mutations; supplied prediction/TODO matched |
| Q2 | Highest-mark interfaces and dangling references | Safe examples passed; real warning captured; unsafe program not run |
| Q3 | Ambiguity, defaults, grams/kg/Parcel overloads | Genuine errors captured; six precommitted selections matched |
| Q4 | Private ten-entry savings history | Correct last-ten order and rejected-operation behaviour |
| Q5 | Static seat counters and arrays | Capacity/waiting/persistence checked; supplied prediction/TODO matched |
| Q6 | Friends, members, getters and inline | Boundary/TODO checks passed; five trials at both flags |
| Q7 | Measured shifting-to-ring redesign, sections A-F | Every oracle snapshot matched; capacity 1000 timing objective achieved |

24 valid C++ source programs were compiled and executed in 26 build/run configurations.
Two separate diagnostic-only sources were compiled for their expected warning/error;
the dangling-reference example was not executed. 12 presentation/supplied programs
also ran on [Programiz](https://www.programiz.com/cpp-programming/online-compiler/),
with 19 current screenshots. Eight earlier screenshots are retained with original
execution records for provenance, not used as current report illustrations.

Q6 inline/ordinary medians were 45.0479/44.9704ms at -O0 and 10.2862/10.3684ms at -O2,
for ten million calls to each of two operations. This does not show a meaningful
keyword-only speed advantage. Q7 at capacity 1000 measured 221.2820 vs0.8666ms
(-O0,255.35x) and 15.7721 vs0.2296ms (-O2,68.69x) for 100000 retention updates.
See the task benchmark methodology and raw trials; these are local observations.

## Verification and outstanding items

Each valid source compiled with C++17 warnings enabled; all unexpected diagnostics
were resolved. C++ checks exercise ordinary, boundary and invalid cases. Supplied
expected outputs and applicable predictions were compared character by character,
normalizing only Windows newline encoding. Programiz outputs were separately read
from the actual result pane and compared with local stdout. Original predictions
and their commit order are preserved in [the prediction history](Reference/PREDICTION_HISTORY.md).

The report contains a faculty-verifiable evidence trail. Completion is limited by
Classroom sign-in/submission and faculty acceptance items. The source/evidence
commits have been pushed to the existing main after the user explicitly approved
handling GitHub; the final report/documentation push is part of final verification. The current
repository name differs from the PDF's `DSA01-192471019-Assignment2` convention and
is intentionally preserved as requested. The PDF deadline was 31 October 2026;
actual work is dated 10 November 2026. Faculty acceptance of the naming/deadline
discrepancies and the student's individual execution remain pending.

Optional report regeneration uses reportlab, pypdf and Pillow with `python tools/build_report.py`; the C++ programs use only the standard library.
