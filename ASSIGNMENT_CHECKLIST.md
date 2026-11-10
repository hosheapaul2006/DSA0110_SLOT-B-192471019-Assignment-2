# Assignment 2 requirement audit

D Hoshea Paul |192471019 |DSA0110 |Slot B

Source: Reference/ASSIGNMENT 2.pdf, all15 pages. PASS means verified evidence; PENDING means unfinished or requiring the student/faculty. Nothing is marked complete from an unobserved execution.

| Requirement | Status | Evidence / remaining action |
|---|---|---|
| Q1 three fee passing mechanisms and caller-side predictions | PASS | Task01/main.cpp; outputs/stored_fee_predictions.md; initial prediction commit c2a6ade |
| Q1 merit10%,sports15%,single-parent25%,sequential design | PASS | Task01/explanation.md; main_actual.txt; validation_actual.txt |
| Q1 supplied exact prediction before execution; defaults/reference return explained | PASS | Task01/predict_output.cpp; predicted_output.txt; predict_output_verification.json; comparison.md |
| Q1 TODO1 completed, surrounding source preserved | PASS | Task01/complete_code.cpp; Reference/Q1_TODO_original.txt; final_audit.json |
| Q1 return-value alternative, const reference, long long vs Student time/space | PASS | Task01/main.cpp; explanation.md; measured sizeof values in actual output |
| Q2 highest reference, +2 moderation and assignment to function call | PASS | Task02/main.cpp; validation.cpp; actual outputs |
| Q2 copy and const-reference differences; index/pointer alternatives | PASS | Task02/main.cpp; explanation.md; executed checks |
| Q2 unsafe local-reference warning, without executing unsafe use | PASS | Task02/unsafe_local.cpp; outputs/unsafe_local_compiler.txt; verification.json confirms NOT executed |
| Q2 growing vector invalidation and justified response | PASS | Forced reserve growth test, saved-index reacquisition and recomputed maximum; explanation.md |
| Q2 O(n) search/O(1) auxiliary space and safety comparison | PASS | Task02/explanation.md |
| Q3 actual ambiguous overload diagnostics | PASS | Task03/ambiguity.cpp; outputs/ambiguity_compiler.txt |
| Q3 unambiguous documented int-grams,double-kg,Parcel interfaces/defaults | PASS | Task03/main.cpp; six checked selections |
| Q3 six predicted selections including charge(2),charge(2.0f) | PASS | Prediction commit c9dd5c2; validation.cpp; immutable predicted_output.txt; original execution archive |
| Q3 match/promotion/conversion, right-side defaults, compile-time resolution | PASS | Task03/explanation.md |
| Q3 Parcel/template alternatives, space/runtime and new-option comparison | PASS | Executed parcelCharge/templateCharge calls; Task03/explanation.md |
| Q4 private account,balance,Transaction[10],count and public operations | PASS | Task04/main.cpp |
| Q4 definitions inside/outside class using scope resolution | PASS | Task04/main.cpp; explanation.md |
| Q4 deposits/withdrawals/rejections,overflow and more than10 transactions | PASS | Task04/test_cases.md; validation_actual.txt |
| Q4 exact last10 chronological order and 11th-update cost | PASS | Complete statement string comparison; nine shifts at11th;18 at12th |
| Q4 capacity50 design and array/ring/deque complexity/pseudocode | PASS | Task04/explanation.md; baseline_growth_actual.txt |
| Q5 student-derived static class design and out-of-class definition | PASS | Task05/main.cpp; explanation.md |
| Q5 static method limitations,this,array construction,capacity/waiting | PASS | Task05/main.cpp; validation output; explanation.md |
| Q5 array larger than capacity and function called twice/static persistence | PASS | Task05/main.cpp; main_actual.txt; test_cases.md |
| Q5 Token exact prediction before execution and constructor explanation | PASS | Commit cbc5040; predict_output.cpp; prediction_reasoning.md; exact comparison |
| Q5 TODO1 and TODO2 preserved/completed; expected output matched | PASS | complete_code.cpp; Reference/Q5_TODO_original.txt; final_audit.json |
| Q5 global/TicketOffice alternatives and multiple-bus,time/memory analysis | PASS | Executed alternative designs in main.cpp; explanation.md |
| Q6 private Time,friend/member/getter comparison and encapsulation | PASS | Task06/main.cpp; explanation.md |
| Q6 both supplied TODOs complete and exact205 false verified | PASS | Task06/complete_code.cpp; complete_code_verification.json; TODO preservation audit |
| Q6 morning/afternoon,equal,noon,midnight and invalid boundaries | PASS | Six hand-calculated cases plus invalid fields; test_cases.md |
| Q6 ten million calls with/without inline at-O0 and-O2 | PASS | benchmark.cpp; five-trial raw CSV outputs and verification JSON at both flags |
| Q6 benchmark observable checksums,method/limitations and deployment decision | PASS | benchmark_results.md; explanation.md; no per-iteration IO/volatile/allocation |
| Q7 A diagnose original limitation with Q1-Q6 evidence | PASS | Task04 measured growth baseline; Task07/explanation.md sectionA |
| Q7 B measurable objective established before redesign | PASS | Task07/outputs/redesign_prediction.md, pre-implementation commit a8e1a25 |
| Q7 C coherent class redesign,C++ features,memory,pseudocode | PASS | history.hpp; explanation.md sectionC; manual circular indexing |
| Q7 D predicted improvement before implementation/benchmarking | PASS | Immutable prediction commit a8e1a25; chronology audited |
| Q7 E identical tests and comparable measurements | PASS | 10000 snapshots/design match deque oracle; identical Transaction streams; both flags/five trials |
| Q7 F objective evaluation,new costs,where original preferable | PASS | comparison.md; explanation.md sectionF; actual medians and limits |
| All valid programs compiled/executed with C++17 warnings | PASS | 24 sources/26 configurations; Reference/final_audit.json; no unexpected warnings |
| Normal,boundary/negative cases and expected/actual/status tables | PASS | Each TaskNN/test_cases.md; executed C++ checks and output records |
| Supplied prediction programs retained; TODO-only editing | PASS | Reference originals; 139 evidence audit checks; source/commit hashes |
| Genuine Programiz execution/screenshots for main and supplied exercises | PASS | 12 runs;19 current JPEG captures; source hashes and actual result-pane text |
| Compiler version,flags,commands,source hashes and real timestamps | PASS | Reference/compiler_version.txt; README; outputs/*_verification.json |
| Progressive commits,at least one per task | PASS | Actual git history contains distinct Q1-Q7 implementation/evidence commits and earlier predictions |
| Existing repository preserved and working public link | PASS | Remote URL verified; first source/evidence push to existing main succeeded |
| All final files pushed and clean remote-matching working tree | PASS | Source, evidence and report commit7aa59be pushed; local/remote hashes matched and clean tree verified; handoff rechecks final status commit |
| README with identity,compiler,run steps,task results and report links | PASS | README.md |
| Report Markdown and PDF with cover,source,tests,outputs,screenshots,complexity | PASS | Rendered pages reviewed; source, outputs, tables and genuine screenshot panels verified |
| Viva preparation with likely questions and two modifications per task | PASS | VIVA_PREPARATION.md |
| No tracked binaries,toolchain archives,credentials or fabricated evidence | PASS | Tracked-file audit; build/ ignored; genuine output/screenshot provenance |
| PDF repository naming convention | PENDING | PDF expects DSA01-192471019-Assignment2; user requires existing different name; faculty acceptance needed |
| PDF31October2026 deadline / late acceptance | PENDING | Actual work10November2026; no backdating; faculty decision required |
| Student individually executes every task including TODOs | PENDING | PDFp1; current automated/browser evidence does not certify personal execution |
| Classroom correct course/assignment selection and final submission | PENDING | User explicitly chooses to submit personally; browser account signed out; materials prepared |

The source, evidence and report are published in the existing repository. The final handoff verifies remote equality and a clean working tree. Classroom submission belongs to the user.

Current online evidence is in screenshots/; eight earlier authentic captures remain in outputs/initial_execution/screenshots/ for provenance. Console demonstrations omit PASS labels. Validation logs and the required test tables retain statuses.
