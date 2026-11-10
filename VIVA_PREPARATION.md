# Viva preparation - DSA0110 Assignment 2

D Hoshea Paul | 192471019 | Slot B

Practise compiling and running every task yourself. The PDF requires individual execution and faculty may ask you to change the code. Read the original predictions before rerunning their programs and explain each result without memorizing only the printed numbers. The validation sources are separate from the console demonstrations.

## Q1 - Passing fees

The same starting fee is sent to a copy, an alias and an address. The copy changes locally; the alias and dereferenced pointer change the caller. Sequential concessions use the remaining fee and round the discount down each time. Returning a new fee makes a chain of updates explicit.

- Why does value leave 45000 unchanged? The parameter is a separate object; no assignment is made to the caller.
- Can a reference be reseated? No. Assigning a reference assigns the object it already aliases.
- Does a pointer parameter avoid copying everything? The address itself is copied; the pointee is not copied.
- Why use const Student&? To read the large object without copying it or allowing mutation through that parameter.
- What does bigger(a,c)=100 do? bigger returns an existing int lvalue reference; assignment updates the selected object.
- What defaults does show(1,2) use? Only z=10; the result is13.
- Complexity? Primitive fee operations O(1) time/space. Copying an object of S bytes is O(S); binding a reference is O(1). With this fixed struct, S is a constant.

Practise modifications: (1) add a20% concession and calculate the expected fee before running; (2) replace the pointer interface with a const-pointer read-only enquiry and explain why assignment is rejected.

## Q2 - Returned references

The scan remembers the first index whose mark is largest. Returning the array element by reference lets callers moderate it directly. A copy is independent; a const reference is read-only through that alias. All aliases depend on the original storage staying alive and unmoved.

- Why is a local-reference return unsafe? The automatic local object dies at return; the alias dangles. A warning is evidence of the defect, not permission to run it.
- Is const reference safe after vector growth? No. Const affects mutation permission, not storage lifetime.
- Does vector push_back always invalidate existing references? Only when it reallocates; the old end iterator is invalidated regardless.
- Is an index always safe? It must be checked against the current size and its logical meaning can change after insert/erase or a new maximum.
- What happens on a tie? This design chooses the first maximum because the comparison is strictly greater.
- Complexity? Each search O(n), auxiliary space O(1), regardless of reference/copy/index/pointer return.

Practise modifications: (1) select the last maximum by changing > to >= and update the tie test; (2) return an optional index instead of -1 and show an empty-register caller.

## Q3 - Overloads and defaults

Integer weights mean grams; floating weights mean kilograms. One numeric overload per unit avoids the PDF's overlapping declarations. Both use a shared tariff implementation. Parcel groups weight and options into named fields.

- Why is charge(2) different from charge(2.0f)? int is exact for the grams overload; float promotes to double for kilograms.
- Does a default count as a poorer match? No. Equally good viable overloads can remain ambiguous even when one uses defaults.
- Can return type resolve the ambiguity? No; ordinary overload resolution does not select by the destination return type.
- Why trailing defaults? Ordinary positional calls cannot omit a middle argument; after a default all following ordinary parameters need visible defaults.
- What are the example rates? Rs50 per started kg, plus30 express and20 insurance. The PDF did not prescribe rates.
- Complexity? Constant runtime tariff/space. Choosing an overload is a compile-time process, not runtime dispatch overhead.

Practise modifications: (1) add a fragile option to Parcel and explain changes required by the overload wrappers; (2) add a float overload, predict charge(2.0f) again, then verify.

## Q4 - Account transaction history

The account validates the operation before changing balance. Only successful transactions enter the private ten-entry history. On a full history, shifting drops the oldest record and makes room at the end. The statement reads oldest to newest.

- Why private array and count? External code must not manufacture balances or corrupt the retention invariant.
- What happens on transaction11? Nine retained records move left; transaction1 is discarded and11 is appended.
- Why integer paise? Exact integer arithmetic avoids binary floating rounding for these amounts.
- Does a rejected withdrawal evict history? No; both balance and history remain unchanged.
- What changes at50? A parameterized array changes one capacity value; full shifting now moves49 records. Ring insertion still overwrites one slot.
- Complexity? Shifting O(k), ring/deque end maintenance O(1); printing O(k), storage O(k). For fixed10, k is a constant.

