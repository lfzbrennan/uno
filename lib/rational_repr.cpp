#include "rational_repr.hpp"

string rational_repr_fraction(const rational_number& num) {
    switch(num.type) {
        case zero:
            return "0";
        case undefined:
            return "undef";
        case positive:
            if (num.denominator == 1) return lexical_cast<string>(num.numerator);
            return lexical_cast<string>(num.numerator) + "/" + lexical_cast<string>(num.denominator);
        case negative:
            if (num.denominator == 1) return "-" + lexical_cast<string>(num.numerator);
            return "-" + lexical_cast<string>(num.numerator) + "/" + lexical_cast<string>(num.denominator);
    }
}

string rational_repr_decimal(const rational_number& num) {
    switch(num.type) {
        case zero:
            return "0";
        case undefined:
            return "undef";
        case positive:
            return lexical_cast<string>(static_cast<cpp_dec_float_100>(num.numerator) / static_cast<cpp_dec_float_100>(num.denominator));
        case negative:
            return "-" + lexical_cast<string>(static_cast<cpp_dec_float_100>(num.numerator) / static_cast<cpp_dec_float_100>(num.denominator));
    }
}
