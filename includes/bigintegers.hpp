#include <string>

using std::string;

struct invalid_string {
    string msg;
};

class Bigintegers {
   private:
    string value;
    bool sign;

    bool is_valid_string(const string& value) const;

    inline int char_to_int(char c) const;

    bool equals(const Bigintegers& a, const Bigintegers& b) const;

    bool greater(const Bigintegers& a, const Bigintegers& b) const;

    string add(const string& a, const string& b) const;

    string multiply(const string& a, const string& b) const;

    string subtract(const string& a, const string& b) const;

   public:
    Bigintegers() : value{"0"}, sign{true} {}

    Bigintegers(const string& number);

    Bigintegers(const string& value, bool sign);

    Bigintegers(const long long int& number);

    string get_value() const;

    bool get_sign() const;

    void set_value(const string& value);

    void set_sign(bool sign);

    Bigintegers operator*(const Bigintegers& b) const;

    Bigintegers operator+(const Bigintegers& b) const;

    Bigintegers operator-(const Bigintegers& b) const;

    void operator+=(const Bigintegers& b);

    void operator-=(const Bigintegers& b);

    void operator*=(const Bigintegers& b);

    void operator=(const Bigintegers& b);

    bool operator>(const Bigintegers& b) const;

    bool operator<(const Bigintegers& b) const;

    bool operator>=(const Bigintegers& b) const;

    bool operator<=(const Bigintegers& b) const;

    bool operator==(const Bigintegers& b) const;

    bool operator!=(const Bigintegers& b) const;

    Bigintegers absolute() const;

    void print() const;
};