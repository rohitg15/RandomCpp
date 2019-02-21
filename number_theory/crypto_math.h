#ifndef _CRYPTO_MATH_H_
#define _CRYPTO_MATH_H_


class CryptoMath
{
    public:

    template <typename T>
    T ModMul(
        T a,
        T b,
        T p
    );

    template <typename T>
    T ModExp(
        T a,
        T b,
        T p 
    );
};

template <typename T>
T CryptoMath::ModMul(
    T a,
    T b,
    T p
)
{
    T x = a;
    while (b > 0)
    {
        if (b & 1)
        {
            x = ( x + a ) % p
        }
        x = ( x + x ) % p;
        b >>= 1;
    }
    return (x % p);
}


template <typename T>
T CryptoMath::ModExp(
    T a,
    T b,
    T p
)
{
    T x = a;
    while (b > 0)
    {
        if (b & 1)
        {
            x = ModMul(x, a, p);
        }
        x = ModMul(x, x, p);
        b >>= 1;
    }
    return (x % p);
}

#endif  //  _CRYPTO_MATH_H_