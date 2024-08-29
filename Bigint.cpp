#include "Bigint.h"
#include <string>
#include <cmath>
#include <iostream>

Bigint::Bigint(int n): Biguint(abs(n)), _is_neg(n<0) {}


Bigint::Bigint(const std::string & s): Biguint(s[0] == '-' ? s.substr(1):s), _is_neg(false){
    if(s[0] == '-'){
        _is_neg = true;
    }
}

int Bigint::compare(const Bigint & b) const{
    // If this is neg, b is pos, return -1
    if(_is_neg && !b._is_neg){
        return -1;
    }

    // If this is pos, b is neg, return 1
    if(!_is_neg && b._is_neg){
        return 1;
    }


    // If both are non negative, use the normal Biguint::compare()
    if(!_is_neg && !b._is_neg){
        return Biguint::compare(b);
    }


    // Comparing two negative values, reverses the results from Biguint::compare()
    if(Biguint::compare(b) == 0){
        return 0;
    }else if(Biguint::compare(b) == -1){
        return 1;
    }else{
        return -1;
    }
}


void Bigint::operator +=(const Bigint & b){

    // If one of them is negative, and they share same absolute value, then set to 0
    if(compare(b) != 0 && Biguint::compare(b) == 0){
        *this = 0;
        _is_neg = false;
        return;
    }

    // If both are negative we would add them together and retain negative sign
    if(_is_neg && b._is_neg){
        Biguint::operator+=(b);
        _is_neg = true;
        return;
    }

    // If both positive then we add normally
    if(!_is_neg && !b._is_neg){
        Biguint::operator+=(b);
        _is_neg = false;
        return;
    }


    // Implied else, if 1 of them is negative

    // EX: (3 + -5)
    if(compare(b) == 1 && Biguint::compare(b) == -1){
        Bigint temp(b);
        temp.Biguint::operator -=(*this);
        *this = temp;
        _is_neg = true;
        return;
    }

    // EX: (3 + -2)
    if(compare(b) == 1 && Biguint::compare(b) == 1){
        Biguint::operator-=(b);
        _is_neg = false;
        return;
    }

    // EX: (-3 + 2)
    if(compare(b) == -1 && Biguint::compare(b) == 1){
        Biguint::operator-=(b);
        _is_neg = true;
        return;
    }

    // EX: (-3 + 5)
    if(compare(b) == -1 && Biguint::compare(b) == -1){
        Bigint temp(b);
        temp.Biguint::operator -=(*this);
        *this = temp;
        _is_neg = false;
        return;
    }

}


std::ostream & operator << (std::ostream &os, const Bigint & b)
{
    if(b.compare(Bigint(0)) == -1){
        os << "-" << Biguint(b);
        return os;
    }
    os << Biguint(b);
    return os;
}

std::istream & operator >>(std::istream & is, Bigint & b)
{
    std::string s;
    is >> s;
    b = Bigint(s);
    return is;
}

Bigint operator + (const Bigint & a , const Bigint & b){
    Bigint ans(a);
    ans += b;
    return ans;
}
