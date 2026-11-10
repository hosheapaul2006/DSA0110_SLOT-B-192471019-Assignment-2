# Q5 executed tests

| ID | Input / scenario | Expected result | Actual result | Status |
|---|---|---|---|---|
| 1 | Initial class state | count0 | Checked | PASS |
| 2 | Array5,capacity3 | Seats1,2,3; two waiting; count3 | Checked and printed | PASS |
| 3 | Function creates2 tickets, called twice | Four waiting; count still3 after destruction | Checked | PASS |
| 4 | Empty passenger | Reject; count unchanged | Checked | PASS |
| 5 | Global counter alternative | 1,2,3,0 | Checked | PASS |
| 6 | Offices of capacity1,2,0 | Independent seat1 on each bus; overflow waits | Checked | PASS |
| 7 | Token prediction program | 101 103 104 4 | Exact precommitted prediction matched | PASS |
| 8 | Supplied TODO | Three seats,Dev waiting,Issued3 | Exact expected output matched | PASS |

See outputs/*_verification.json and *_actual.txt. Every valid source is compiled warning-free and executed; no stdin required. Character comparison normalizes Windows newlines only.
