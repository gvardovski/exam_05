#include "bigint.hpp"

bigint::bigint() : value("0") {}

bigint::bigint(unsigned int n)
{
    if (n == 0)
        value = "0";
    else {
        while (n)
        {
            value.push_back('0' + (n % 10));
            n /= 10;
        }
    }
}

bigint::bigint(const bigint &src) {*this = src;}

bigint::~bigint() {}

std::string bigint::getValue() const {return value;}

bigint &bigint::operator=(const bigint &src)
{
    if (this != &src)
        value = src.value;
    return *this;
}

std::ostream &operator<<(std::ostream &os, const bigint &n)
{
    std::string s = n.getValue();
    for (int i = s.length() - 1; i >= 0; i--)
        os << s[i];
    return os;
}

bigint &bigint::operator+=(const bigint &b)
{
    int t = 0, sum;
    size_t la = this->value.length();
    size_t lb = b.value.length();
    if (lb > la)
        this->value.append(lb - la, '0');
    la = this->value.length();
    for (size_t i = 0; i < la; i++)
    {
        if (i < lb)
            sum = (this->value[i] - '0') + (b.value[i] - '0') + t;
        else
            sum = (this->value[i] - '0') + t;
        t = sum / 10;
        this->value[i] = sum % 10 + '0';
    }
    if (t)
        this->value.push_back(t + '0');
    return *this;
}  

bigint bigint::operator+(const bigint &b)
{
    bigint tmp;
    tmp = *this;
    return tmp += b;
}

bigint &bigint::operator++()
{
    int i, n = value.size();
    for (i = 0; i < n && value[i] == '9';i++)
        value[i] = '0';
    if(i == n)
        value.push_back('1');
    else
        value[i]++;
    return *this;
}

bigint bigint::operator++(int)
{
    bigint tmp(*this);
    ++(*this);
    return tmp;
}

bigint &bigint::operator<<=(int shift) 
{
    if (value != "0" && shift > 0)
        value.insert(0, shift, '0');
    return *this;
}

bigint bigint::operator<<(int shift) const
{
    bigint tmp(*this);
    tmp <<= shift;
    return tmp;
}

bigint &bigint::operator<<=(const bigint &shift)
{
    std::string s = shift.getValue();
    int sh = 0;
    for (int i = s.length() - 1; i >= 0; i--)
        sh = sh * 10 + (s[i] - '0');
    return *this <<= sh;
}

bigint bigint::operator<<(const bigint &shift) const
{
    bigint tmp(*this);
    tmp <<= shift;
    return tmp;
}

bigint &bigint::operator>>=(int shift)
{
    if (value != "0" && shift > 0 && shift < (int)value.size())
        value.erase(0, shift);
    else if (shift >= (int)value.size())
        value = "0";
    return *this;
}

bigint bigint::operator>>(int shift) const
{
    bigint tmp(*this);
    tmp >>= shift;
    return tmp;
}

bigint &bigint::operator>>=(const bigint &shift)
{
    std::string s = shift.getValue();
    int sh = 0;
    for (int i = s.length() - 1; i >= 0; i--)
        sh = sh * 10 + (s[i] - '0');
    return *this >>= sh;
}

bigint bigint::operator>>(const bigint &shift) const
{
    bigint tmp(*this);
    tmp >>= shift;
    return tmp;
}

bool bigint::operator<(const bigint &b) const
{
    if (this->value.length() != b.value.length())
        return this->value.length() < b.value.length();
    for (int i = this->value.length() - 1; i >= 0; i--)
    {
        if (this->value[i] != b.value[i])
            return this->value[i] < b.value[i];
    }
    return false;
}

bool bigint::operator==(const bigint &b) const
{
    return this->value == b.value;
}

bool bigint::operator!=(const bigint &b) const
{
    return !(*this == b);
}

bool bigint::operator>(const bigint &b) const
{
    return b < *this;
}

bool bigint::operator<=(const bigint &b) const
{
    return (*this < b || *this == b);
}

bool bigint::operator>=(const bigint &b) const
{
    return (*this > b || *this == b);
}