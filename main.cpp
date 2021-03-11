#include <iostream>
#include <bigintegers.hpp>

using std::cout;
using std::cin;
using std::endl;

Bigintegers factorial(size_t n) {
    Bigintegers res{1};

    while (n > 1) {
        res *= n;
        n--;
    }

    return res;
}

int main() {

    Bigintegers big_int_1{"9871298631784518925481273187263175487254912538179251825385"}, big_int_2{"123123686847553717263815276358172837"}, sum, mult, sub;

    sum = big_int_1 + big_int_2;
    mult = big_int_1 * big_int_2;
    sub = big_int_1 - big_int_2;

    sum.print();
    mult.print();
    sub.print();

    cout << ((big_int_1 > big_int_2) ? "true" : "false") << endl << endl; 

    factorial(2000).print(); 

    return 0;
}