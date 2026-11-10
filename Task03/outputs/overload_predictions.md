# Predictions before execution

| Call | Selected overload | Reason |
|---|---|---|
| charge(2) | int grams | exact int match beats int-to-double conversion |
| charge(2.0f) | double kilograms | float-to-double promotion beats float-to-int conversion |
| charge(2.5) | double kilograms | exact double match |
| charge(1500,true) | int grams | exact int and bool; third argument defaults false |
| charge(1.0,false,true) | double kilograms | exact double and bool matches |
| charge(Parcel{1.2,true,true}) | const Parcel& | binds Parcel; no numeric overload is viable |

For the separate original declarations, charge(2.0) is ambiguous between the
one-argument overload and the three-argument overload using two defaults.
charge(2.0,true) is ambiguous between the two-argument and three-argument forms.
These predictions and the exact expected demonstration output are committed
before compiling/running the corresponding programs.
