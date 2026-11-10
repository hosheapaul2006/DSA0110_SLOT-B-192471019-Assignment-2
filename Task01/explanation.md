# Q1 - Hostel fee concessions

Objective: show which parameter mechanisms update the caller, then choose an interface for multiple concessions.

`main.cpp` demonstrates merit 10%, sports 15% and single-parent 25% from independent 45000 fees. A value parameter is a separate local object; assigning it changes that copy. A reference parameter aliases the caller's object. A pointer parameter is itself copied but dereferencing its stored address accesses the caller's fee. A null pointer must be rejected; references require a valid object when bound.

## Algorithm

1. Validate fee >= 0 and percentage in [0,100].
2. Compute floor(fee * percent / 100); subtract the discount.
3. For reference or pointer interfaces, assign back to the caller's object.
4. To combine concessions, assign the returned new fee for each concession in order.

The main implementation splits quotient and remainder to avoid overflow in `fee * percent`. The supplied TODO uses the requested expression unchanged except for filling the TODO. Its demonstrated 45000 input is safely within range. Integer division truncates a nonnegative discount downward. Combining percentages is a different policy: sequential discounts give 25819, while adding rates to 50% would give 22500. Sequential application was selected explicitly; rounding occurs at each step.

## Prediction and supplied exercise

The prediction files were committed before the first run. `change` leaves a=1, changes b=12 and c=13. `bigger(a,c)` returns a reference to c, so assigning the call changes c to 100. For equal arguments the conditional chooses q. `show(1)` uses y=5,z=10; `show(1,2)` uses z=10; `show(1,2,3)` uses no defaults. The final output line ends with a space.

`complete_code.cpp` fills only TODO 1; `Reference/Q1_TODO_original.txt` preserves the original. Pass by value leaves the hostel fee at 45000 because no assignment to the original occurs. A const reference permits reading a large object without copying it and prohibits mutation through that parameter; it does not extend an arbitrary caller object's lifetime.

## Interface decision and alternatives

Keep all three interfaces for the demonstration. Prefer `fee = updatedFee(fee, percent)` when composing concessions: the assignment makes the update explicit, and calculating a candidate fee does not mutate existing state. A reference is convenient for a clearly named in-place operation. Pointer parameters are useful where optional/null arguments have a meaning, but add validation here.

| Parameter | Time | Extra parameter storage / copy | Mutation |
|---|---|---|---|
| long long by value | O(1) | sizeof(long long) | local only |
| long long reference / const reference | O(1) | typically one address; C++ does not mandate reference representation | mutable / read-only access |
| Student by value | O(S) in object size S | O(S) copied bytes | local only |
| Student reference / const reference | O(1) binding | O(1), no object copy | mutable / read-only access |
| pointer | O(1) | sizeof(pointer) copied | pointee can change |

For the fixed Student definition, S is constant and every call is O(1) as problem input grows; O(S) describes scaling the object. `sizeof` measurements in the actual output document the local ABI, not a required language-wide size. A trivially copied large object still costs memory bandwidth; optimizers can remove unobservable copies. References introduce aliasing and lifetime concerns. The program checks the boundary and negative cases without relying on timing guesses.
