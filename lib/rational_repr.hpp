#ifndef _RATIONAL_REPR_HPP
#define _RATIONAL_REPR_HPP

#include "number.hpp"

#include <boost/multiprecision/cpp_dec_float.hpp>

using boost::multiprecision::cpp_dec_float_100;
using boost::lexical_cast;
using namespace std;

string rational_repr_fraction(const rational_number& num);
string rational_repr_decimal(const rational_number& num);
#endif
