# Q7 - Diagnose, redesign and validate

## A. Diagnose the limitation

Q4's correct shifting class performs nine record moves on the 11th update. Its executed growth baseline measured 900000,4900000,99900000 assignments for 100000 insertions at capacities10,50,1000. The measured -O0 times grew from1.7393 to10.5686 to175.542ms. This identifies repeated movement of retained records as a capacity-dependent cost. The scalar baseline diagnoses growth; final comparison uses identical full Transaction records for both designs.

## B. Define the objective

Before implementation, outputs/redesign_prediction.md established identical chronological contents and a >=2x median update speedup at capacity1000 under both -O0 and -O2. It specified 100000 updates and five trials. Smaller capacities are observations, not required timing wins. The prediction is committed as a8e1a25 and remains immutable.

## C. Design the revised solution

Extract bounded transaction history as a small private-storage component. The original shifts the allocated array; the redesign stores count and start and uses modular indexing. Both use the same vector-backed contiguous allocation to permit capacity10,50,1000 without recompilation. Neither resizes on push, allocates in the timed loop, or uses a library container as the queue algorithm. The original Q4 literal array remains available unchanged. Only retention changes; successful-transaction validation and balance rules remain Q4's responsibility. The retention tests use arbitrary transaction payloads, not an alternate banking policy.

Circular pseudocode:

```text
if count < capacity:
    records[(start + count) % capacity] = new_record
    count += 1
else:
    records[start] = new_record
    start = (start + 1) % capacity
for i in 0 .. count-1:
    display records[(start + i) % capacity]
```

The C++ features are classes with private state, const-reference parameters, constructors, vectors used solely as fixed allocated arrays, and const snapshot methods. Both use O(k) record storage and O(k) statement/snapshot time. Original insertion is O(k); ring insertion O(1). The ring adds one size_t start index (implementation padding may affect sizeof). Snapshot materialization allocates O(k) temporary storage in both; a streaming statement could use O(1) extra space instead. Capacity is fixed per constructed instance, not unbounded.

## D. Predict before implementing

See the original precommitted prediction: >2x at capacity1000 for both flags, potentially weak or absent benefit at10. A full ring update performs one record assignment plus index work; shifting performs k-1 moves plus append. These operation counts follow from the algorithm; the elapsed times below are measured separately. No historical prediction was reconstructed after running.

## E. Implement and validate

original.cpp and redesigned.cpp run identical validation templates against an independent std::deque oracle. For capacities1,10,50,1000 every one of 2500 successive snapshots is checked, including empty state, first fill and repeated wraps. Every field is compared, not just the last item or checksum. Zero capacity is rejected.

benchmark.cpp uses the same pre-generated sequence of100000 Transaction objects and initially full histories. It times only pushes, checks the entire final sequence outside timing, and prints an observable checksum. Five trials alternate ordering. Both classes use the same allocation type, payload and capacity. -O0 and -O2 builds use identical flags except optimization. No IO, allocation, per-iteration volatile or instrumentation counter dominates the update loop. The optimizer may turn the shift loop into a bulk copy; that is valid measured behaviour. Raw timings and medians appear in comparison.md.

## F. Defend the final design

Judge the objective from comparison.md, not complexity alone. A ring guarantees constant update work as capacity grows, with extra index bookkeeping and a less direct logical order. It requires wraparound tests and the capacity must be nonzero. A shifted array can remain preferable for tiny histories, infrequent updates or a requirement that physical storage always be chronological. Capacity changes from10 to50 are one constructor argument for either generalized class. These microbenchmarks do not include banking validation, persistent storage, GUI work or concurrent access, so their speedups apply only to retention updates in this environment.
