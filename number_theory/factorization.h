#ifndef _DISCRETE_LOG_H_
#define _DISCRETE_LOG_H_

#include <cstdlib>

template<typename T>
class Factorization
{
    public:

        static T PollardsRho(
            T x
        );

    private:

        static T f(
            T x,
            T n
        );

        static T Gcd(
            T a,
            T b
        );

        static bool Egcd(
            T a,
            T b,
            std::pair<T, T>& result
        );
};

template<typename T>
T Factorization<T>::Gcd(
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
        return Gcd(b, a);
    }

    // a > b
    T r = 0;
    while (b)
    {
        r = a % b;
        a = b;
        b = r;
    }
    return a;
}

template <typename T>
bool Factorization<T>::Egcd(
    T a,
    T b,
    std::pair<T, T>& result
)
{
    if (a == 0 || b == 0)
    {
        return false;
    }

    if (a < b)
    {
        return false;
    }

    T s0 = 1, s1 = 0, s2 = 0, t0 = 0, t1 = 1, t2 = 0;
    T q = 0, r = 0;

    while (b > 0)
    {
        q = a / b;
        r = a - q * b;

        s2 = s0 - q * s1;
        t2 = t0 - q * t1;

        s0 = s1, s1 = s2;
        t0 = t1, t1 = t2;
        a = b, b = r;
    }


    // a is the gcd at this point
    result.first = s0;
    result.second = t0;

    return true;
}
    

template<typename T>
T Factorization<T>::f(
    T x,
    T n
)
{
    return ((x * x) + rand()) % n;
}


template<typename T>
T Factorization<T>::PollardsRho(
    T n
)
{
    T a = 2, b = 2;
    T factor = 0;
    do
    {
        T diff = (a > b) ? a - b : b - a;
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

#endif