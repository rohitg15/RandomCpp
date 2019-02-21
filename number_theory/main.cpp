#include "factorization.h"
#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>
#include "crypto_math.h"
#include "primality.h"
#include "file_helper.h"

#include <locale>
#include <codecvt>
#include <sstream>

namespace BigNum = boost::multiprecision;


int main()
{
    // test factorization using Pollard's rho
    std::cout << Factorization<BigNum::cpp_int>::PollardsRho(23) << std::endl;

    // test modular exponentiation and multiplication using repeated squaring
    assert( 0 == CryptoMath::ModMul<BigNum::cpp_int>(10, 0, 5) );
    assert( 0 == CryptoMath::ModMul<BigNum::cpp_int>(10, 1, 5) );
    assert( 0 == CryptoMath::ModMul<BigNum::cpp_int>(10, 2, 5) );
    assert( 1 == CryptoMath::ModMul<BigNum::cpp_int>(3, 7, 5) );
    assert( 1 == CryptoMath::ModExp<BigNum::cpp_int>(10, 0, 5) );
    assert( 0 == CryptoMath::ModExp<BigNum::cpp_int>(10, 1, 5) );
    assert( 2 == CryptoMath::ModExp<BigNum::cpp_int>(3, 7, 5) );

    // test primality using miller rabin
    assert( true == Primality::IsPrime<unsigned int>(23) ); 
    assert( true == Primality::IsPrime<unsigned int>(2) );
    assert( true == Primality::IsPrime<unsigned int>(3) );
    assert( true == Primality::IsPrime<unsigned int>(7) );
    
    assert( false == Primality::IsPrime<unsigned int>(9) );
    assert( false == Primality::IsPrime<unsigned int>(15) );
    
    return 0;
}