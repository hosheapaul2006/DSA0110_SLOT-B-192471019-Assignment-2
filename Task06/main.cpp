#include <iostream>
#include <stdexcept>
#include <utility>

class Time {
    int h,m;
public:
    Time(int hour,int minute):h(hour),m(minute) {
        if(h<0 || h>23 || m<0 || m>59) throw std::invalid_argument("invalid time");
    }
    int hours() const { return h; }
    int minutes() const { return m; }
    int minutesTo(const Time& other) const {
        int delta=(h*60+m)-(other.h*60+other.m); return delta<0?-delta:delta;
    }
    bool isEarlier(const Time& other) const { return h*60+m<other.h*60+other.m; }
    friend int minutesBetween(const Time& a,const Time& b);
    friend bool earlier(const Time& a,const Time& b);
};
inline int minutesBetween(const Time& a,const Time& b) {
    int delta=(a.h*60+a.m)-(b.h*60+b.m); return delta<0?-delta:delta;
}
inline bool earlier(const Time& a,const Time& b) { return a.h*60+a.m<b.h*60+b.m; }
int getterDifference(const Time& a,const Time& b) {
    int delta=(a.hours()*60+a.minutes())-(b.hours()*60+b.minutes()); return delta<0?-delta:delta;
}
bool getterEarlier(const Time& a,const Time& b) {
    return a.hours()*60+a.minutes()<b.hours()*60+b.minutes();
}
void check(bool condition,const char* label) {
    if(!condition) throw std::runtime_error(label);
}
int main() {
    struct Test { int h1,m1,h2,m2,difference; bool firstEarlier; };
    const Test tests[]={{9,45,13,10,205,true},{12,0,12,0,0,false},{11,59,12,1,2,true},
                        {15,30,8,15,435,false},{0,0,23,59,1439,true},{23,59,0,0,1439,false}};
    for(const auto& test:tests) {
        Time a(test.h1,test.m1),b(test.h2,test.m2);
        check(minutesBetween(a,b)==test.difference && earlier(a,b)==test.firstEarlier &&
              a.minutesTo(b)==test.difference && a.isEarlier(b)==test.firstEarlier &&
              getterDifference(a,b)==test.difference && getterEarlier(a,b)==test.firstEarlier,
              "friend/member/getter agreement with hand-calculated case");
        std::cout << test.h1 << ':' << test.m1 << " to " << test.h2 << ':' << test.m2
                  << " difference=" << minutesBetween(a,b) << " earlier=" << std::boolalpha << earlier(a,b) << '\n';
    }
    int invalid=0;
    for(const auto& pair : {std::pair<int,int>{-1,0},{24,0},{0,-1},{0,60}}) {
        try { Time value(pair.first,pair.second); } catch(const std::invalid_argument&) { ++invalid; }
    }
    check(invalid==4,"invalid time fields rejected");
    std::cout << "Supplied case: " << minutesBetween(Time(9,45),Time(13,10)) << ' '
              << earlier(Time(13,10),Time(9,45)) << '\n';
}
