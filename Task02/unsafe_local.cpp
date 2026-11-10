// Diagnostic-only negative example. Never execute this demonstration.
int& danglingReference() {
    int localMark=90;
    return localMark;
}
int main() { return 0; }
