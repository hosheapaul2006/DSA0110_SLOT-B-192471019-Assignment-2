#include <iostream>
#include <stdexcept>
#include <vector>

int highestIndex(const int* marks, int count) {
    if (count < 0 || (count > 0 && marks == nullptr)) throw std::invalid_argument("invalid register");
    if (count == 0) return -1;
    int best=0;
    for (int i=1;i<count;++i) if (marks[i]>marks[best]) best=i;
    return best;
}
int& highest(int* marks, int count) {
    const int index=highestIndex(marks,count);
    if(index<0) throw std::out_of_range("empty register");
    return marks[index];
}
const int& highestConst(const int* marks, int count) {
    const int index=highestIndex(marks,count);
    if(index<0) throw std::out_of_range("empty register");
    return marks[index];
}
int highestCopy(const int* marks,int count) { return highestConst(marks,count); }
int* highestPointer(int* marks,int count) {
    const int index=highestIndex(marks,count);
    return index<0 ? nullptr : &marks[index];
}
void check(bool condition,const char* label) {
    if(!condition) throw std::runtime_error(label);
}
int main() {
    int marks[]={67,91,78,91};
    std::cout << "Original highest=" << highestCopy(marks,4) << '\n';
    highest(marks,4)+=2;
    std::cout << "After +2 through reference=" << marks[1] << '\n';
    check(marks[1]==93 && marks[3]==91,"moderate first highest by reference");
    highest(marks,4)=95;
    std::cout << "After assignment to function call=" << marks[1] << '\n';
    check(marks[1]==95,"function call on assignment left side");
    int copy=highestCopy(marks,4); copy+=2;
    check(copy==97 && marks[1]==95,"copy is independent");
    std::cout << "Changed copy=" << copy << ", stored mark=" << marks[1] << '\n';
    const int& readOnly=highestConst(marks,4);
    check(readOnly==95 && &readOnly==&marks[1],"const reference aliases array");
    std::cout << "Const reference reads=" << readOnly << '\n';
    const int index=highestIndex(marks,4); marks[index]+=1;
    int* pointer=highestPointer(marks,4); *pointer+=1;
    check(marks[1]==97 && index==1 && pointer==&marks[1],"index and pointer update");
    int single[]={0}; highest(single,1)=100;
    check(single[0]==100,"single element and mark boundaries");
    check(highestIndex(nullptr,0)==-1 && highestPointer(nullptr,0)==nullptr,"empty index and pointer sentinels");
    bool empty=false,invalid=false;
    try { highest(nullptr,0); } catch(const std::out_of_range&) { empty=true; }
    try { highestIndex(nullptr,1); } catch(const std::invalid_argument&) { invalid=true; }
    check(empty && invalid,"empty reference and invalid register rejected");
    int ties[]={80,80,70}; check(highestIndex(ties,3)==0,"ties choose first element");
    std::vector<int> growing={65,90,72};
    const int savedIndex=highestIndex(growing.data(),static_cast<int>(growing.size()));
    { const int& before=growing[savedIndex]; check(before==90,"reference valid before growth"); }
    const auto oldCapacity=growing.capacity();
    growing.reserve(oldCapacity+1); // Forces reallocation; do not use any old alias.
    check(growing.capacity()>oldCapacity && growing[savedIndex]==90,"index reacquired after forced reallocation");
    growing.push_back(99);
    check(highestIndex(growing.data(),static_cast<int>(growing.size()))==3,"recompute maximum after append");
    std::cout << "Final moderated mark=" << marks[1] << '\n';
}
