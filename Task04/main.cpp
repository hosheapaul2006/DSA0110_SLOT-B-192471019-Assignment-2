#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>

class SavingsAccount {
    struct Transaction { long long amount; long long balance; char type; unsigned long long number; };
    std::string accountNumber;
    long long balance;
    Transaction transactions[10]{};
    int transactionCount=0;
    unsigned long long totalTransactions=0;
    unsigned long long shiftedElements=0;
    void record(long long amount,char type);
public:
    SavingsAccount(std::string number,long long openingBalance=0)
      :accountNumber(number),balance(openingBalance) {
        if(number.empty() || openingBalance<0) throw std::invalid_argument("invalid account");
    }
    long long getBalance() const { return balance; }
    int count() const { return transactionCount; }
    unsigned long long shifts() const { return shiftedElements; }
    bool deposit(long long amount);
    bool withdraw(long long amount);
    void miniStatement(std::ostream& out=std::cout) const;
};
void SavingsAccount::record(long long amount,char type) {
    if(transactionCount==10) {
        for(int i=1;i<10;++i) { transactions[i-1]=transactions[i]; ++shiftedElements; }
        --transactionCount;
    }
    transactions[transactionCount++]={amount,balance,type,++totalTransactions};
}
bool SavingsAccount::deposit(long long amount) {
    if(amount<=0 || amount>std::numeric_limits<long long>::max()-balance) return false;
    balance+=amount; record(amount,'D'); return true;
}
bool SavingsAccount::withdraw(long long amount) {
    if(amount<=0 || amount>balance) return false;
    balance-=amount; record(amount,'W'); return true;
}
void SavingsAccount::miniStatement(std::ostream& out) const {
    out << "Account " << accountNumber << " balance(paise)=" << balance << '\n';
    for(int i=0;i<transactionCount;++i) {
        const Transaction& t=transactions[i];
        out << t.number << ' ' << t.type << ' ' << t.amount << ' ' << t.balance << '\n';
    }
}
void check(bool condition,const char* label) {
    if(!condition) throw std::runtime_error(label);
}
int main() {
    SavingsAccount account("B192471019");
    check(account.count()==0 && account.getBalance()==0,"empty account");
    check(account.deposit(10000) && account.withdraw(2500) && account.getBalance()==7500,
          "deposit and withdrawal");
    check(!account.deposit(0) && !account.deposit(-1) && !account.withdraw(0) &&
          !account.withdraw(-1) && !account.withdraw(7501) && account.count()==2 && account.getBalance()==7500,
          "invalid and insufficient transactions leave state unchanged");
    check(account.withdraw(7500) && account.getBalance()==0,"withdraw exact balance");
    SavingsAccount history("HISTORY");
    for(int i=1;i<=10;++i) if(!history.deposit(100)) return 1;
    check(history.count()==10 && history.shifts()==0,"first ten require no shifts");
    if(!history.deposit(100)) return 1;
    check(history.count()==10 && history.shifts()==9,"eleventh discards oldest and shifts nine");
    if(!history.deposit(100)) return 1;
    std::ostringstream actual,expected;
    history.miniStatement(actual);
    expected << "Account HISTORY balance(paise)=1200\n";
    for(int i=3;i<=12;++i) expected << i << " D 100 " << i*100 << '\n';
    check(actual.str()==expected.str(),"last ten are transactions 3 through 12 in chronological order");
    check(history.shifts()==18,"two full-buffer insertions move eighteen records");
    SavingsAccount large("LARGE",std::numeric_limits<long long>::max());
    check(!large.deposit(1) && large.count()==0,"balance overflow rejected");
    bool rejected=false;
    try { SavingsAccount invalid("",-1); } catch(const std::invalid_argument&) { rejected=true; }
    check(rejected,"invalid opening account rejected");
    history.miniStatement();
}
