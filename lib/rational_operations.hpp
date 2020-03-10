#ifndef _RATIONAL_OPERATIONS_HPP
#define _RATIONAL_OPERATIONS_HPP

#include "number.hpp"
#include "rational_misc.hpp"

using namespace std;
using boost::multiprecision::uint128_t;

rat rational_multiply(rat r1, rat r2);
rat rational_divide(rat r1, rat r2);
rat rational_addition(rat r1, rat r2);
rat rational_subtract(rat r1, rat r2);

#endif
