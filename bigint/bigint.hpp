#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <string>
#include <iostream>
// #include <bits/stdc++.h>
#include <cstdlib>

class bigint
{
    private:
        std::string value;

    public:
        bigint();
        bigint(unsigned int n);
        bigint(const bigint &src);
        ~bigint();

        std::string getValue() const;
        bigint &operator=(const bigint &src);
        bigint &operator+=(const bigint &b);
        bigint operator+(const bigint &b);

        bigint &operator++();
        bigint operator++(int);

        bigint &operator<<=(int shift); 
        bigint operator<<(int shift) const;
        bigint &operator<<=(const bigint &shift); 
        bigint operator<<(const bigint &shift) const;

        bigint &operator>>=(int shift);
        bigint operator>>(int shift) const;
        bigint &operator>>=(const bigint &shift);
        bigint operator>>(const bigint &shift) const;

        bool operator<(const bigint &b) const;
        bool operator==(const bigint &b) const;
        bool operator!=(const bigint &b) const;
        bool operator>(const bigint &b) const;
        bool operator<=(const bigint &b) const;
        bool operator>=(const bigint &b) const;
};

std::ostream &operator<<(std::ostream &os, const bigint &n);

#endif