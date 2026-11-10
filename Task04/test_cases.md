# Q4 executed tests

| ID | Input / scenario | Expected result | Actual result | Status |
|---|---|---|---|---|
| 1 | New zero account | count0,balance0 | Checked | PASS |
| 2 | Deposit10000,withdraw2500 paise | 7500, two records | Checked | PASS |
| 3 | 0/negative amounts,withdraw7501 | Reject all; unchanged balance/history | Checked | PASS |
| 4 | Withdraw7500 | Balance0 | Checked | PASS |
| 5 | First10 deposits | count10,zero shifts | Checked | PASS |
| 6 | 11th deposit | count10,nine shifts | Checked | PASS |
| 7 | 12th deposit | Exact complete statement for records3..12; 18 shifts | String comparison passed | PASS |
| 8 | LLONG_MAX balance +1 | Rejected; no transaction | Checked | PASS |
| 9 | Invalid opening account | invalid_argument | Caught | PASS |
| 10 | k=10,50,1000; 100000 full-history inserts | Assignments=(k-1)*100000; final arithmetic-series checksum | Checked in baseline_growth_actual.txt | PASS |

Evidence: outputs/*_verification.json and *_actual.txt. Main and baseline compiled at -O0; timings are actual local measurements, not Programiz timings. No stdin required.
