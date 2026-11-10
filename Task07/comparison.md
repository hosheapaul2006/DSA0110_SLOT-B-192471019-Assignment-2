# Q7 measured comparison

Milliseconds for100000 full-history Transaction insertions; five trials. Ratios are median shifting time / median circular time.

| Flags | Capacity | Shifting trials (ms) | Circular trials (ms) | Median shift | Median ring | Speedup |
|---|---|---|---|---|---|---|
| -O0 | 10 | 2.8757, 2.4487, 2.4782, 2.5846, 2.5413 | 0.9750, 0.7943, 0.8366, 0.8422, 0.8251 | 2.5413 | 0.8366 | 3.04x |
| -O0 | 50 | 12.3926, 12.6008, 12.3690, 12.3287, 12.9527 | 0.8101, 0.8055, 0.8363, 0.8386, 0.8277 | 12.3926 | 0.8277 | 14.97x |
| -O0 | 1000 | 225.4640, 221.6180, 221.2820, 220.6250, 218.4960 | 0.8680, 0.8590, 0.8666, 0.8750, 0.8533 | 221.2820 | 0.8666 | 255.35x |
| -O2 | 10 | 0.4432, 0.4540, 0.4333, 0.4369, 0.4333 | 0.2273, 0.2272, 0.2271, 0.2271, 0.2281 | 0.4369 | 0.2272 | 1.92x |
| -O2 | 50 | 1.5222, 0.8671, 0.8588, 0.8580, 0.8582 | 0.2270, 0.2271, 0.2271, 0.2314, 0.2304 | 0.8588 | 0.2271 | 3.78x |
| -O2 | 1000 | 15.6824, 15.9921, 15.7721, 15.7157, 15.7807 | 0.2274, 0.2296, 0.2477, 0.2278, 0.2336 | 15.7721 | 0.2296 | 68.69x |

Correctness objective: PASS. Both designs matched every field of every one of10000 oracle snapshots per design, plus all benchmark final sequences.

Capacity1000 timing objective (at least2x under both flags): PASS. These are observed local medians, not guaranteed platform-wide speedups.

The original pre-implementation prediction remains in outputs/redesign_prediction.md (commit a8e1a25). Compare its small-capacity caveat with the measured rows; it was a hypothesis, and any contrary observation is retained here.

The circular design is recommended for bounded history with larger capacity. It adds a start index and wrapped traversal; the simpler shifted representation remains defensible for tiny, infrequently updated histories. Statement/snapshot complexity remains O(k). Both benchmark stores allocate once at construction and never grow on push.
