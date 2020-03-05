#ifndef NUMBER_DOT_HPP
#define NUMBER_DOT_HPP

#include <iostream>

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/lexical_cast.hpp>

enum rational_types {zero, negative, positive, undefined};

typedef struct {
    rational_types type; // 0 = 0, 1 = negative, 2 = positive, 3 = inf
    boost::multiprecision::uint128_t numerator;
    boost::multiprecision::uint128_t denominator;
} rational_number;

#endif
