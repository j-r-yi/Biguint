#include <iostream>
#include "Bigint.h"

using namespace std;

int main()
{
    Bigint a;

    cout << Bigint(-123) << endl;
    cout << Bigint(0) << endl;
    cout << Bigint(123) << endl;
    cout << Bigint("-123") << endl;
    cout << Bigint("0") << endl;
    cout << Bigint("123") << endl;
    cout << Bigint() << endl;
    cout << "Please type -12345: ";
    cin >> a;
    cout << "a = " << a << endl;
    cout << endl;
    cout << Bigint("-12345678901234567890") + Bigint("12345678901234567890") << endl;
    cout << Bigint("12345678901234567890") + Bigint("-12345678901234567890") << endl;
    cout << Bigint("-12345678901234567890") + Bigint("1234567890123456789") << endl;
    cout << Bigint("1234567890123456789") + Bigint("-12345678901234567890") << endl;
    cout << Bigint("-1234567890123456789") + Bigint("12345678901234567890") << endl;
    cout << Bigint("12345678901234567890") + Bigint("-1234567890123456789") << endl;
    cout << Bigint("-12345678901234567890") + Bigint("-12345678901234567890") << endl;
    cout << Bigint("12345678901234567890") + Bigint("12345678901234567890") << endl;

    return 0;
}
