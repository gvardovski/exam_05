#include "bigint.hpp"

bigint::bigint() : value("0") {}

bigint::bigint(unsigned long long n)
{
    while (n)
    {
        value.push_back(n % 10);
        n /= 10;
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
    std::string value = n.getValue();
    for (int i = value.length() - 1; i >= 0; i--)
        os << value[i];
    return os;
}