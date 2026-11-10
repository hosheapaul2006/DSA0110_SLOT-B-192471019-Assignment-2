#include "history.hpp"
#include <chrono>
#include <cstdint>
#include <iostream>
#include <string>

constexpr int updates=100000;
template<class History>
void measure(int trial,int capacity,const char* name,const std::vector<Transaction>& input) {
    History history(static_cast<std::size_t>(capacity));
    // Start full: compare the same steady-state replacement workload.
    for(int i=0;i<capacity;++i) history.push(input[static_cast<std::size_t>(i)]);
    const auto begin=std::chrono::steady_clock::now();
    for(const auto& transaction:input) history.push(transaction);
    const auto end=std::chrono::steady_clock::now();
    const auto snapshot=history.snapshot();
    if(snapshot!=std::vector<Transaction>(input.end()-capacity,input.end()))
        throw std::runtime_error("benchmark final history mismatch");
    std::uint64_t checksum=0;
    for(const auto& transaction:snapshot)
        checksum+=static_cast<std::uint64_t>(transaction.amount)+static_cast<std::uint64_t>(transaction.balance)
                 +transaction.sequence+static_cast<unsigned char>(transaction.type);
    std::cout << trial << ',' << name << ',' << capacity << ',' << updates << ','
              << std::chrono::duration<double,std::milli>(end-begin).count() << ',' << checksum << '\n';
}
int main() {
    std::vector<Transaction> input; input.reserve(updates);
    std::uint32_t state=192471019u;
    long long balance=10000000;
    for(int i=0;i<updates;++i) {
        state=state*1664525u+1013904223u;
        long long amount=state%10000u; char type=(state&16u)?'D':'W';
        balance+=(type=='D'?amount:-amount);
        input.push_back({amount,balance,static_cast<unsigned long long>(i+1),type});
    }
    std::cout << "trial,design,capacity,updates,milliseconds,checksum\n";
    for(int capacity:{10,50,1000}) for(int trial=1;trial<=5;++trial) {
        if(trial%2) {
            measure<ShiftingHistory>(trial,capacity,"shifting",input);
            measure<CircularHistory>(trial,capacity,"circular",input);
        } else {
            measure<CircularHistory>(trial,capacity,"circular",input);
            measure<ShiftingHistory>(trial,capacity,"shifting",input);
        }
    }
}
