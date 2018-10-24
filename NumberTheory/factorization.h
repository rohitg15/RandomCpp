#ifndef _DISCRETE_LOG_H_
#define _DISCRETE_LOG_H_

class Factorization
{
    public:

        static unsigned long PollardsRho(
            unsigned long long x
        );

    private:

        static unsigned long long f(
            unsigned long long x,
            unsigned long long n
        );

        static unsigned long long Gcd(
            unsigned long long a,
            unsigned long long b
        );
};

#endif