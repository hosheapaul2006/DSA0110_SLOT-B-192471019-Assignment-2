# Q2 - Examination marks register

Objective: update the first highest mark directly while understanding alias lifetime.

## Algorithm and interfaces

Scan the nonempty register once, remember the index of the largest element, and replace the index only on a strict increase. This deterministically selects the first tie. Returning `marks[index]` as `int&` aliases an existing element, so `highest(marks,4) += 2` updates it and `highest(marks,4) = 95` is a valid assignment. Returning an int copies the value; changing the copy cannot change the register. `const int&` avoids a value copy but prevents assignment through that alias. It is not a snapshot and does not prevent another alias from changing the element.

Index calling code: `int i=highestIndex(marks,n); if(i>=0) marks[i]+=2;`.
Pointer calling code: `int* p=highestPointer(marks,n); if(p) *p+=2;`.
The reference/copy/const-reference interfaces throw for an empty register; index returns -1 and pointer returns null. Invalid negative length or nonempty null register is rejected. Raw pointer lengths must describe actual accessible storage; this API cannot discover an incorrect caller-provided positive length.

## Dangling reference and vector growth

`unsafe_local.cpp` returns an alias to an automatic local object. That object dies when its function returns. A reference does not keep it alive; using the dangling alias is undefined behaviour. The source is compiled with `-Wreturn-local-addr`, its real diagnostic is stored in outputs/unsafe_local_compiler.txt, and its executable is deliberately never run.

Vector reallocation moves/copies elements into new storage, invalidating all references, pointers and iterators into old storage. The executed vector test forces this with reserve(oldCapacity+1), then reacquires through a saved index. It does not read an invalid reference or pointer. Without reallocation, push_back preserves existing element aliases but invalidates the old end iterator. Erase/insert may shift elements even without reallocation. An index survives storage relocation if sequence positions stay the same, but is not a permanent identity and need not still identify the maximum after growth. The append-99 test explicitly recomputes the maximum.

## Comparison and design decision

| Return type | Search time | Auxiliary space | After array/vector storage changes |
|---|---|---|---|
| int& | O(n) | O(1) | may dangle; cannot represent empty directly |
| const int& | O(n) | O(1) | same lifetime risk; read-only through this alias |
| int copy | O(n) | O(1) | independent snapshot; cannot update original |
| int index | O(n) | O(1) | can reacquire after reallocation; validate bounds/meaning |
| int* | O(n) | O(1) | can be null, but may dangle like a reference |

The returned primitive itself is constant size in every case. Prefer an index with immediate bounds-checked reacquisition for a growing register. Recompute when the question is 'current highest'. A fixed array with a controlled lifetime is suitable for the reference demonstration; do not expose a long-lived mutable alias to a reallocating vector.
