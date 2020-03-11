#ifndef _GOD_PARSE_HPP
#define _GOD_PARSE_HPP

#include "../lib/number.hpp"
#include "../lib/rational_operations.hpp"
#include "../lib/rational_misc.hpp"
#include "../lib/rational_repr.hpp"

#include "commands.hpp"

#include <stack>
#include <map>
#include <regex>

using namespace std;
using boost::lexical_cast;
using boost::multiprecision::uint128_t;

#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#define SPECIAL_POW_CHAR 1
#define SPECIAL_ROOT_CHAR 2

vector<string> split(string l);

string replace(string str, const string& from, const string& to);

rat operation(rat r1, rat r2, char op);
rat eval_lambda(const lambda& l, vector<string>& params);
rat dec_to_rat(string& num);
rat parse_number(string& num);

bool get_assignment(string& line);
bool allowable_variable_name(string variable);
bool validate_lambda(vector<string>& parameters, string expression);
bool validate_lambda_parameters(vector<string>& params);

void create_lambda(string& line);
void error_message();
void process_infix();
void process_command(string& command);
void infix_parse(string& line);
void process_operator(char front);
void make_output();
void controller(string line, vector<rat>& rational_vec, vector<lambda>& l_vec);

#endif
