#ifndef BIGINTEGER_H
#define BIGINTEGER_H

#include <bigintegers.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>

using std::cin;
using std::cout;
using std::endl;
using std::pair;
using std::string;
using std::stringstream;

const size_t MAX = 50000;

bool Biginteger::is_valid_string(const string& value) const {
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

inline int Biginteger::char_to_int(char c) const {
    return c - '0';
}

int Biginteger::compare_digit_string(const string& a, const string& b) const {
    if (a == b) return 0;

    if (a.length() > b.length())
        return 1;
    else if (b.length() > a.length())
        return -1;
    else
        return a.compare(b);
}

bool Biginteger::equals(const Biginteger& a, const Biginteger& b) const {
    return a.value == b.value && a.sign == b.sign;
}

bool Biginteger::greater(const Biginteger& a, const Biginteger& b) const {
    if (a.sign && !b.sign)
        return true;

    if (!a.sign && b.sign)
        return false;

    if (a.value.length() == b.value.length()) {
        if (a.value.compare(b.value) > 0)
            return true;
        else
            return false;
    }

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
}

string Biginteger::add(const string& a, const string& b) const {
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

string Biginteger::multiply(const string& a, const string& b) const {
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

string Biginteger::subtract(const string& a, const string& b) const {
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

pair<string, string> Biginteger::divide(const string& a, const string& b) const {
    if (a.length() < b.length() || (a.length() == b.length() && a.compare(b) < 0)) {
        return {"0", a};
    }

    if (a == b) {
        return {"1", "0"};
    }

    if (b == "1") {
        return {a, "0"};
    }

    string div, first_div, resto;

    size_t cont = 0;
    while (compare_digit_string(first_div, b) < 0) {
        first_div += a[cont];
        cont++;
    }

    for (long long int i = first_div.length() - 1; i < (long long)a.length(); i++) {
        if (i != (long long)first_div.length() - 1)
            resto += a[i];
        else
            resto = first_div;

        while (resto[0] == '0' && resto.length() != 1)
            resto.erase(0, 1);

        cont = 0;
        while (compare_digit_string(resto, b) >= 0) {
            resto = subtract(resto, b);
            cont++;
        }

        div += std::to_string(cont);
    }

    return {div, subtract(a, multiply(b, div))};
}

Biginteger::Biginteger(const string& number) {
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

Biginteger::Biginteger(const string& value, bool sign) {
    if (!is_valid_string(value))
        throw invalid_string{"Error invalid string."};

    this->value = value;
    this->sign = sign;
}

Biginteger::Biginteger(const long long int& number) {
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

string Biginteger::get_value() const {
    return value;
}

bool Biginteger::get_sign() const {
    return sign;
}

void Biginteger::set_value(const string& value) {
    if (!is_valid_string(value))
        throw invalid_string{"Error invalid string."};

    this->value = value;
}

void Biginteger::set_sign(bool sign) {
    this->sign = sign;
}

Biginteger Biginteger::operator*(const Biginteger& b) const {
    Biginteger res;

    res.set_value(multiply(value, b.value));
    res.set_sign(sign == b.sign);

    return res;
}

Biginteger Biginteger::operator+(const Biginteger& b) const {
    Biginteger res;

    if (sign && b.sign)
        res.value = add(value, b.value);

    if (!sign && !b.sign) {
        res.value = add(value, b.value);
        res.sign = false;
    }

    if (sign != b.sign) {
        const Biginteger &greater_bigint = absolute() >= b.absolute() ? (*this) : b,
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

Biginteger Biginteger::operator-(const Biginteger& b) const {
    Biginteger temp{b.value, b.sign ? false : true};
    return (*this) + temp;
}

Biginteger Biginteger::operator/(const Biginteger& b) const {
    if (b.value == "0")
        throw std::runtime_error("Math error: Attempted to divide by Zero\n");

    Biginteger res;

    res.value = divide(value, b.value).first;
    res.sign = (sign == b.sign);

    if (res.value == "0" && !res.sign)
        res.sign = true;

    return res;
}

Biginteger Biginteger::operator%(const Biginteger& b) const {
    if (b.value == "0")
        throw std::runtime_error("Math error: Attempted to divide by Zero\n");

    Biginteger res;

    res.value = divide(value, b.value).second;
    res.sign = (sign == b.sign);

    if (res.value == "0" && !res.sign)
        res.sign = true;

    return res;
}

Biginteger& Biginteger::operator+=(const Biginteger& b) {
    (*this) = (*this) + b;
    return (*this);
}

Biginteger& Biginteger::operator-=(const Biginteger& b) {
    (*this) = (*this) - b;
    return (*this);
}

Biginteger& Biginteger::operator*=(const Biginteger& b) {
    (*this) = (*this) * b;
    return (*this);
}

Biginteger& Biginteger::operator/=(const Biginteger& b) {
    (*this) = (*this) / b;
    return (*this);
}

Biginteger& Biginteger::operator%=(const Biginteger& b) {
    (*this) = (*this) % b;
    return (*this);
}

Biginteger& Biginteger::operator++() {
    return (*this) += 1;
}

Biginteger Biginteger::operator++(int) {
    Biginteger before = (*this);

    (*this) += 1;

    return before;
}

Biginteger& Biginteger::operator--() {
    return (*this) -= 1;
}

Biginteger Biginteger::operator--(int) {
    Biginteger before = (*this);

    (*this) -= 1;

    return before;
}

Biginteger Biginteger::operator-() const {
    return (*this) * -1;
}

void Biginteger::operator=(const Biginteger& b) {
    value = b.value;
    sign = b.sign;
}

bool Biginteger::operator>(const Biginteger& b) const {
    return !equals((*this), b) && greater((*this), b);
}

bool Biginteger::operator<(const Biginteger& b) const {
    return !equals((*this), b) && !greater((*this), b);
}

bool Biginteger::operator>=(const Biginteger& b) const {
    return equals((*this), b) || greater((*this), b);
}

bool Biginteger::operator<=(const Biginteger& b) const {
    return equals((*this), b) || !greater((*this), b);
}

bool Biginteger::operator==(const Biginteger& b) const {
    return equals((*this), b) && sign == b.sign;
}

bool Biginteger::operator!=(const Biginteger& b) const {
    return !equals((*this), b) || sign != b.sign;
}

Biginteger::operator string() const {
    return (sign ? "" : "-") + value;
}

Biginteger Biginteger::absolute() const {
    Biginteger res{value, true};
    return res;
}

void Biginteger::print() const {
    cout << (sign ? "" : "-") << value << endl;
}

#endif