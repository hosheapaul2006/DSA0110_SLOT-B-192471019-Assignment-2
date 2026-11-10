# Predictions recorded before the first Q1 execution

Each independent demonstration begins at 45000 rupees.

| Concession | By value: inside / caller | By reference: caller | By pointer: caller |
|---|---|---|---|
| Merit 10% | 40500 / 45000 | 40500 | 40500 |
| Sports 15% | 38250 / 45000 | 38250 | 38250 |
| Single parent 25% | 33750 / 45000 | 33750 | 33750 |

Sequential return-value updates: 45000 -> 40500 -> 34425 -> 25819.
The last discount truncates 8606.25 to 8606, then subtracts it.
The supplied TODO program should print 45000 after value and 40500 after reference.

For the supplied prediction program, change modifies b and c only. bigger(a,c)
aliases c and assigns 100 to it. show uses defaults (5,10), then just 10, then none.
The third output line has a trailing space before its newline. The original
prediction is immutable after execution; any differences belong in comparison.md.
