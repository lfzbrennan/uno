#include "rational_repr.hpp"

#include <iostream>
using namespace std;

// max size of numerator or denominator to display
uno_int max_int_repr = lexical_cast<uno_int>("1000000000000");

// returns fration string representation of number
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

// returns decimal string representaiton of number -> uses rat_to_dec_string helper function
string rational_repr_decimal(rat& num) {
    switch(num.type) {
        case zero:
            return "0";
        case undefined:
            return "undef";
        case positive:
            return rat_to_dec_string(num);
            //return lexical_cast<string>(numeric_cast<uno_float>(num.numerator) / numeric_cast<uno_float>(num.denominator));
        case negative:
            return "-" + rat_to_dec_string(num);
            //return "-" + lexical_cast<string>(numeric_cast<uno_float>(num.numerator) / numeric_cast<uno_float>(num.denominator));
    }
}

// default print rat functions. decides to print either fraction or decimal form based on string length
string print_rat(rat& num) {
    if (num.numerator > max_int_repr || num.denominator > max_int_repr) return rational_repr_decimal(num);
    return rational_repr_fraction(num);
}
