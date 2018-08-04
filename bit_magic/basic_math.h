#ifndef _BASIC_MATH_H_
#define _BASIC_MATH_H_

class BasicMath
{
public:
    static int Divide(
        int a,
        int b
    );

    static long long int Multiply(
        int a,
        int b
    );

    static unsigned long long AddU32(
        unsigned a,
        unsigned b,
        bool addCarry = true
    );

    static long SubU32(
        unsigned a,
        unsigned b
    );
};

#endif  //  _BASIC_MATH_H_