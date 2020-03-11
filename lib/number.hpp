#ifndef _NUMBER_HPP
#define _NUMBER_HPP

#include <iostream>
#include <numeric>

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/lexical_cast.hpp>

#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/integer/common_factor.hpp>

enum rational_types {zero, negative, positive, undefined};

using boost::multiprecision::cpp_dec_float;
using boost::multiprecision::uint1024_t;

typedef boost::multiprecision::number<cpp_dec_float<1000> > uno_float;
typedef uint1024_t uno_int;

typedef struct {
    std::string name;
    rational_types type; // 0 = 0, 1 = negative, 2 = positive, 3 = inf
    uno_int numerator;
    uno_int denominator;
} rational_number;

typedef struct {
    std::string name;
    std::vector<std::string> parameters;
    std::string expression;
} lambda;

typedef rational_number rat;

#endif
