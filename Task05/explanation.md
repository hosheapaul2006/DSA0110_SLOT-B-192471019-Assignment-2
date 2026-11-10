# Q5 - College bus tickets

Principle: seat issuance state belongs to the class as a whole, so one private static `issued` counter is shared by all tickets. Each ticket holds its own passenger name and seat. The constructor assigns ++issued while below capacity, otherwise leaves seat zero to represent waiting. Waiting tickets do not inflate the number of seats issued. The out-of-class `int BusTicket::issued=0;` is a definition that allocates the shared object. C++17 also allows inline static definitions, but the supplied style is retained.

## Algorithm and lifecycle

Validate the passenger; if issued<capacity increment issued and store that seat; otherwise store zero. Print either Seat N or Waiting. Static count() returns issued and is called as BusTicket::count() without a ticket. A static member function has no this pointer, so it cannot access any particular object's seat/name without an explicit object.

An initialized array constructs each element in increasing index order. Five tickets with capacity three get 1,2,3,0,0. createTickets() constructs two more tickets and is called twice; all remain waiting and the static count stays three. Automatic ticket objects die on return, but the static counter remains until program termination. This model counts seats ever issued for one trip; destruction is not cancellation and never frees a seat. Waiting is a recorded status; automatic queue promotion/cancellation is outside the stated exercise. Starting another bus requires distinct office state, not secretly resetting a shared static counter.

The independent implementation deletes copying to avoid duplicating a seat by ordinary copies. C++17 guaranteed copy elision permits the array's direct prvalue initialization. This restriction is deliberately not added to the supplied TODO exercise: only its two TODOs change.

## Supplied programs and prediction

Token's static next starts at 100 because of its out-of-class initializer. Four constructors issue 101..104. The requested printed IDs are 101,103,104 and issued() is 4. The prediction was committed before execution and remains unchanged. The BusTicket TODO prints the exact expected Asha/Bala/Chitra/Dev output. Original text is preserved in Reference; only TODO regions were replaced.

## Alternatives

| Design | Issue time / extra space per issue | Shared state | Encapsulation / two buses |
|---|---|---|---|
| Static class counter | O(1) / O(1) | one counter per class | private but globally shared across class instances |
| Global counter | O(1) / O(1) | one global counter | easy accidental modification; still one bus unless generalized |
| TicketOffice | O(1) / O(1) | one counter per office/bus | private state, independently configurable capacities |

Names take O(L) character storage/copy time, where L is name length, in addition to constant seat bookkeeping. n tickets use O(n + sum L) storage. A single bus needs one counter in all alternatives; b independently tracked buses need O(b) counters. The main program executes both alternatives, including independent buses and a zero-capacity bus. Prefer TicketOffice for multiple buses; static BusTicket is clear for the assignment's one-bus model.
