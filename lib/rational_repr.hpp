#ifndef _RATIONAL_REPR_HPP
#define _RATIONAL_REPR_HPP

#include "number.hpp"
#include "rational_misc.hpp"

#include <boost/multiprecision/cpp_dec_float.hpp>

using boost::lexical_cast;
using boost::numeric_cast;
using namespace std;

string rational_repr_fraction(const rat& num);
string rational_repr_decimal(rat& num);
string print_rat(rat& num);
#endif
