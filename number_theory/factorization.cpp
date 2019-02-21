#include "factorization.h"
#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>
#include <vector>
#include "crypto_math.h"
// #include "codes.h"

// namespace BigNum = boost::multiprecision;


int main()
{
    std::cout << Factorization<BigNum::cpp_int>::PollardsRho(23) << std::endl;

    std::cout << CryptoMath<BigNum::cpp_int>(3, 4) << std::endl;

    // std::vector<uint8_t> buf{0x01, 0x02, 0x00};
    // Code ch;
    // std::cout << static_cast<uint32_t>(ch.Crc8Precomputed(buf)) << std::endl;
    // std::cout << static_cast<uint32_t>(Code::Crc8(buf));
    return 0;
}