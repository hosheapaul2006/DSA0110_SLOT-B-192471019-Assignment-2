#include <iostream>
#include <limits>
#include <stdexcept>

long long updatedFee(long long fee, int percent) {
    if (fee < 0 || percent < 0 || percent > 100)
        throw std::invalid_argument("fee or percentage out of range");
    // Equivalent to fee * percent / 100 for nonnegative values, without overflow.
    const long long discount = (fee / 100) * percent + (fee % 100) * percent / 100;
    return fee - discount;
}
long long applyByValue(long long fee, int percent) {
    fee = updatedFee(fee, percent);
    return fee;
}
void applyByReference(long long& fee, int percent) { fee = updatedFee(fee, percent); }
void applyByPointer(long long* fee, int percent) {
    if (!fee) throw std::invalid_argument("null fee pointer");
    *fee = updatedFee(*fee, percent);
}
struct Student { char name[128]{}; long long fee{}; int marks[64]{}; };
long long readValue(Student student) { return student.fee; }
long long readConstReference(const Student& student) { return student.fee; }
void updateStudent(Student& student, int percent) { applyByReference(student.fee, percent); }

void check(bool condition, const char* label) {
    if (!condition) throw std::runtime_error(label);
}
int main() {
    const int rates[] = {10, 15, 25};
    const long long expected[] = {40500, 38250, 33750};
    for (int i = 0; i < 3; ++i) {
        long long valueFee=45000, referenceFee=45000, pointerFee=45000;
        const long long localFee=applyByValue(valueFee, rates[i]);
        applyByReference(referenceFee,rates[i]); applyByPointer(&pointerFee,rates[i]);
        std::cout << rates[i] << "%: local=" << localFee << " value=" << valueFee
                  << " reference=" << referenceFee << " pointer=" << pointerFee << '\n';
        check(localFee==expected[i] && valueFee==45000 && referenceFee==expected[i]
              && pointerFee==expected[i], "passing modes");
    }
    long long fee=45000;
    for (int rate:rates) fee=updatedFee(fee,rate);
    check(fee==25819,"sequential concessions and rounding");
    std::cout << "Sequential fee=" << fee << '\n';
    check(updatedFee(0,25)==0 && updatedFee(999,0)==999 && updatedFee(999,100)==0,
          "zero fee and 0/100 percent");
    check(updatedFee(std::numeric_limits<long long>::max(),100)==0,"large fee without overflow");
    for (int percent : {-1,101}) {
        bool rejected=false; try { updatedFee(100,percent); } catch(const std::invalid_argument&) { rejected=true; }
        check(rejected,"invalid percentage rejected");
    }
    bool negative=false, null=false;
    try { updatedFee(-1,10); } catch(const std::invalid_argument&) { negative=true; }
    try { applyByPointer(nullptr,10); } catch(const std::invalid_argument&) { null=true; }
    check(negative && null,"negative fee and null pointer rejected");
    Student student{}; student.fee=45000;
    check(readValue(student)==45000 && readConstReference(student)==45000,"large object reads");
    updateStudent(student,10); check(student.fee==40500,"large object reference mutation");
    std::cout << "sizeof(long long)=" << sizeof(long long) << " sizeof(Student)=" << sizeof(Student)
              << " sizeof(pointer)=" << sizeof(Student*) << '\n';
}
