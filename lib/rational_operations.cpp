#include "number.hpp"
#include "rational_misc.hpp"

using boost::multiprecision::uint128_t;

rational_number multiply(rational_number r1, rational_number r2) {
    rational_number out;

    // check edge cases
    if (r1.type == zero || r2.type == zero) {
        out.type = zero;
        return out;
    } else if (r1.type == undefined|| r2.type == undefined) {
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

rational_number divide(rational_number r1, rational_number r2) {
    rational_number out;

    // check edge cases
    if (r1.type == zero || r2.type == zero) {
        out.type = zero;
        return out;
    } else if (r1.type == undefined|| r2.type == undefined) {
        out.type = undefined;
        return out;
    }

    // calculate
    uint128_t top = r1.numerator * r2.denominator;
    uint128_t bot = r1.denominator * r2.numerator;
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
