#include "rational_repr.hpp"

#include <iostream>
using namespace std;

uno_int max_int_repr = uno_int(100000000000);

string rational_repr_fraction(const rat& num) {
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

string rational_repr_decimal(const rat& num) {
    switch(num.type) {
        case zero:
            return "0";
        case undefined:
            return "undef";
        case positive:
            return lexical_cast<string>(numeric_cast<uno_float>(num.numerator) / numeric_cast<uno_float>(num.denominator));
        case negative:
            return "-" + lexical_cast<string>(numeric_cast<uno_float>(num.numerator) / numeric_cast<uno_float>(num.denominator));
    }
}

string print_rat(const rat& num) {
    if (num.numerator > max_int_repr || num.denominator > max_int_repr) return rational_repr_decimal(num);
    return rational_repr_fraction(num);
}
