# Q6 measured results

All timings are milliseconds for 10000000 difference calls plus 10000000 earlier calls. Five trials per row; values come directly from the captured CSV output.

| Optimization | Design | Trials (ms) | Median (ms) |
|---|---|---|---|
| -O0 | friend_inline | 44.4563, 42.6810, 48.5856, 45.0479, 45.2734 | 45.0479 |
| -O0 | friend_ordinary | 42.6123, 52.9873, 44.9704, 49.4588, 44.6219 | 44.9704 |
| -O0 | member | 44.0498, 50.2164, 45.0060, 50.0194, 43.2113 | 45.0060 |
| -O0 | getters | 108.7380, 110.7260, 112.5360, 109.0650, 109.2900 | 109.2900 |

| -O2 | friend_inline | 10.2862, 10.2020, 10.2218, 10.8555, 10.7794 | 10.2862 |
| -O2 | friend_ordinary | 10.2029, 10.3305, 10.3684, 10.4878, 10.5681 | 10.3684 |
| -O2 | member | 10.2289, 10.2325, 10.4112, 10.5775, 10.4004 | 10.4004 |
| -O2 | getters | 10.1997, 10.2155, 10.2869, 10.5756, 10.4375 | 10.2869 |

All printed checksums match within each executable. The keyword does not force the optimizer to retain a call boundary; ordinary functions can also be inlined. These are observations of this compiler/machine/run, including loop and access work. No isolated nanosecond call cost is inferred.

Raw data: outputs/benchmark_O0_actual.txt and outputs/benchmark_O2_actual.txt. Compilation commands, source hashes, UTC timestamps and exit codes are in the corresponding verification JSON.
