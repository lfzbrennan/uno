#include "number.hpp"
#include "rational_misc.hpp"

#include <numeric>

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/integer/common_factor.hpp>

void rational_simplify(rational_number& num) {
    boost::multiprecision::uint128_t gcd = boost::math::gcd(num.denominator, num.numerator);
    if (gcd == 1) return;
    num.denominator /= gcd;
    num.numerator /= gcd;
}
