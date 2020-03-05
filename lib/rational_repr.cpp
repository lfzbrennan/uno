#include "number.hpp"

#include <boost/multiprecision/cpp_dec_float.hpp>

using boost::multiprecision::cpp_dec_float_100;
using boost::lexical_cast;

std::string rational_repr_fraction(const rational_number& num) {
    switch(num.type) {
        case zero:
            return "0";
        case undefined:
            return "undef";
        case positive:
            return lexical_cast<std::string>(num.numerator) + "/" + lexical_cast<std::string>(num.denominator);
        case negative:
            return "-" + lexical_cast<std::string>(num.numerator) + "/" + lexical_cast<std::string>(num.denominator);
    }
}

std::string rational_repr_decimal(const rational_number& num) {
    switch(num.type) {
        case zero:
            return "0";
        case undefined:
            return "undef";
        case positive:
            return lexical_cast<std::string>(static_cast<cpp_dec_float_100>(num.numerator) / static_cast<cpp_dec_float_100>(num.denominator));
        case negative:
            return "-" + lexical_cast<std::string>(static_cast<cpp_dec_float_100>(num.numerator) / static_cast<cpp_dec_float_100>(num.denominator));
    }
}
