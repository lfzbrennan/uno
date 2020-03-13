#ifndef _NUMBER_HPP
#define _NUMBER_HPP

#include <iostream>
#include <numeric>

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>

#include <boost/integer/common_factor.hpp>
#include <boost/lexical_cast.hpp>

#define SENTINEL ""

// 4 possible types of rational numbers
enum rational_types {zero=0, negative=1, positive=2, undefined=3};

using boost::multiprecision::cpp_dec_float;     // for cpp_dec_float<100>
using boost::multiprecision::uint1024_t;        // for uint1024_t

// defining uno_float and uno_int type globally
typedef boost::multiprecision::number<cpp_dec_float<100> > uno_float;
typedef uint1024_t uno_int;

// rational number "object"
typedef struct {
    std::string name;
    rational_types type;
    uno_int numerator;
    uno_int denominator;
} rational_number;

// lambda "object"
typedef struct {
    std::string name;
    std::vector<std::string> parameters;
    std::string expression;
} lambda;

// shorthand -> writing rational_number is a pain
typedef rational_number rat;

#endif
