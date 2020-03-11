#include "rational_misc.hpp"

void rational_simplify(rat& num) {
    uno_int gcd = boost::integer::gcd(num.denominator, num.numerator);
    if (gcd <= 1) return;
    num.denominator /= gcd;
    num.numerator /= gcd;
}

uno_float rat_to_large_float(rat& num) {
    return numeric_cast<uno_float >(num.numerator) / numeric_cast<uno_float >(num.numerator);
}
