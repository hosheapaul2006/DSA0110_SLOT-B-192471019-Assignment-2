# Q1 executed tests

| ID | Input / scenario | Expected result | Actual result | Status |
|---|---|---|---|---|
| 1 | 45000, 10% | local 40500; caller value 45000; reference/pointer 40500 | Exact values verified in main_actual.txt | PASS |
| 2 | 45000, 15% | local 38250; value 45000; reference/pointer 38250 | Exact values verified | PASS |
| 3 | 45000, 25% | local 33750; value 45000; reference/pointer 33750 | Exact values verified | PASS |
| 4 | Sequential 10%,15%,25% | 25819 | 25819 | PASS |
| 5 | Zero fee; 0% and 100% | 0; unchanged; 0 | All assertions passed | PASS |
| 6 | LLONG_MAX,100% | 0 without overflow | Assertion passed | PASS |
| 7 | -1%,101%; negative fee; null pointer | invalid_argument | Exceptions caught and checked | PASS |
| 8 | Student reads and reference update | 45000 reads; updated fee 40500 | Assertions passed | PASS |
| 9 | Supplied prediction | Exact precommitted prediction | Identical after newline decoding | PASS |
| 10 | Supplied TODO | 45000 then 40500 | Exact expected output comparison passed | PASS |

Evidence: outputs/*_verification.json, outputs/main_actual.txt, outputs/predict_output_actual.txt and outputs/complete_code_actual.txt. All three programs compiled warning-free at -O0. Inputs are deterministic and embedded in main; no stdin is needed.
