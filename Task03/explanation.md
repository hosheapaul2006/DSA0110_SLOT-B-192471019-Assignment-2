# Q3 - Courier charge calculator

The PDF gives no monetary tariff. The documented illustrative rule, selected before implementation, is Rs 50 per started kilogram plus Rs 30 express and Rs 20 insurance. Integer input means grams; floating input means kilograms. Optional booleans default to false. Nonfinite, nonpositive and over-one-million-kilogram weights are rejected to keep pricing arithmetic in int range. This is an example policy, not a real courier tariff.

## Diagnose and redesign

`ambiguity.cpp` retains the three declarations from the PDF and adds the two ambiguous calls. The one- and two-argument declarations compete with the three-argument declaration using defaults. Default use does not make an otherwise identical match worse. GCC's genuine errors are in outputs/ambiguity_compiler.txt. This is an expected negative test, not a broken delivered implementation.

The working design has exactly one numeric overload per unit type: `charge(int,bool=false,bool=false)` and `charge(double,bool=false,bool=false)`, plus `charge(const Parcel&)`. All route to one tariff calculation. Pseudocode: validate kilograms; ceiling to started kilograms; multiply by 50; add requested option charges. The six predicted selections are in outputs/overload_predictions.md and their exact predicted output was committed before running main.cpp.

An exact match ranks ahead of a promotion, which ranks ahead of other standard conversions. For charge(2), int is exact. For charge(2.0f), float-to-double is a promotion whereas float-to-int is a conversion. Default arguments fill omitted trailing parameters; in these ordinary declarations, once a parameter has a default all following parameters must have defaults visible in the declaration. There is no syntax for skipping a middle positional argument. Return types do not choose an overload. Overload resolution occurs at compile time; it adds no runtime dispatch.

The delivered six calls are unambiguous. This is not a claim that arbitrary unrelated user-defined input types can never produce ambiguity: callers should use the documented int, floating-point, or Parcel inputs. In particular a type convertible equally well to both numeric overloads may require an explicit cast.

## Alternatives and complexity

| Design | Runtime / auxiliary space | Copying | Adding a new option |
|---|---|---|---|
| Overloads with defaults | O(1) / O(1) | scalar values, Parcel passed by const reference | update numeric wrappers and shared calculation |
| Single const Parcel& | O(1) / O(1) | no object copy at entry; caller owns a fixed-size object | add a defaulted field; call sites can stay short |
| Constrained template | O(1) / O(1) | scalar Weight by value | modify template/wrapper and calculation |

`parcelCharge` implements the single-structure alternative and `templateCharge` implements a C++17 compile-time integral/floating branch. Both are exercised. Template instantiations may increase code size and can obscure the units policy unless constrained. Compile-time lookup/instantiation costs are not runtime Big-O costs and were not benchmarked. A temporary Parcel is fixed size and O(1) to construct. Prefer the overloads for this teaching exercise; for many future options, a named Parcel request scales better than a long list of positional booleans.
