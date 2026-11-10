# Token prediction before execution

The static next counter is defined as 100 before main. The three counter array
elements run the constructor in order and receive 101,102,103. extra receives
104. issued() returns 104-100=4. Four constructors run. The exact predicted
output is in predicted_output.txt and is committed before the first execution.
