#ifndef _RATIONAL_MISC_HPP
#define _RATIONAL_MISC_HPP

#include "number.hpp"
#include "rational_operations.hpp"

#include <boost/multiprecision/cpp_dec_float.hpp>
using boost::multiprecision::cpp_dec_float;
using boost::lexical_cast;
using boost::numeric_cast;

void simplify(rat& num);
void invert(rat& num);

uno_float rat_to_large_float(rat& num);

rat large_float_to_rat(uno_float& num);

std::string rat_to_dec_string(rat& num);

#endif
