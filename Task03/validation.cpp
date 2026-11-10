#include <cmath>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <type_traits>

struct Parcel { double kilograms; bool express=false; bool insured=false; };
struct Quote { int rupees; const char* selected; };
int parcelCharge(const Parcel& parcel) {
    if(!std::isfinite(parcel.kilograms) || parcel.kilograms<=0 || parcel.kilograms>1000000)
        throw std::invalid_argument("weight must be finite and in (0,1000000] kg");
    return static_cast<int>(std::ceil(parcel.kilograms))*50
         + (parcel.express?30:0) + (parcel.insured?20:0);
}
Quote charge(double weight,bool express=false,bool insured=false) {
    return {parcelCharge({weight,express,insured}),"double kilograms"};
}
Quote charge(int grams,bool express=false,bool insured=false) {
    return {parcelCharge({grams/1000.0,express,insured}),"int grams"};
}
Quote charge(const Parcel& parcel) { return {parcelCharge(parcel),"Parcel"}; }
template<class Weight>
int templateCharge(Weight weight,bool express=false,bool insured=false) {
    static_assert(std::is_same_v<Weight,int> || std::is_floating_point_v<Weight>,
                  "use int grams or floating-point kilograms");
    if constexpr(std::is_same_v<Weight,int>) return parcelCharge({weight/1000.0,express,insured});
    else return parcelCharge({static_cast<double>(weight),express,insured});
}
void check(bool condition,const char* label) {
    if(!condition) throw std::runtime_error(label);
    std::cout << "PASS " << label << '\n';
}
int main() {
    const Quote quotes[]={charge(2),charge(2.0f),charge(2.5),charge(1500,true),
                          charge(1.0,false,true),charge(Parcel{1.2,true,true})};
    const char* labels[]={"charge(2)","charge(2.0f)","charge(2.5)","charge(1500,true)",
                          "charge(1.0,false,true)","charge(Parcel{1.2,true,true})"};
    const char* kinds[]={"int grams","double kilograms","double kilograms","int grams","double kilograms","Parcel"};
    const int expected[]={50,100,150,130,70,150};
    bool matched=true;
    for(int i=0;i<6;++i) {
        std::cout << labels[i] << ": " << quotes[i].selected << " = " << quotes[i].rupees << '\n';
        matched=matched && quotes[i].rupees==expected[i] && std::string(quotes[i].selected)==kinds[i];
    }
    check(matched,"six overload selections");
    check(templateCharge(1500,true)==130 && templateCharge(2.0f)==100 &&
          parcelCharge({1.2,true,true})==150 && charge(1000).rupees==50 && charge(1001).rupees==100,
          "pricing equivalent alternatives");
    int rejected=0;
    for(double weight : {0.0,-1.0,1000001.0,std::numeric_limits<double>::infinity(),
                         std::numeric_limits<double>::quiet_NaN()}) {
        try { charge(weight); } catch(const std::invalid_argument&) { ++rejected; }
    }
    try { charge(-2); } catch(const std::invalid_argument&) { ++rejected; }
    check(rejected==6,"invalid weights rejected");
}
