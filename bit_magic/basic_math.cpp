#include <iostream>
#include <cstdio>
#include "basic_math.h"
#include <assert.h>
#include <limits>


int BasicMath::Divide(
    int a,
    int b
)
{
    if (b == 0)
    {
        throw std::runtime_error("Error: attempted divide by zero!");
    }

    if (a == 0 || b == 1)
    {
        return a;
    }

    int sign = ( (a < 0) ^ (b < 0) ) ? -1 : 1;
    
    size_t sa = abs(a), sb_copy = abs(b), sb = 0;

    // idea is to perform binary long-division
    int q = 0;
    while (sa >= sb_copy)
    {
        // find left-most 1 in divisor such that divisor <= dividend
        int pos = 0;
        sb = sb_copy;
        
        while (sb <= sa)
        {
            sb <<= 1;
            ++pos;
        }

        // adjust sb so that it is still < sa
        sb >>= 1;
        --pos;
        
        // remove sb from sa, set appropriate bit in quotient
        sa -= sb;
        q |= (1 << pos);
    }
    return sign * q;
}

long long int BasicMath::Multiply(
    int a,
    int b
)
{
    if (a == 0 || b == 0)
    {
        return 0;
    }
    int sign = ( (a < 0) ^ (b < 0) ) ? -1 : 1;
    long long int sa = abs(a);
    int sb = abs(b), pos = 0;

    long long int res = 0;
    while (sb > 0)
    {
        if (sb & 1)
        {
            res += (sa << pos);
        }
        ++pos;
        sb >>= 1;
    }
    return res * sign;
}

unsigned long long BasicMath::AddU32(
    unsigned a,
    unsigned b,
    bool addCarry
)
{
    unsigned long long res = 0;
    int i = 0;
    unsigned int ai = 0, bi = 0, carry = 0;
    while (a > 0 || b > 0)
    {
        ai = (a & 1);
        bi = (b & 1);
        res |= ((ai ^ bi ^ carry) << i);
        carry = (ai & bi) | (ai & carry) | (bi & carry);
        ++i;
        a >>= 1;
        b >>= 1;
    }

    // cast carry to long long to account for overflows
    if (addCarry)
    {
        res |= (static_cast<unsigned long long>(carry) << i);
    }
    
    return res;
}

long BasicMath::SubU32(
    unsigned a,
    unsigned b
)
{
    if (a < b)
    {
        throw std::runtime_error("Error: a cannot be < b!");
    }

    // truncate result of addition to 32 bits
    return (b == 0) ? a : static_cast<long>( BasicMath::AddU32(a, (~b) + 1, false) );
}


int main(int argc, char **argv)
{
    assert(1 == BasicMath::Divide(1, 1));
    assert(0 == BasicMath::Divide(1, 2));
    assert(2 == BasicMath::Divide(6, 3));
    assert(83 ==  BasicMath::Divide(1927, 23));
    assert(10 == BasicMath::Divide(200, 20));
    assert(1 == BasicMath::Divide(12, 8));
    assert(-2 == BasicMath::Divide(-6, 3));
    assert(-2 == BasicMath::Divide(6, -3));
    assert(2 == BasicMath::Divide(-6, -3));

    assert(0 == BasicMath::Multiply(0, 10));
    assert(0 == BasicMath::Multiply(-12, 0));
    assert(1 == BasicMath::Multiply(1, 1));
    assert(2 == BasicMath::Multiply(2, 1));
    assert(2 == BasicMath::Multiply(-1, -2));
    assert(-2 == BasicMath::Multiply(1, -2));
    assert( static_cast<long long int>(std::numeric_limits<int>::max()) * static_cast<long long int>(std::numeric_limits<int>::max())
     == BasicMath::Multiply(std::numeric_limits<int>::max(), std::numeric_limits<int>::max()));
    assert(-512 == BasicMath::Multiply(-64, 8));
    

    assert(0 == BasicMath::AddU32(0, 0));
    assert(2 == BasicMath::AddU32(0, 2));
    assert(2 == BasicMath::AddU32(2, 0));
    assert(10 == BasicMath::AddU32(4, 6));
    assert(198 == BasicMath::AddU32(99, 99));
    assert(
        static_cast<unsigned long long>(std::numeric_limits<unsigned>::max()) + static_cast<unsigned long long>(std::numeric_limits<unsigned>::max())
        ==
        BasicMath::AddU32(
            std::numeric_limits<unsigned>::max(),
            std::numeric_limits<unsigned>::max()
        )
    );

    assert(0 == BasicMath::SubU32(0, 0));
    assert(0 == BasicMath::SubU32(9, 9));
    assert(1 == BasicMath::SubU32(100, 99));
    assert(15 == BasicMath::SubU32(45, 30));
    assert(0 == BasicMath::SubU32(
            std::numeric_limits<unsigned>::max(),
            std::numeric_limits<unsigned>::max()
        )
    );
    return 0;
}