Practise modifications: (1) retain50 entries with one named capacity; (2) print withdrawals only while keeping the full chronological history unchanged.

## Q5 - Shared ticket counters

Each ticket stores its own name and seat; a single static counter tracks seats issued for the class's one bus. After capacity, new objects remain waiting. Leaving a function destroys its automatic objects but does not reset shared issuance state.

- Where is issued defined? Once outside the class, as int BusTicket::issued=0; the supplied program uses this style.
- Why can static count() run without an object? It has no this and uses only static state.
- How many Token constructors run? Four: three array elements and one extra; IDs101..104.
- Does a destructor free a seat here? No. Issued means seats allocated for this trip, not live C++ object count. Cancellation would require a separate policy.
- How can two buses both issue seat1? Give each a separate TicketOffice instance. One static or global counter conflates their state.
- Complexity? O(1) seat bookkeeping, one counter per bus/office. Names require O(L) storage/copy time; n tickets use O(n+sum L).

Practise modifications: (1) change capacity3 to5 and predict the sixth ticket; (2) create two TicketOffice objects and demonstrate independent waiting status.

## Q6 - Friends and inline

Clock times convert to minutes since midnight. Absolute subtraction gives difference; strict comparison determines earlier. A friend nonmember can read both private representations equally; member/getter alternatives implement the same arithmetic.

- Is friend necessary because there are two operands? No. It is one API choice; members or getters also work.
- Is friendship reciprocal or inherited? Neither, and it is not transitive.
- Does inline guarantee faster code? No. The compiler decides actual inlining and may inline ordinary functions too.
- What does inline additionally allow? Identical conforming definitions in multiple translation units, subject to the one-definition rules.
- Why not make h,m public? It exposes representation and allows invalid time states.
- What is the midnight interpretation? Same-day absolute clock difference; 23:59 vs00:00 is1439, not a one-minute overnight trip.
- Complexity? O(1) time/auxiliary space per comparison. The benchmark includes loop/index work; the keyword alone did not show a meaningful advantage.

Practise modifications: (1) implement forward elapsed time modulo1440 and change midnight expectations; (2) replace friend comparisons with a.minutesTo(b) and a.isEarlier(b), then rerun at both flags.

## Q7 - Evidence-based redesign

Q4's shift counts and growth timings identified repeated movement as the limitation. The redesign overwrites an oldest slot and advances start. Logical traversal maps index i to (start+i)%capacity. Both versions are tested against an independent deque oracle with every transaction field checked.

- What was predicted before implementation? Identical histories and at least2x median speedup at1000 under both flags; the prediction is committed and unchanged.
- What was actually measured? At1000, medians were221.2820 vs0.8666ms at-O0 and15.7721 vs0.2296ms at-O2. These are local retention-update timings.
- Why not say O(1) is automatically faster? Constant factors, compiler transformations, payload size and workload affect elapsed time. We report actual timings separately.
- What is the new cost? One start index, modular indexing, wraparound reasoning and less direct physical order.
- Why use the same vector allocation for both? It keeps allocation/storage representation comparable; neither grows in the timed loop. The queue algorithm is implemented manually.
- What remains O(k)? Printing/materializing a chronological snapshot and storing k records. Snapshot allocation is outside update timing.
- When might shifting be preferable? Tiny capacities, rare updates, simpler invariants or a need for physically chronological storage.

Practise modifications: (1) replace modulus advancement with a branch and benchmark without assuming it is better; (2) accept capacity at construction and test1,10,50,1000 and reject0.

## Personal rehearsal

Run all commands in README and read compiler diagnostics. Explain the trailing space in Q1's predicted output, the float promotion in Q3, static persistence in Q5, invalidation in Q2, the same-day assumption in Q6 and each A-F section of Q7. Reproduce one negative test and one benchmark. Keep a record of your own execution before submitting; the current automated/browser evidence does not certify that personal step.
