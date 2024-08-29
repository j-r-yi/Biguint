
#include <cassert>
#include <algorithm>
#include <cctype>
#include "Biguint.h"
#include <cmath>
#include <iostream>


// CONSTRUCTORS

Biguint::Biguint(std::size_t n, size_type c)
{

    size_type nsize = ceil(log(n+1.0)/log(10));
    _capacity = std::max(nsize, c);
    _data = new digit_type[_capacity];
    std::fill(_data, _data+_capacity, 0);

    size_type i(0);
    while (n > 0)
    {
        _data[i] = n % 10;
        ++i;
        n /= 10;
    }
}

Biguint::Biguint(const std::string &s)
{
    _capacity = s.size();
    _data = new digit_type[_capacity];
    std::fill(_data, _data+_capacity, 0);

    size_type k(0);

    for (int i = s.size()-1; i >= 0; --i)
    {
        if (isdigit(s[i]))
            _data[k++] = s[i] - '0';
    }
}


Biguint::Biguint(const Biguint & b)
{
    _capacity = b._capacity;
    _data = new digit_type[_capacity];
    std::copy(b._data, b._data+b._capacity, _data);
}

Biguint::~Biguint()
{
    delete [] _data;
}

void Biguint::operator =(const Biguint & b)
{
    if (this == &b)
        return;
    if (_capacity != b._capacity)
    {
        delete [] _data;
        _capacity = b._capacity;
        _data = new digit_type[_capacity];
    }
    std::copy(b._data, b._data+_capacity, _data);
}

void Biguint::reserve(size_type new_capacity)
{
    if (size() > new_capacity || _capacity == new_capacity)
        return;
    digit_type *new_data = new digit_type[new_capacity];
    std::fill(new_data, new_data+new_capacity, 0);
    std::copy(_data, _data+size(), new_data);
    delete [] _data;
    _data = new_data;
    _capacity = new_capacity;
}

// CONSTANT FUNCTIONS

Biguint::digit_type Biguint::operator[](size_type pos) const
{
    if (pos >= _capacity)
        return 0;
    else
        return _data[pos];
}

Biguint::size_type Biguint::size() const
{
    size_type ans(_capacity);
    while (ans > 0 && _data[ans-1] == 0)
        --ans;
    return ans;
}



int Biguint::compare(const Biguint &n) const
{
    size_type d = size(), d2 = n.size();

    if (d > d2)
        return 1;
    if (d < d2)
        return -1;

    for (int i = d-1; i >= 0; --i)
    {
        if (_data[i] < n._data[i])
            return -1;
        if (_data[i] > n._data[i])
            return 1;
    }
    return 0;
}

// SHIFT MEMBER FUNCTIONS

void Biguint::ls(size_type n)
{
    size_type d = size();
    size_type need = n + d;
    if (need > _capacity)
        reserve(need);

    std::copy_backward(_data,_data+d, _data+need);
    std::fill(_data, _data+n, 0);
}

void Biguint::rs(size_type n)
{
    size_type d = size();
    if (n >= d)
    {
        *this = 0;
        return;
    }

    std::copy(_data+n, _data+d, _data);
    std::fill_n(_data+d-n, n, 0);
}

// ARITHMETIC MEMBER FUNCTIONS

void Biguint::operator +=(const Biguint & b)
{

    size_type newcapacity = std::max(_capacity, b._capacity) + 1;
    digit_type *newdata = new digit_type[newcapacity];
    std::fill(newdata, newdata+newcapacity, 0);

    size_type carry(0);

    for (size_type i = 0; i < newcapacity; ++i)
    {
        size_type sum = carry;
        if (i < _capacity)
            sum += _data[i];
        if (i < b._capacity)
            sum += b._data[i];
        newdata[i] = sum % 10;
        carry = sum/10;
    }

    delete[] _data;
    _capacity = newcapacity;
    _data = newdata;

}


void Biguint::operator -=(const Biguint & b)
{
    if (compare(b) == -1)
    {
        *this = 0;
        return;
    }

    size_type borrow(0);

    for (size_type i = 0; i < _capacity; ++i)
    {
        size_type t = borrow;
        if (i < b._capacity)
            t += b._data[i];

        if (_data[i] >= t)
        {
            _data[i] -= t;
            borrow = 0;
        }
        else
        {
            _data[i] += 10;
            _data[i] -= t;
            borrow = 1;
        }
    }
}

