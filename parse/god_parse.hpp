#ifndef _GOD_PARSE_HPP
#define _GOD_PARSE_HPP

#include "../lib/number.hpp"
#include "../lib/rational_operations.hpp"
#include "../lib/rational_repr.hpp"

#include <stack>
#include <map>

using namespace std;
using boost::lexical_cast;
using boost::multiprecision::uint128_t;

#include <stdlib.h>
#include <unistd.h>
#include <math.h>

bool get_assignment(string& line);
void make_output(vector<rational_number>& rat_vec);
void controller(string line, vector<rational_number>& rat_vec);

#endif
