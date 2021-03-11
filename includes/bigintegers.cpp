#ifndef BIGINTEGER_H
#define BIGINTEGER_H

#include <bigintegers.hpp>
#include <iostream>
#include <sstream>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::stringstream;

const size_t MAX = 50000;

bool Bigintegers::is_valid_string(const string& value) const {
    if (value.length() > MAX)
        return false;

    if (value[0] == '+' || value[0] == '-') {
        for (const auto& elem : value.substr(1))
            if (!isdigit(elem))
                return false;
    } else {
        for (const auto& elem : value)
            if (!isdigit(elem))
                return false;
    }

    return true;
}

inline int Bigintegers::char_to_int(char c) const {
    return c - '0';
}

bool Bigintegers::equals(const Bigintegers& a, const Bigintegers& b) const {
    return a.value == b.value && a.sign == b.sign;
}

bool Bigintegers::greater(const Bigintegers& a, const Bigintegers& b) const {
    if (a.sign && !b.sign)
        return true;

    if (!a.sign && b.sign)
        return false;

    if (a.sign) {
        if (a.value.length() > b.value.length())
            return true;
        else
            return false;
    } else {
        if (a.value.length() < b.value.length())
            return true;
        else
            return false;
    }

    if (a.value.compare(b.value) > 0)
        return true;
    else
        return false;
}

string Bigintegers::add(const string& a, const string& b) const {
    string res;
    const string &big_string = (a.length() >= b.length()) ? a : b,
                 &small_string = (a.length() >= b.length()) ? b : a;

    size_t max_size = big_string.length();
    long long int string_diff = max_size - small_string.length();
    int resto = 0;

    for (long long int i = max_size - 1; i >= 0; i--) {
        int b_val = 0;
        long long int b_index = i - string_diff;

        if (b_index >= 0) {
            b_val = char_to_int(small_string[b_index]);
        }

        int sum = char_to_int(big_string[i]) + b_val + resto;
        resto = sum / 10;
        res.insert(0, std::to_string(sum % 10));
    }

    if (resto > 0)
        res.insert(0, std::to_string(resto));

    return res;
}

string Bigintegers::multiply(const string& a, const string& b) const {
    string res = "0";

    if (a == "0" || b == "0")
        return res;

    if (a == "1")
        return b;

    if (b == "1")
        return a;

    const string &big_string = (a.length() >= b.length()) ? a : b,
                 &small_string = (a.length() >= b.length()) ? b : a;

    for (long long int i = small_string.length() - 1; i >= 0; i--) {
        string partial_mult;
        int current_digit = char_to_int(small_string[i]), resto = 0;

        for (long long int j = big_string.length() - 1; j >= 0; j--) {
            int mult = char_to_int(big_string[j]) * current_digit + resto;
            resto = mult / 10;
            partial_mult.insert(0, std::to_string(mult % 10));
        }

        if (resto > 0)
            partial_mult.insert(0, std::to_string(resto));

        partial_mult.append(small_string.length() - i - 1, '0');
        res = add(res, partial_mult);
    }

    return res;
}

string Bigintegers::subtract(const string& a, const string& b) const {
    if (a == b)
        return "0";

    string res;
    size_t string_diff = a.length() - b.length();
    bool prestito = false;

    for (long long int i = a.length() - 1; i >= 0; i--) {
        int a_val = prestito ? char_to_int(a[i]) - 1 : char_to_int(a[i]),
            b_index = i - string_diff,
            b_val = b_index >= 0 ? char_to_int(b[b_index]) : 0;

        if (a_val < b_val) {
            prestito = true;
            a_val += 10;
        } else {
            prestito = false;
        }

        res.insert(0, std::to_string(a_val - b_val));
    }

    while (res[0] == '0' && res.length() != 1) {
        res.erase(0, 1);
    }

    return res;
}

Bigintegers::Bigintegers(const string& number) {
    if (!is_valid_string(number))
        throw invalid_string{"Error invalid string."};

    if (!isdigit(number[0])) {
        value = number.substr(1);
        sign = number[0] == '+' ? true : false;
    } else {
        value = number;
        sign = true;
    }
}

Bigintegers::Bigintegers(const string& value, bool sign) {
    if (!is_valid_string(value))
        throw invalid_string{"Error invalid string."};

    this->value = value;
    this->sign = sign;
}

Bigintegers::Bigintegers(const long long int& number) {
    stringstream ss;
    string s;

    ss << number;
    ss >> s;

    if (!isdigit(s[0])) {
        value = s.substr(1);
        sign = s[0] == '+' ? true : false;
    } else {
        value = s;
        sign = true;
    }
}

string Bigintegers::get_value() const {
    return value;
}

bool Bigintegers::get_sign() const {
    return sign;
}

void Bigintegers::set_value(const string& value) {
    if (!is_valid_string(value))
        throw invalid_string{"Error invalid string."};

    this->value = value;
}

void Bigintegers::set_sign(bool sign) {
    this->sign = sign;
}

Bigintegers Bigintegers::operator*(const Bigintegers& b) const {
    Bigintegers res;

    res.set_value(multiply(value, b.value));
    res.set_sign(sign == b.sign);

    return res;
}

Bigintegers Bigintegers::operator+(const Bigintegers& b) const {
    Bigintegers res;

    if (sign && b.sign)
        res.value = add(value, b.value);

    if (!sign && !b.sign) {
        res.value = add(value, b.value);
        res.sign = false;
    }

    if (sign != b.sign) {
        const Bigintegers &greater_bigint = absolute() >= b.absolute() ? (*this) : b,
                          &smaller_bigint = absolute() >= b.absolute() ? b : (*this);

        res.value = subtract(greater_bigint.value, smaller_bigint.value);

        if (!greater_bigint.sign) {
            res.sign = false;
        }
    }

    if (res.value == "0" && !res.sign)
        res.sign = true;

    return res;
}

Bigintegers Bigintegers::operator-(const Bigintegers& b) const {
    Bigintegers temp{b.value, b.sign ? false : true};
    return (*this) + temp;
}

void Bigintegers::operator+=(const Bigintegers& b) {
    (*this) = (*this) + b;
}

void Bigintegers::operator-=(const Bigintegers& b) {
    (*this) = (*this) - b;
}

void Bigintegers::operator*=(const Bigintegers& b) {
    (*this) = (*this) * b;
}

void Bigintegers::operator=(const Bigintegers& b) {
    value = b.value;
    sign = b.sign;
}

bool Bigintegers::operator>(const Bigintegers& b) const {
    return !equals((*this), b) && greater((*this), b);
}

bool Bigintegers::operator<(const Bigintegers& b) const {
    return !equals((*this), b) && !greater((*this), b);
}

bool Bigintegers::operator>=(const Bigintegers& b) const {
    return equals((*this), b) || greater((*this), b);
}

bool Bigintegers::operator<=(const Bigintegers& b) const {
    return equals((*this), b) || !greater((*this), b);
}

bool Bigintegers::operator==(const Bigintegers& b) const {
    return equals((*this), b) && sign == b.sign;
}

bool Bigintegers::operator!=(const Bigintegers& b) const {
    return !equals((*this), b) || sign != b.sign;
}

Bigintegers Bigintegers::absolute() const {
    Bigintegers res{value, true};
    return res;
}

void Bigintegers::print() const {
    cout << (sign ? '+' : '-') << value << endl;
}

#endif