#include "factorization.h"
#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>
#include "crypto_math.h"

namespace BigNum = boost::multiprecision;


int main()
{
    std::cout << Factorization<BigNum::cpp_int>::PollardsRho(23) << std::endl;

    assert( 0 == CryptoMath::ModMul<BigNum::cpp_int>(10, 0, 5) );
    assert( 0 == CryptoMath::ModMul<BigNum::cpp_int>(10, 1, 5) );
    assert( 0 == CryptoMath::ModMul<BigNum::cpp_int>(10, 2, 5) );
    assert( 1 == CryptoMath::ModMul<BigNum::cpp_int>(3, 7, 5) );
    assert( 1 == CryptoMath::ModExp<BigNum::cpp_int>(10, 0, 5) );
    assert( 0 == CryptoMath::ModExp<BigNum::cpp_int>(10, 1, 5) );
    assert( 4 == CryptoMath::ModExp<BigNum::cpp_int>(3, 7, 5) );

    return 0;
}