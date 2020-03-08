#ifndef RATIONAL_REPR_DOT_HPP
#define RATIONAL_REPR_DOT_HPP

#include "number.hpp"

#include <boost/multiprecision/cpp_dec_float.hpp>

std::string rational_repr_fraction(const rational_number& num);
std::string rational_repr_decimal(const rational_number& num);
#endif
