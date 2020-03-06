#include <boost/multiprecision/cpp_int.hpp>

#include "lib/number.hpp"
#include "lib/rational_repr.cpp"
#include "lib/rational_misc.cpp"
#include "lib/rational_operations.cpp"

#include "parse/god_parse.cpp"

#include "config.hpp"

#include <iostream>
#include <vector>

#include <stdio.h>

typedef std::vector<rational_number> rational_vec;



using namespace std;


int main(int argc, char** argv) {
    rational_number n1;
    rational_number n2;

    n1.type = negative;
    n1.numerator = 5;
    n1.denominator = 1;

    n2.type = positive;
    n2.numerator = 3;
    n2.denominator = 1;

    cout << rational_repr_fraction(rational_multiply(n1, n2)) << endl;
    cout << rational_repr_decimal(rational_divide(n1, n2)) << endl;

}
