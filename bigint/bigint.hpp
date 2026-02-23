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
        bigint(unsigned long long n);
        bigint(const bigint &src);
        ~bigint();

        std::string getValue() const;
        bigint &operator=(const bigint &src);

};

std::ostream &operator<<(std::ostream &os, const bigint &n);

#endif