#ifndef _COMMANDS_HPP
#define _COMMANDS_HPP

#include "../lib/number.hpp"
#include "god_parse.hpp"
#include "../lib/rational_misc.hpp"
#include "../lib/rational_repr.hpp"

#include <iostream>

void __clear();
void __history();
void __show();
void __exit(std::string& arg);
void __dec(std::string& arg);
void __frac(std::string& arg);

#endif
