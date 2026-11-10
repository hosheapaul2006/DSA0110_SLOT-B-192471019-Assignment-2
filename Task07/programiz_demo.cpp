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

#include <iostream>
int main() {
    ShiftingHistory original(10);
    CircularHistory redesigned(10);
    for(int i=1;i<=12;++i) {
        Transaction t{100,i*100,static_cast<unsigned long long>(i),'D'};
        original.push(t); redesigned.push(t);
    }
    const auto a=original.snapshot(),b=redesigned.snapshot();
    if(a!=b) throw std::runtime_error("retained histories differ");
    std::cout << "Original retained transactions:";
    for(const auto& t:a) std::cout << ' ' << t.sequence;
    std::cout << "\nRedesigned retained transactions:";
    for(const auto& t:b) std::cout << ' ' << t.sequence;
    std::cout << "\nBoth balances: " << a.back().balance << " paise\n";
}
