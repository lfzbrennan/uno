#include "number.hpp"
#include "rational_misc.hpp"

#include <numeric>

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/integer/common_factor.hpp>

#include <iostream>
using namespace std;

using boost::multiprecision::uint128_t;

void rational_simplify(rational_number& num) {
    uint128_t gcd = boost::integer::gcd(num.denominator, num.numerator);
    if (gcd <= 1) return;
    num.denominator /= gcd;
    num.numerator /= gcd;
}
