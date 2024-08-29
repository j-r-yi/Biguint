#ifndef DYNAMIC_BIGUINT_H
#define DYNAMIC_BIGUINT_H

#include <cstdlib>
#include <string>

class Biguint
{
public:
    // TYPES and CONSTANTS
    typedef std::size_t size_type;
    typedef unsigned int digit_type;
    static const size_type DEFAULT_CAPACITY = 10;



    // CONSTRUCTORS & DESTRUCTOR

    // pre: none
    // post: creates a Biguint with inital value n (default value = 0) and initial capacity c (default value = DEFAULT_CAPACITY)
    Biguint(std::size_t n = 0, size_type c = DEFAULT_CAPACITY);

    // pre: s consists of decimal digits only
    // post: creates a Biguint whose digits are given in a string s
    //       rightmost digit of s corresponds to the least significant digit
    Biguint (const std::string & s);

    // pre: none
    // post: creates a Biguint with the same value as b
    Biguint(const Biguint & b);

    // pre: none
    // post: returns dynamically allocated memory to the heap
    ~Biguint();








    // CONSTANT FUNCTIONS
    // pre: none
    // post: returns the (pos+1)^st digit from the right of this Biguint (most digits are 0)
    digit_type operator [](size_type pos) const;

    // pre: none
    // post: returns the number of digits in this Biguint (not counting leading zeros)
    size_type size() const;

    // pre: none
    // post: return 0 if this Biguint == n
    //             -1 if this Biguint < n
    //              1 if this Biguint > n
    int compare(const Biguint & n) const;








    // MODIFICATION FUNCTIONS
    // pre: none
    // post: this Biguint has been made a copy of source; old dynamically allocated memory has been returned to the heap
    void operator = (const Biguint & source);

    // pre: none
    // post: digits of this Biguint has been left shifted by n positions
    //       the new n least significiant digits are 0
    void ls (size_type n);

    // pre: none
    // post: digits of this Biguint has been right shifted by n positions; the n least significant digits are discarded
    void rs (size_type n);

    // pre: none
    // post: a new dynamically allocated array with new_capacity digits has been allocated;
    //       the digits have been copied to the new array
    //       the old dynamic array has been returned to the heap
    //       if new_capacity < size(), nothing happens
    void reserve(size_type new_capacity);







    // ARITHMETIC member operators

    // pre: none
    // post: b has been added to this Biguint
    void operator +=(const Biguint &b);

    // pre: none
    // post: if b > this Biguint, then this Biguint is reset to 0
    //       else b is subtracted from this Biguint
    void operator -=(const Biguint & b);

    // pre: d represents a decimal digit
    // post: this Biguint has been multiplied by d
    void operator *= (digit_type d);

    // pre: none
    // post: this Biguint has been multiplied by b
    void operator *= (const Biguint & b);

    // pre: b != 0
    // post: this Biguint has been divided by b; the result is rounded down to the nearest integer
    void operator /= (const Biguint & b);

    // pre: b != 0
    // post: this Biguint has been modded by b;
    //       the new value is the remainder when dividing the original value by b
    void operator %= (const Biguint & b);

    // pre: none
    // post: this Biguint has been incremented/decremented by 1 (but capped below at 0)
    //       return value is the new value (pre)
    Biguint operator++();
    Biguint operator--();

    // pre: none
    // post: this Biguint has been incremented/decremented by 1 (but capped below at 0)
    //       return value is the original value (post)
    Biguint operator++(int);
    Biguint operator--(int);


    // pre: b has to be nonnegative
    // post: this biguint has been raised to the power of b (if b=0, this biguint = 1)
    //    void power(const digit_type & b);


    //    void factorial();

    //    void gcd(Biguint & b);

private:
    digit_type * _data;
    size_type _capacity;

    // _data[i] corresponds to the (i+1)^st rightmost digit of this Biguint (0 if it is not used)
    // _data[0] = least significant (units) digit
    // _capacity = the current size of the dynamically allocated array _data points to
};







// NON-MEMBER OPERATORS

// I/O operators
std::ostream & operator <<(std::ostream & os, const Biguint &);
std::istream & operator >>(std::istream & is, Biguint &);

// ARITHMETIC operators
Biguint operator + (const Biguint &, const Biguint &);
Biguint operator - (const Biguint &, const Biguint &);
Biguint operator * (const Biguint &, const Biguint &);
Biguint operator / (const Biguint &, const Biguint &);
Biguint operator % (const Biguint &, const Biguint &);

// COMPARISON operators
bool operator <(const Biguint &, const Biguint &);
bool operator <=(const Biguint &, const Biguint &);
bool operator ==(const Biguint &, const Biguint &);
bool operator !=(const Biguint &, const Biguint &);
bool operator >=(const Biguint &, const Biguint &);
bool operator >(const Biguint &, const Biguint &);

// SHIFT operators
Biguint operator << (const Biguint &, unsigned int);
Biguint operator >> (const Biguint &, unsigned int);



//Biguint lg(const Biguint & b);

#endif // DYNAMIC_BIGUINT_H

