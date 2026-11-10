#include <iostream>
#include <stdexcept>
#include <string>

class BusTicket {
    static int issued;
    static constexpr int capacity=3;
    int seat;
    std::string name;
public:
    explicit BusTicket(const std::string& passenger) : seat(0),name(passenger) {
        if(name.empty()) throw std::invalid_argument("empty passenger");
        if(issued<capacity) seat=++issued;
    }
    BusTicket(const BusTicket&)=delete; // Do not duplicate an issued seat by copying.
    BusTicket& operator=(const BusTicket&)=delete;
    int getSeat() const { return seat; }
    static int count() { return issued; }
    void print() const { std::cout << name << ": " << (seat?"Seat "+std::to_string(seat):"Waiting") << '\n'; }
};
int BusTicket::issued=0;

void check(bool condition,const char* label) {
    if(!condition) throw std::runtime_error(label);
    std::cout << "PASS " << label << '\n';
}
void createTickets(int call) {
    BusTicket tickets[2]={BusTicket("Function A"),BusTicket("Function B")};
    std::cout << "Function call " << call << ": issued=" << BusTicket::count() << '\n';
    for(const auto& ticket:tickets) {
        ticket.print();
        if(ticket.getSeat()!=0) throw std::runtime_error("capacity exceeded in function");
    }
}
int globalIssued=0;
int globalSeat() { return globalIssued<3?++globalIssued:0; }
class TicketOffice {
    int issued=0;
    int capacity;
public:
    explicit TicketOffice(int seats):capacity(seats) {
        if(seats<0) throw std::invalid_argument("negative capacity");
    }
    int issue() { return issued<capacity?++issued:0; }
    int count() const { return issued; }
};
class OfficeTicket {
    int seat;
public:
    explicit OfficeTicket(TicketOffice& office):seat(office.issue()) {}
    int getSeat() const { return seat; }
};
int main() {
    check(BusTicket::count()==0,"static counter initialized once");
    BusTicket trip[5]={BusTicket("Asha"),BusTicket("Bala"),BusTicket("Chitra"),BusTicket("Dev"),BusTicket("Eva")};
    for(const auto& ticket:trip) ticket.print();
    check(trip[0].getSeat()==1 && trip[1].getSeat()==2 && trip[2].getSeat()==3 &&
          trip[3].getSeat()==0 && trip[4].getSeat()==0 && BusTicket::count()==3,"array beyond capacity");
    createTickets(1); createTickets(2);
    check(BusTicket::count()==3,"static counter persists across function calls and destruction");
    bool invalid=false;
    try { BusTicket empty(""); } catch(const std::invalid_argument&) { invalid=true; }
    check(invalid && BusTicket::count()==3,"invalid passenger does not issue a seat");
    check(globalSeat()==1 && globalSeat()==2 && globalSeat()==3 && globalSeat()==0,"global counter alternative");
    TicketOffice busA(1),busB(2),zero(0);
    OfficeTicket a(busA),b(busB),c(busB),d(busB);
    check(a.getSeat()==1 && b.getSeat()==1 && c.getSeat()==2 && d.getSeat()==0 &&
          busA.count()==1 && busB.count()==2 && zero.issue()==0,"separate offices support independent buses");
    std::cout << "Issued: " << BusTicket::count() << '\n';
}
