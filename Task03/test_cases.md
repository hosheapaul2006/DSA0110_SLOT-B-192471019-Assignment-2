# Q3 executed tests

| ID | Input / scenario | Expected result | Actual result | Status |
|---|---|---|---|---|
| 1-6 | Six precommitted calls | int,double,double,int,double,Parcel; 50,100,150,130,70,150 | Exact character comparison passed | PASS |
| 7 | 1000 and 1001 grams | Rs50 and Rs100 | C++ checks passed | PASS |
| 8 | Parcel and template alternatives | Same tariff | Checks passed | PASS |
| 9 | 0,-1,1000001,inf,NaN kg; -2 grams | Six invalid_argument exceptions | Six caught | PASS |
| 10 | Original declarations and two calls | Ambiguous compiler errors | Genuine GCC diagnostic captured | PASS |

See outputs/main_actual.txt, main_verification.json and ambiguity_compiler.txt. Inputs are embedded; no stdin. Prediction comparison normalizes only platform newline encoding. No original prediction was changed.
