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

    template <typename T>
    T BinaryGcd(
        T a,
        T b
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


template <typename T>
T CryptoMath::BinaryGcd(
    T a,
    T b
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
        return CryptoMath::BinaryGcd(b, a);
    }

    if (a == b)
    {
        return a;
    }

    T d = 1;
    while (a != b)
    {
        if (a < b)
        {
            T t = a;
            a = b;
            b = t;
        }

        if ( !(a & 1) && !(b & 1) )
        {
            d <<= 1;
            a >>= 1;
            b >>= 1;
        }
        else if ( !(a & 1) )
        {
            a >>= 1;
        }
        else if ( !(b & 1) )
        {
            b >>= 1;
        }
        else
        {
            T t = a - b;
            a = b;
            b = t;
        }
    }
    return d * a;
}

#endif  //  _CRYPTO_MATH_H_