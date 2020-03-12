#ifndef _RATIONAL_OPERATIONS_HPP
#define _RATIONAL_OPERATIONS_HPP

#include "number.hpp"
#include "rational_misc.hpp"

using namespace std;

rat rational_multiply(rat r1, rat r2);
rat rational_divide(rat r1, rat r2);
rat rational_addition(rat r1, rat r2);
rat rational_subtract(rat r1, rat r2);
rat rational_exponent(rat r1, rat r2);
rat rational_exponent_root(rat r1, rat r2);

#endif
