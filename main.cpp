#include <iostream>
#include <bigintegers.hpp>

using std::cout;
using std::cin;
using std::endl;

Biginteger factorial(size_t n) {
    Biginteger res{1};

    while (n > 1) {
        res *= n;
        n--;
    }

    return res;
}

int main() {
    cout << endl;

    Biginteger big_int_1{"10"}, big_int_2{"3"}, sum, mult, sub, div, mod;

    sum = -big_int_1++ + --big_int_2;

    cout << string(big_int_1) << " " << string(big_int_2) << " " << string(sum) << endl;

    sum = big_int_1 + big_int_2;
    mult = big_int_1 * big_int_2;
    sub = big_int_1 - big_int_2;
    div = big_int_1 / big_int_2;
    mod = big_int_1 % big_int_2;

    sum.print();
    mult.print();
    sub.print();
    div.print();
    mod.print();

    cout << endl;

    cout << ((big_int_1 > big_int_2) ? "true" : "false") << endl << endl; 

    cout << string(mod) << endl;

    //factorial(2000).print(); 

    return 0;
}