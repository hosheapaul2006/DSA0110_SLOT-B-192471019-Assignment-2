#include <iostream> 
 
class Time { 
    int h, m; 
 
public: 
    Time(int hh, int mm) : h(hh), m(mm) {} 
    friend int minutesBetween(const Time& a, const Time& b); 
    friend bool earlier(const Time& a, const Time& b); 
}; 
 
int minutesBetween(const Time& a, const Time& b) 
{ 
    int delta = (a.h * 60 + a.m) - (b.h * 60 + b.m);
    return delta < 0 ? -delta : delta;
} 
 
bool earlier(const Time& a, const Time& b) 
{ 
    return a.h * 60 + a.m < b.h * 60 + b.m;
} 
 
int main() 
{ 
    Time departure(9, 45), arrival(13, 10); 
    std::cout << minutesBetween(departure, arrival) << ' ' 
              << std::boolalpha << earlier(arrival, departure) << '\n'; 
}
