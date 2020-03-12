#include "rational_operations.hpp"

rat rational_multiply(rat r1, rat r2) {
    rat out;

    // check edge cases
    if (r1.type == zero || r2.type == zero) {
        out.type = zero;
        return out;
    }

    if (r1.type == undefined|| r2.type == undefined) {
        out.type = undefined;
        return out;
    }

    // calculate
    uno_int top = r1.numerator * r2.numerator;
    uno_int bot = r1.denominator * r2.denominator;
    out.numerator = top;
    out.denominator = bot;

    // set negative
    if ((r1.type + r2.type) % 2 == 0) {
        out.type = positive;
    } else {
        out.type = negative;
    }
    //simplify and return
    rational_simplify(out);

    return out;
}

rat rational_divide(rat r1, rat r2) {
    uno_int temp = r2.numerator;
    r2.numerator = r2.denominator;
    r2.denominator = temp;

    return rational_multiply(r1, r2);
}

rat rational_addition(rat r1, rat r2) {
    rat out;

    if (r1.type == undefined || r2.type == undefined) {
        out.type = undefined;
        return out;
    }

    if (r1.type == zero) {
        out.type = r2.type;
        out.numerator = r2.numerator;
        out.denominator = r2.denominator;
        return out;
    }

    if (r2.type == zero) {
        out.type = r1.type;
        out.numerator = r1.numerator;
        out.denominator = r1.denominator;
        return out;
    }

    uno_int r1d = r1.denominator;
    uno_int r2d = r2.denominator;

    uno_int common_denom = r1d * r2d;

    r1.numerator *= r2d;
    r2.numerator *= r1d;

    if (r1.type == negative && r2.type == negative) {
        out.type = negative;
        out.numerator = r1.numerator + r2.numerator;
    }

    else if (r1.type == negative && r2.type == positive) {
        if (r1.numerator == r2.numerator) {
            out.type = zero;
            return out;
        }
        if (r2.numerator > r1.numerator) {
            out.type = positive;
            out.numerator = r2.numerator - r1.numerator;
        } else {
            out.type = negative;
            out.numerator = r1.numerator - r2.numerator;
        }
    }

    else if (r1.type == positive && r2.type == negative) {
        if (r1.numerator == r2.numerator) {
            out.type = zero;
            return out;
        }
        if (r2.numerator > r1.numerator) {
            out.type = negative;
            out.numerator = r2.numerator - r1.numerator;
        } else {
            out.type = positive;
            out.numerator = r1.numerator - r2.numerator;
        }
    }

    else if (r1.type == positive && r2.type == positive) {
        out.type = positive;
        out.numerator = r1.numerator + r2.numerator;
    }

    out.denominator = common_denom;

    rational_simplify(out);

    return out;
}

rat rational_subtract(rat r1, rat r2) {

    if (r2.type == positive)
        r2.type = negative;

    else if (r2.type == negative)
        r2.type = positive;

    return rational_addition(r1, r2);
}

rat rational_exponent(rat r1, rat r2) {
    rat out;
    out.type = positive;

    // 0^anything = 0, undef^anything = undef
    if (r1.type == zero || r1.type == undefined) {
        out.type = r1.type;
        return out;
    }
    // anything^zero = 1
    if (r2.type == zero) {
        out.type = positive;
        out.numerator = 1;
        out.denominator = 1;
        return out;
    }
    // (a/b)^-c = (b/a)^c
    if (r2.type == negative) {
        uno_int temp = r1.numerator;
        r1.numerator = r1.denominator;
        r1.denominator = temp;
    }
    // anything^1 = anything
    if (r2.type == zero && r2.numerator == 1 && r2.denominator == 1)
        return r1;

    out.numerator = boost::multiprecision::pow(r1.numerator, (int)r2.numerator);
    if (r1.denominator != 1) out.denominator = boost::multiprecision::pow(r1.denominator, (int)r2.numerator);
    else out.denominator = 1;

    if (r1.type == negative && r2.numerator % 2) out.type = negative;
    else out.type = positive;

    rational_simplify(out);

    if (r2.denominator!= 1) {
        if (out.type == negative) {
            out.type = undefined;
            return out;
        }
        uno_float estimation = rat_to_large_float(out);
        uno_float root = boost::multiprecision::pow(estimation, 1.0 / numeric_cast<double>(r2.denominator));
        out = large_float_to_rat(root);
        out.type = positive;
        rational_simplify(out);
    }
    return out;
}

rat rational_exponent_root(rat r1, rat r2) {
    uno_int temp = r2.numerator;
    r2.numerator = r2.denominator;
    r2.denominator = temp;
    return rational_exponent(r1, r2);
}
