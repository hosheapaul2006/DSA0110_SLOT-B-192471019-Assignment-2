# Prediction comparison

Prediction commit: c2a6ade. First local execution occurred after that commit.
The supplied program matched every predicted character, including the trailing
space on line 3. Windows stdout encodes newlines as CRLF; text comparison decodes
these as LF and changes no spaces or other characters. No semantic differences.
The original prediction file was not rewritten. All three stored-fee predictions
and the sequential result were checked by main.cpp's executed assertions.
