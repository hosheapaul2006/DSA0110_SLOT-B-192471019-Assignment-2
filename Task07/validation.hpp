#ifndef VALIDATION_HPP
#define VALIDATION_HPP
#include "history.hpp"
#include <cstdint>
#include <deque>
#include <iostream>
template<class History>
void validate(const char* name) {
    bool invalid=false;
    try { History zero(0); } catch(const std::invalid_argument&) { invalid=true; }
    if(!invalid) throw std::runtime_error("zero capacity was accepted");
    std::cout << "PASS " << name << " zero capacity rejected\n";
    for(std::size_t capacity:{1u,10u,50u,1000u}) {
        History history(capacity);
        std::deque<Transaction> oracle;
        if(!history.snapshot().empty()) throw std::runtime_error("nonempty new history");
        std::uint32_t state=192471019u;
        long long balance=0;
        for(unsigned long long i=1;i<=2500;++i) {
            state=state*1664525u+1013904223u;
            long long amount=state%10000u;
            char type=(state&16u)?'D':'W';
            balance+=(type=='D'?amount:-amount);
            Transaction transaction{amount,balance,i,type};
            history.push(transaction); oracle.push_back(transaction);
            if(oracle.size()>capacity) oracle.pop_front();
            const auto snapshot=history.snapshot();
            if(snapshot!=std::vector<Transaction>(oracle.begin(),oracle.end()))
                throw std::runtime_error("history differs from independent deque oracle");
        }
        std::cout << "PASS " << name << " capacity=" << capacity << " all 2500 snapshots match deque oracle\n";
    }
}
#endif
