# Q7 executed tests

| ID | Input / scenario | Expected result | Actual result | Status |
|---|---|---|---|---|
| 1 | Capacity0, both designs | invalid_argument | Caught and checked | PASS |
| 2 | Empty histories at1,10,50,1000 | Empty snapshots | Checked | PASS |
| 3 | First fill and first overwrite | Same chronological records as deque | Every snapshot checked | PASS |
| 4 | 2500 generated records per capacity | Every field in every snapshot matches independent oracle | All10000 snapshots per design matched | PASS |
| 5 | 100000 full-history updates, capacities10,50,1000 | Exact final input suffix | Checked outside each timing | PASS |
| 6 | Five trials per capacity, both -O0/-O2 | Comparable real measurements, equal checksums | Raw CSV plus verification JSON | PASS |

See comparison.md for the objective evaluation. validation_demo.cpp preserves the combined full validation. programiz_demo.cpp is a self-contained demonstration assembled from the same history definitions; it prints the original/redesigned retained sequences without validation labels and is compiled locally before Programiz execution.
