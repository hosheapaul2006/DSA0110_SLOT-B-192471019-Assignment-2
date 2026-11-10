# Q4 - Savings account mini-statement

The class stores its account number, nonnegative balance, fixed Transaction[10], and transaction count privately. Each successful operation records an amount, resulting balance, type and sequence number. Deposits/withdrawals take integer paise. Failed operations do not change balance or history. Opening balances are not transactions. The constructor and simple observers are defined inside the class; deposit, withdraw, record and miniStatement use `SavingsAccount::` outside it.

Private data prevents callers from manufacturing a false balance, count or transaction. The statement prints oldest to newest. It exposes output rather than mutable internal storage. This is a single-threaded educational model with no interest, transfers, persistent storage or concurrency.

## Original algorithm and evidence

Validate amount and funds/overflow before mutation. Update balance. If history is full, copy entries 1..9 into 0..8 and reduce count to 9. Append the new record and restore count to 10. The 11th transaction discards transaction 1 and makes exactly nine record shifts. The 12th discards transaction 2. The executed complete-statement comparison verifies transactions 3..12 in order and the correct balances.

`baseline_growth.cpp` generalizes only the original shifting strategy to k=10,50,1000. It performs 100000 full-history insertions, counts assignments, times the loop, and checks final contents with a closed-form sum. Its measured outputs supply original-design evidence for Q7; no redesign exists yet in this task.

## Alternatives and changed capacity

| Storage | Add full history | Statement | Storage | Trade-off |
|---|---|---|---|---|
| Shifted array | O(k) | O(k) | O(k), contiguous | simplest physical chronological order |
| Circular array | O(1) | O(k) | O(k) plus start/count | wrapped logical ordering |
| deque | O(1) end insertion/front removal | O(k) | O(k) plus block/allocation overhead | easy growth, noncontiguous storage |

Circular pseudocode: if count<k, write at (start+count)%k and increment count; otherwise overwrite at start and set start=(start+1)%k. Print element (start+i)%k for i=0..count-1. Deque pseudocode: push_back(record); if size>k pop_front().

The literal ten-entry original class demonstrates the assignment's fixed array. A named capacity/template parameter lets either array design change from 10 to 50 with one capacity change. A deque limit similarly changes with one constant. Thus a ring does not uniquely require fewer source edits than a properly parameterized shifting array; its advantage is stable update work. At k=50 the original full update moves 49 records rather than nine. For a literal fixed k=10, O(k) is O(1) with respect to the number of transactions; the growth comparison treats capacity as a variable. Prefer a circular array when bounded storage and larger history are required, contingent on measured costs in Q7. For ten records and rare updates, shifting may remain clearer.
