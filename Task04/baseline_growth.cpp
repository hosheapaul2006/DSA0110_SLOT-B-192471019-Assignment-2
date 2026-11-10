#include <chrono>
#include <cstdint>
#include <iostream>
#include <vector>

// Original shifting strategy with variable capacity for the growth experiment.
int main() {
    constexpr int updates=100000;
    std::cout << "capacity,updates,shift_assignments,milliseconds,checksum\n";
    for(int capacity:{10,50,1000}) {
        std::vector<long long> records(static_cast<std::size_t>(capacity),0);
        std::uint64_t assignments=0;
        const auto start=std::chrono::steady_clock::now();
        for(int i=1;i<=updates;++i) {
            for(int j=1;j<capacity;++j) { records[j-1]=records[j]; ++assignments; }
            records[capacity-1]=i;
        }
        const auto stop=std::chrono::steady_clock::now();
        long long checksum=0; for(long long record:records) checksum+=record;
        const long long expected=static_cast<long long>(capacity)*(2LL*updates-capacity+1)/2;
        if(checksum!=expected || assignments!=static_cast<std::uint64_t>(updates)*(capacity-1)) return 1;
        std::cout << capacity << ',' << updates << ',' << assignments << ','
                  << std::chrono::duration<double,std::milli>(stop-start).count() << ',' << checksum << '\n';
    }
}
