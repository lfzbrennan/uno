#ifndef _SHELL_HPP
#define _SHELL_HPP

#include <boost/multiprecision/cpp_int.hpp>

#include "lib/number.hpp"
#include "lib/rational_repr.hpp"
#include "lib/rational_misc.hpp"
#include "lib/rational_operations.hpp"

#include "parse/god_parse.hpp"

#include "config.hpp"

#include <iostream>
#include <vector>

#include <stdio.h>

using namespace std;

vector<rational_number> rational_vec;

vector<string> comma_split(string l);
#endif
