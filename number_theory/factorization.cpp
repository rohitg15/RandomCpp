#include "factorization.h"
#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>

namespace BigNum = boost::multiprecision;


int main()
{
    std::cout << Factorization<BigNum::cpp_int>::PollardsRho(23) << std::endl;
    return 0;
}