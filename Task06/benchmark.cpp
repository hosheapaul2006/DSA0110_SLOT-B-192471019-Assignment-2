#include <chrono>
#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <vector>

class Time {
    int h,m;
public:
    Time(int hour,int minute):h(hour),m(minute) {}
    int hours() const { return h; }
    int minutes() const { return m; }
    int minutesTo(const Time& b) const {
        int delta=(h*60+m)-(b.h*60+b.m); return delta<0?-delta:delta;
    }
    bool isEarlier(const Time& b) const { return h*60+m<b.h*60+b.m; }
    friend int inlineDifference(const Time&,const Time&);
    friend bool inlineEarlier(const Time&,const Time&);
    friend int ordinaryDifference(const Time&,const Time&);
    friend bool ordinaryEarlier(const Time&,const Time&);
};
inline int inlineDifference(const Time& a,const Time& b) {
    int delta=(a.h*60+a.m)-(b.h*60+b.m); return delta<0?-delta:delta;
}
inline bool inlineEarlier(const Time& a,const Time& b) { return a.h*60+a.m<b.h*60+b.m; }
int ordinaryDifference(const Time& a,const Time& b) {
    int delta=(a.h*60+a.m)-(b.h*60+b.m); return delta<0?-delta:delta;
}
bool ordinaryEarlier(const Time& a,const Time& b) { return a.h*60+a.m<b.h*60+b.m; }
int getterDifference(const Time& a,const Time& b) {
    int delta=(a.hours()*60+a.minutes())-(b.hours()*60+b.minutes()); return delta<0?-delta:delta;
}
bool getterEarlier(const Time& a,const Time& b) {
    return a.hours()*60+a.minutes()<b.hours()*60+b.minutes();
}
struct Pair { Time a,b; };
constexpr int calls=10000000;
template<class Operation>
long long run(const std::vector<Pair>& input,Operation operation) {
    long long checksum=0;
    for(int i=0;i<calls;++i) {
        const Pair& pair=input[static_cast<unsigned>(i)&4095u];
        checksum+=operation(pair.a,pair.b);
    }
    return checksum;
}
template<class Operation>
void measure(int trial,const char* name,const std::vector<Pair>& input,Operation operation,long long expected) {
    const auto start=std::chrono::steady_clock::now();
    const long long checksum=run(input,operation);
    const auto end=std::chrono::steady_clock::now();
    if(checksum!=expected) throw std::runtime_error("benchmark checksum mismatch");
    std::cout << trial << ',' << name << ',' << calls << ','
              << std::chrono::duration<double,std::milli>(end-start).count() << ',' << checksum << '\n';
}
int main() {
    std::vector<Pair> input; input.reserve(4096);
    std::uint32_t state=192471019u;
    for(int i=0;i<4096;++i) {
        state=state*1664525u+1013904223u; int a=static_cast<int>(state%1440u);
        state=state*1664525u+1013904223u; int b=static_cast<int>(state%1440u);
        input.push_back({Time(a/60,a%60),Time(b/60,b%60)});
    }
    auto member=[](const Time& a,const Time& b){ return a.minutesTo(b)+static_cast<int>(a.isEarlier(b)); };
    auto inlined=[](const Time& a,const Time& b){ return inlineDifference(a,b)+static_cast<int>(inlineEarlier(a,b)); };
    auto ordinary=[](const Time& a,const Time& b){ return ordinaryDifference(a,b)+static_cast<int>(ordinaryEarlier(a,b)); };
    auto getters=[](const Time& a,const Time& b){ return getterDifference(a,b)+static_cast<int>(getterEarlier(a,b)); };
    const long long expected=run(input,member); // Untimed warm-up and observable reference checksum.
    std::cout << "trial,design,calls_per_function,milliseconds,checksum\n";
    for(int trial=1;trial<=5;++trial) {
        // Rotate ordering to reduce consistent first/last thermal/cache bias.
        if(trial%2) {
            measure(trial,"friend_inline",input,inlined,expected); measure(trial,"friend_ordinary",input,ordinary,expected);
            measure(trial,"member",input,member,expected); measure(trial,"getters",input,getters,expected);
        } else {
            measure(trial,"getters",input,getters,expected); measure(trial,"member",input,member,expected);
            measure(trial,"friend_ordinary",input,ordinary,expected); measure(trial,"friend_inline",input,inlined,expected);
        }
    }
}
