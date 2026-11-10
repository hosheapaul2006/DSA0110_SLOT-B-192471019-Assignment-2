# Prediction and presentation history

The original predictions were committed before execution and never rewritten.
Q1 supplied prediction: commit c2a6ade; Q3 overload prediction: c9dd5c2;
Q5 Token prediction: cbc5040; Q7 redesign prediction: a8e1a25.

After the initial executions, the student requested console demonstrations
without PASS labels. The original independent main programs are preserved as
Task01..Task06/validation.cpp. Their original main execution records and any
early online evidence are preserved under outputs/initial_execution/.
The historical records correctly name main.cpp, its path at execution time.
Their source SHA256 matches the preserved validation.cpp bytes, aside from
newline normalization where applicable. New main.cpp files suppress test labels
and show coursework results. Checks still run and throw on any mismatch.

In particular Q3/outputs/predicted_output.txt is the exact original prediction
for the source now named validation.cpp. It includes the original validation
labels. It is not relabelled as a prediction of the later presentation version.
Q1 and Q5 supplied prediction sources remain unchanged. Q7's original combined
validation demo is preserved as validation_demo.cpp; its new programiz_demo.cpp
shows the retained transaction sequences directly.

Final Programiz evidence uses the presentation sources. Automated validation
labels remain in separate validation outputs and test-case tables as requested.
