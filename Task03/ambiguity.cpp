double charge(double weight);
double charge(double weight, bool express);
double charge(double weight, bool express = false, bool insured = false);
int main() {
    charge(2.0);       // Deliberately ambiguous: one-argument vs defaults.
    charge(2.0,true);  // Deliberately ambiguous: two-argument vs defaults.
}
