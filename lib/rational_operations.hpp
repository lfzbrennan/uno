#ifndef _RATIONAL_OPERATIONS_HPP
#define _RATIONAL_OPERATIONS_HPP

#include "number.hpp"
#include "rational_misc.hpp"

using namespace std;
using boost::multiprecision::uint128_t;

rational_number rational_multiply(rational_number r1, rational_number r2);
rational_number rational_divide(rational_number r1, rational_number r2);
rational_number rational_addition(rational_number r1, rational_number r2);
rational_number rational_subtract(rational_number r1, rational_number r2);

#endif
