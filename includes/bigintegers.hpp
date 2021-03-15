#include <string>

using std::pair;
using std::string;

struct invalid_string {
    string msg;
};

class Biginteger {
   private:
    string value;
    bool sign;

    bool is_valid_string(const string& value) const;

    inline int char_to_int(char c) const;

    int compare_digit_string(const string& a, const string& b) const;

    bool equals(const Biginteger& a, const Biginteger& b) const;

    bool greater(const Biginteger& a, const Biginteger& b) const;

    string add(const string& a, const string& b) const;

    string multiply(const string& a, const string& b) const;

    string subtract(const string& a, const string& b) const;

    pair<string, string> divide(const string& a, const string& b) const;

   public:
    Biginteger() : value{"0"}, sign{true} {}

    Biginteger(const string& number);

    Biginteger(const string& value, bool sign);

    Biginteger(const long long int& number);

    string get_value() const;

    bool get_sign() const;

    void set_value(const string& value);

    void set_sign(bool sign);

    Biginteger operator*(const Biginteger& b) const;

    Biginteger operator+(const Biginteger& b) const;

    Biginteger operator-(const Biginteger& b) const;

    Biginteger operator/(const Biginteger& b) const;

    Biginteger operator%(const Biginteger& b) const;

    Biginteger& operator+=(const Biginteger& b);

    Biginteger& operator-=(const Biginteger& b);

    Biginteger& operator*=(const Biginteger& b);

    Biginteger& operator/=(const Biginteger& b);

    Biginteger& operator%=(const Biginteger& b);

    Biginteger& operator++();    // prefix

    Biginteger operator++(int);  // postfix

    Biginteger& operator--();    // prefix

    Biginteger operator--(int);  // postfix

    Biginteger operator-() const;

    void operator=(const Biginteger& b);

    bool operator>(const Biginteger& b) const;

    bool operator<(const Biginteger& b) const;

    bool operator>=(const Biginteger& b) const;

    bool operator<=(const Biginteger& b) const;

    bool operator==(const Biginteger& b) const;

    bool operator!=(const Biginteger& b) const;

    operator string() const;

    Biginteger absolute() const;

    void print() const;
};