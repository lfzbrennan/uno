#include "rational_misc.hpp"

void rational_simplify(rat& num) {
    uno_int gcd = boost::integer::gcd(num.denominator, num.numerator);
    if (gcd <= 1) return;
    num.denominator /= gcd;
    num.numerator /= gcd;
}

uno_float rat_to_large_float(rat& num) {
    return numeric_cast<uno_float >(num.numerator) / numeric_cast<uno_float >(num.denominator);
}

rat large_float_to_rat(uno_float& num) {
    rat out;
    rat cur;
    string s_num = lexical_cast<string>(num);
    int dec = s_num.find('.');

    // not a decimal, can just be cast as an int
    if (dec == string::npos) {
        out.numerator = lexical_cast<uno_int>(s_num);
        out.denominator = 1;
        return out;
    }

    // iterate through string, compiling the number
    out.type = zero;
    for (int i = 0; i < s_num.size(); ++i) {
        if (i == dec || s_num[i] == '0') continue;
        cur.type = positive;
        if (dec > i) {
            cur.numerator = uno_int((int)s_num[i] - '0')
                * boost::multiprecision::pow(uno_int(10), dec - i - 1);
            cur.denominator = 1;
        } else {
            cur.numerator = ((int)s_num[i] - '0');
            cur.denominator = boost::multiprecision::pow(uno_int(10), i - dec);
        }
        out = rational_addition(out, cur);
    }
    rational_simplify(out);
    return out;
}
