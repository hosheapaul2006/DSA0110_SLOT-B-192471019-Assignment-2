# Q7 objective and prediction - BEFORE redesign implementation and benchmarking

## A. Original evidence

Task04 baseline_growth.cpp already executed at -O0. For 100000 full-history
insertions: capacity10 shifted900000 entries in1.7393ms; capacity50 shifted4900000
in10.5686ms; capacity1000 shifted99900000 in175.542ms. Its checksum assertions
passed. These timings concern scalar entries and are diagnosis evidence, not
the final apples-to-apples Transaction benchmark. The Q4 class also directly
checked nine Transaction shifts on its 11th insertion.

## B. Measurable objective

Preserve identical last-k Transaction records in chronological order, including
amount, balance, type and sequence. Reduce full-history insertion work from
k-1 shifted records plus one appended record to one overwritten record and
constant index bookkeeping. Target at least a 2x reduction in median elapsed
update time at k=1000 under both -O0 and -O2, using 100000 updates and five trials
per capacity/optimization level. Also report k=10 and k=50 without presuming a win.

## C. Proposed design

Use a bounded circular array, held in one vector allocated at construction with
a runtime capacity. The vector is never resized during updates. Keep start and
count; overwrite the oldest slot when full and advance start modulo capacity.
Snapshot traverses logical oldest-to-newest order. Both comparison versions
will use exactly the same Transaction type, allocated capacity and test stream.
This is a hand-designed indexing redesign, not replacement with a library queue.

## D. Prediction

For k=1000 I predict a median speedup greater than 2x at both optimization
levels. This is a testable hypothesis, not a result. I predict exactly one
Transaction write per full ring insertion versus 1000 writes for shifting
(999 moves + one appended write). k=10 may have a small or absent timing win
because modulo/index overhead can dominate a short optimized copy. k=50
should lie between these cases. Both designs use O(k) storage; the ring needs
one additional start index. Snapshot remains O(k) and is outside update timing.

This file must be committed before writing the circular implementation or
running any comparison benchmark. Do not rewrite it after measurements.
