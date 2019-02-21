#ifndef _PRIMALITY_H_
#define _PRIMALITY_H_

#include <random>

class Primality
{
public:
    template <typename T>
    static bool MillerRabinPrimalityTest(
        T x,
        unsigned int k = 1000
    );
};

template <typename T>
bool Primality::MillerRabinPrimalityTest(
    T x,
    unsigned int k
)
{
    /*
     *  Idea: if x is prime, then x-1 must be even. we write x-1 as (2 ** s) * d
     *  from Fermat's theorem we know that any random a ** (x - 1) = 1 mod x if x is prime
     *  additionally, there are no non-trivial square roots of unity modulo x if x is prime
     *  This implies that y = a ** (d) = 1 mod x or y * (2 ** i) = -1 mod x for some i
     *  If this is not true, then the random number a is a witness for the 'compositeness' of x
     *  Repeating this k times, with appropriately chosen k gives us a primality test with high confidence  
     */
    static_assert(x >= 2);
    T r = x - 1;
    if (r & 1)
    {
        // r is odd, thus x was even and therefore not prime
        return (x == 2);
    }

    T s = 0, d = r;
    while (d % 2 == 0)
    {
        ++s;
        d >>= 1;
    }

    while (k--)
    {
        std::default_random_engine generator;
        std::uniform_int_distribution<T> distribution(2, r);
        T a = distribution(generator);
        
    }


}

#endif  //  _PRIMALITY_H_