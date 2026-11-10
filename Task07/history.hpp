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
