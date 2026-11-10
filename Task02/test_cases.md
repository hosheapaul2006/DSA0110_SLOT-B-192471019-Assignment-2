# Q2 test plan and evidence

| ID | Input / scenario | Expected result | Actual result | Status |
|---|---|---|---|---|
| 1 | {67,91,78,91}, +2 | First 91 becomes 93 | Checked in main_actual.txt | PASS |
| 2 | highest(...)=95 | Array element becomes 95 | Checked | PASS |
| 3 | Copy plus two | Copy 97, array 95 | Checked | PASS |
| 4 | Const reference | Address matches element, value 95 | Checked | PASS |
| 5 | Index then pointer increments | Element 97 | Checked | PASS |
| 6 | Single 0 updated to 100; tied maxima | 100; first tie index 0 | Checked | PASS |
| 7 | Empty register | -1/null; reference throws | Checked | PASS |
| 8 | Nonempty null register | invalid_argument | Checked | PASS |
| 9 | reserve(capacity+1), append99 | Reacquired 90; new maximum index3 | Checked without using old aliases | PASS |
| 10 | Return local reference, compile only | GCC local-reference warning | See unsafe_local_compiler.txt | PASS |

The statuses apply only after the accompanying verification JSON records successful execution/diagnostic checks. The diagnostic-only source is never executed. Inputs are embedded in the sources; no stdin.
