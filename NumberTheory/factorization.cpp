#include "factorization.h"
#include <iostream>


unsigned long long Factorization::Gcd(
    unsigned long long a,
    unsigned long long b
)
{
    if (a == 0 || b == 0)
    {
        return 0;
    }

    if (a == 1 || b == 1)
    {
        return 1;
    }

    if (a < b)
    {
        return Gcd(b, a);
    }

    // a > b
    unsigned long long r = 0;
    while (b)
    {
        r = a % b;
        a = b;
        b = r;
    }
    return a;
}

unsigned long long Factorization::f(
    unsigned long long x,
    unsigned long long n
)
{
    return ((x * x) + 1) % n;
}

unsigned long Factorization::PollardsRho(
    unsigned long long n
)
{
    unsigned long long a = 2, b = 2;
    unsigned long long diff = (a > b) ? a - b : b - a;
    unsigned long long factor = 0;
    do
    {
        unsigned long long diff = (a > b) ? a - b : b - a;
        factor = Factorization::Gcd(diff, n);
        if (factor > 1)
        {
            return factor;
        }

        a = Factorization::f(a, n);
        b = Factorization::f(b, n);
        b = Factorization::f(b, n);

    } while (b != a);

    return 0;
}


int main()
{
    std::cout << Factorization::PollardsRho(10) << std::endl;
    return 0;
}