void Biguint::operator *=(digit_type d)
{
    assert(d <= 9);

    size_type newcapacity = _capacity + 1;
    digit_type *newdata = new digit_type[newcapacity];
    size_type carry(0);

    for (size_type i = 0; i < _capacity ; ++i)
    {
        size_type sum = carry + _data[i] * d;
        newdata[i] = sum % 10;
        carry = sum/10;
    }
    newdata[newcapacity-1] = carry;
    delete[] _data;
    _data = newdata;
    _capacity = newcapacity;

}


void Biguint::operator *=(const Biguint & b)
{


    size_type newcap = _capacity + b._capacity;
    Biguint ans;
    ans.reserve(newcap);
    size_type carry;
    for (size_type i = 0; i < _capacity; ++i)
    {
        size_type j;
        carry = 0;
        for (j = 0; j < b._capacity; ++j)
        {
            size_type sum = carry  + ans._data[i+j] + _data[i]*b._data[j];
            ans._data[i+j] = sum % 10;
            carry = sum / 10;
        }
        ans._data[i+j] = carry;
    }

    *this = ans;
}




void Biguint::operator /=(const Biguint & divisor)
{

    assert(divisor != 0);
    if (compare(divisor) == -1)
    {
        *this = 0;
        return;
    }

    Biguint remainder;
    remainder.reserve(1+divisor.size());
    Biguint quotient;
    quotient.reserve(size());
    for (int i = size()-1; i >= 0; --i)
    {
        remainder.ls(1);
        remainder._data[0] = _data[i];

        size_type d = 0;
        while (remainder >= divisor)
        {
            ++d;
            remainder -= divisor;
        }
        quotient._data[i] = d;
    }
    *this = quotient;
}

void Biguint::operator %=(const Biguint & divisor)
{

    assert(divisor != 0);
    if (compare(divisor) == -1)
        return;


    Biguint remainder;
    remainder.reserve(1+divisor.size());
    for (int i = size()-1; i >= 0; --i)
    {
        remainder.ls(1);
        remainder._data[0] = _data[i];
        while (remainder >= divisor)
            remainder -= divisor;
    }

    *this = remainder;
}



Biguint Biguint::operator ++()
{
    *this += 1;
    return *this;
}

Biguint Biguint::operator--()
{
    *this -= 1;
    return *this;
}

Biguint Biguint::operator++(int)
{
    Biguint ans(*this);
    *this += 1;
    return ans;
}

Biguint Biguint::operator--(int)
{
    Biguint ans(*this);
    *this -= 1;
    return ans;
}

// Nonmember I/O operators


std::ostream & operator << (std::ostream &os, const Biguint & b)
{
    if (b == 0)
        os << 0;
    else
        for (int i = b.size()-1; i >= 0; --i)
        {
            os << b[i];
        }

    return os;
}
std::istream & operator >>(std::istream & is, Biguint & b)
{
    std::string s;
    is >> s;
    b = Biguint(s);
    return is;

}


// Nonmember comparison operators

bool operator < (const Biguint &a, const Biguint & b)
{
    return (a.compare(b) == -1);
}

bool operator <= (const Biguint &a, const Biguint & b)
{
    return (a.compare(b) <= 0);
}

bool operator == (const Biguint &a, const Biguint & b)
{
    return (a.compare(b) == 0);
}

bool operator != (const Biguint &a, const Biguint & b)
{
    return (a.compare(b) != 0);
}

bool operator >= (const Biguint &a, const Biguint & b)
{
    return (a.compare(b) >= 0);
}

bool operator > (const Biguint &a, const Biguint & b)
{
    return (a.compare(b) == 1);
}

// Nomember shift operators

Biguint operator << (const Biguint & a, unsigned int n)
{
    Biguint ans(a);
    ans.ls(n);
    return ans;
}

Biguint operator >> (const Biguint & a, unsigned int n)
{
    Biguint ans(a);
    ans.rs(n);
    return ans;
}

// Nonmember arithmetic operators

Biguint operator + (const Biguint &a, const Biguint &b)
{
    Biguint ans(a);
    ans += b;
    return ans;
}

Biguint operator - (const Biguint & a, const Biguint & b)
{
    Biguint ans(a);
    ans -= b;
    return ans;

}


Biguint operator *(const Biguint & b, Biguint::size_type d)
{
    Biguint ans(b);
    ans *= d;
    return ans;
}


Biguint operator *(const Biguint &a, const Biguint & b)
{
    Biguint ans(a);
    ans *= b;
    return ans;
}


Biguint operator /(const Biguint & a, const Biguint & b)
{
    Biguint ans(a);
    ans /= b;
    return ans;
}

Biguint operator %(const Biguint & a, const Biguint & b)
{
    Biguint ans(a);
    ans %= b;
    return ans;
}
