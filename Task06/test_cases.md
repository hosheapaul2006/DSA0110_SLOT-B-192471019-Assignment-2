# Q6 executed correctness tests

| ID | Input / scenario | Expected result | Actual result | Status |
|---|---|---|---|---|
| 1 | 09:45,13:10 | Difference205; first earlier; reverse false | All three interfaces matched | PASS |
| 2 | 12:00,12:00 | 0,false | Matched | PASS |
| 3 | 11:59,12:01 | 2,true | Matched | PASS |
| 4 | 15:30,08:15 | 435,false | Matched | PASS |
| 5 | 00:00,23:59 and reverse | 1439,true and 1439,false | Matched | PASS |
| 6 | h=-1,24; m=-1,60 | Four invalid_argument exceptions | Four caught | PASS |
| 7 | Supplied TODO | Exact `205 false` plus newline | Exact expected output matched | PASS |
| 8 | Four benchmark modes, five trials, two optimization levels | All checksums agree per run | See benchmark outputs and verification JSON | PASS |

Deterministic embedded inputs; no stdin. Benchmark timings are excluded from exact-output comparisons because they are measured values.
