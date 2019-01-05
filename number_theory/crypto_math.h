#ifndef _CRYPTO_MATH_H_
#define _CRYPTO_MATH_H_


class CryptoMath
{

public:
    template <typename T>
    static T ModMul(
        T a,
        T b,
        T p
    );

    template <typename T>
    static T ModExp(
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
    T x = 0, y = a;
    while (b)
    {
        if (b & 1)
        {
            x = (x + y) % p;
        }
        y = (y + y) % p;
        b >>= 1;
    }
    return x % p;
}

template <typename T>
T CryptoMath::ModExp(
    T a,
    T b,
    T p
)
{
    T x = 1, y = a;
    while (b)
    {
        if (b & 1)
        {
            x = ModMul(x, y, p);
        }
        x = ModMul(x, x, p);
        b >>= 1;
    }
    return x % p;
}

#endif  //  _CRYPTO_MATH_H_