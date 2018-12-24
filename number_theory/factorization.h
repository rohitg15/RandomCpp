#ifndef _DISCRETE_LOG_H_
#define _DISCRETE_LOG_H_

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

template<typename T>
T Factorization<T>::f(
    T x,
    T n
)
{
    return ((x * x) + 1) % n;
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