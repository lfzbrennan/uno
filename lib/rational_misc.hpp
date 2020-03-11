#ifndef _RATIONAL_MISC_HPP
#define _RATIONAL_MISC_HPP

#include "number.hpp"

#include <boost/multiprecision/cpp_dec_float.hpp>
using boost::multiprecision::cpp_dec_float;
using boost::lexical_cast;
using boost::numeric_cast;

void rational_simplify(rat& num);

uno_float rat_to_large_float(rat& num);

#endif
