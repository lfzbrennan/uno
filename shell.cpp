#include <boost/multiprecision/cpp_int.hpp>

#include "lib/number.hpp"
#include "lib/rational_repr.cpp"
#include "lib/rational_misc.cpp"

#include <iostream>
#include <vector>

typedef std::vector<rational_number> rational_vec;

using namespace std;

int main(int argc, char** argv) {

    rational_number n1;
    n1.type = positive;
    n1.numerator = 23434;
    n1.denominator = 9990;

    rational_number n2;
    n1.type = positive;
    n1.numerator = 23434;
    n1.denominator = 9990;

    cout << rational_repr_fraction(n1) << endl;

    rational_simplify(n1);

    cout << rational_repr_fraction(n1) << endl;
}
