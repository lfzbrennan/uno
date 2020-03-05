#include "number.hpp"

#include <boost/multiprecision/cpp_dec_float.hpp>

using boost::multiprecision::cpp_dec_float_100;
using boost::lexical_cast;

std::string rational_repr_fraction(const rational_number& num) {
    // check edge cases
    if (num.type == zero) return "0";
    if (num.type == undefined) return "undef";

    // calculate and return
    return lexical_cast<std::string>(num.numerator) + "/" + lexical_cast<std::string>(num.denominator);
}

std::string rational_repr_decimal(const rational_number& num) {
    // check edge cases
    if (num.type == zero) return "0";
    if (num.type == undefined) return "undef";

    // calculate and return
    cpp_dec_float_100 out = static_cast<cpp_dec_float_100>(num.numerator) / static_cast<cpp_dec_float_100>(num.denominator);
    return lexical_cast<std::string>(out);
}
