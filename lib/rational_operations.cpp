#include "rational_operations.hpp"

rational_number rational_multiply(rational_number r1, rational_number r2) {
    rational_number out;

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
    uint128_t top = r1.numerator * r2.numerator;
    uint128_t bot = r1.denominator * r2.denominator;
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

rational_number rational_divide(rational_number r1, rational_number r2) {
    uint128_t temp = r2.numerator;
    r2.numerator = r2.denominator;
    r2.denominator = temp;

    return rational_multiply(r1, r2);
}

rational_number rational_addition(rational_number r1, rational_number r2) {
    rational_number out;

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

    uint128_t r1d = r1.denominator;
    uint128_t r2d = r2.denominator;

    uint128_t common_denom = r1d * r2d;

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

rational_number rational_subtract(rational_number r1, rational_number r2) {

    if (r2.type == positive)
        r2.type = negative;

    else if (r2.type == negative)
        r2.type = positive;

    return rational_addition(r1, r2);
}
