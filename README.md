# bigintegers
A c++ library that implement bigintegers class/type

This library allow you to work with very large integer (Max 50000 digits).

The implemented operators are:

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
    Biginteger& operator++();   //prefix
    Biginteger operator++(int); //postfix
    Biginteger& operator--();   //prefix
    Biginteger operator--(int); //postfix
    Biginteger operator-() const;
    void operator=(const Biginteger& b);
    bool operator>(const Biginteger& b) const;
    bool operator<(const Biginteger& b) const;
    bool operator>=(const Biginteger& b) const;
    bool operator<=(const Biginteger& b) const;
    bool operator==(const Biginteger& b) const;
    bool operator!=(const Biginteger& b) const;
    operator string() const;
