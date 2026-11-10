#ifndef HISTORY_HPP
#define HISTORY_HPP
#include <cstddef>
#include <stdexcept>
#include <vector>
struct Transaction {
    long long amount;
    long long balance;
    unsigned long long sequence;
    char type;
    bool operator==(const Transaction& other) const {
        return amount==other.amount && balance==other.balance && sequence==other.sequence && type==other.type;
    }
};
class ShiftingHistory {
    std::vector<Transaction> data;
    std::size_t count=0;
public:
    explicit ShiftingHistory(std::size_t capacity):data(capacity) {
        if(capacity==0) throw std::invalid_argument("zero history capacity");
    }
    void push(const Transaction& transaction) {
        if(count==data.size()) {
            for(std::size_t i=1;i<count;++i) data[i-1]=data[i];
            --count;
        }
        data[count++]=transaction;
    }
    std::vector<Transaction> snapshot() const { return {data.begin(),data.begin()+count}; }
};
class CircularHistory {
    std::vector<Transaction> data;
    std::size_t count=0;
    std::size_t start=0;
public:
    explicit CircularHistory(std::size_t capacity):data(capacity) {
        if(capacity==0) throw std::invalid_argument("zero history capacity");
    }
    void push(const Transaction& transaction) {
        if(count<data.size()) data[(start+count++)%data.size()]=transaction;
        else {
            data[start]=transaction;
            start=(start+1)%data.size();
        }
    }
    std::vector<Transaction> snapshot() const {
        std::vector<Transaction> result; result.reserve(count);
        for(std::size_t i=0;i<count;++i) result.push_back(data[(start+i)%data.size()]);
        return result;
    }
};
#endif

#ifndef VALIDATION_HPP
#define VALIDATION_HPP

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

int main() { validate<ShiftingHistory>("shifting"); validate<CircularHistory>("circular"); }
