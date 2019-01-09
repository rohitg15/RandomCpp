#ifndef _PRIMALITY_H_
#define _PRIMALITY_H_

#include <random>
#include "crypto_math.h"

class Primality
{
public:

    template <typename T>
    static bool IsPrime(
        T p,
        unsigned int k = 100
    );

private:
    template <typename T>
    static bool MillerRabinPrimalityTest(
        T p,
        T d,
        T s
    );
};


template <typename T>
bool Primality::IsPrime(
    T p,
    unsigned int k
)
{
    T n = p - 1;
    if (n & 1)
    {
        // n is odd, which means p was even. 2 is the only even prime. 
        return (p == 2);
    }

    T d = n, s = 0;
    while (d % 2 == 0)
    {
        ++s;
        d >>= 1;
    }
    assert (p - 1 == (1 << s) * d);

    while (k--)
    {
        if (!MillerRabinPrimalityTest(p, d, s))
        {
            return false;
        }
    }
    return true;
}


template <typename T>
bool Primality::MillerRabinPrimalityTest(
    T p,
    T d,
    T s
)
{
    /*
     * Idea: if p is a prime, then n = p - 1 must be even.
     * From fermat's theorem we know that for some random a, (a ** n) % p is 1
     * i.e. (a ** (p - 1)) = 1 mod p
     * let (p - 1) = d * (2 ** s)
     * if p must be prime then there are no non-trivial square roots of unity
     * Finding successive square roots, we can observe whether any one of the 
     * intermediate values gives a value other than +/-1. If so, then a is 
     * a witness for the compositeness of p. If not, then we know that all
     * values from (a ** (p - 1)) to (a ** d) mod p where either +/-1, which
     * implies that p is a prime (with high confidence).
     */
    


    T a = 0;
    do
    {
        // replace rand() with a better rng
        a = (rand() % p);
    } while (a < 2);

    T val = CryptoMath::ModExp<T>(a, d, p);

    if (val == 1 || val == p - 1)
    {
        return true;
    }

    // repeatedly square val and check for non-trivial roots
    for (T i = 0; i < s; ++i)
    {
        T old = val;
        val = CryptoMath::ModExp<T>(val, 2, p);
        if (val == p - 1 )
        {
            // probably prime
            return true;
        }
        else if (val == 1)
        {
            // this implies that for the previous value of i (say iprev),
            // 2 ** iprev != -1 mod p; But 2 ** i = 1 mod p;
            // which means that the previous value was a non-trivial square root
            // of 1, which implies p is composite
            return false;
        }
    }
    return false;
}

#endif  //  _PRIMALITY_H_