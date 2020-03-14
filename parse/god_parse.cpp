#include "god_parse.hpp"

/**
*   This is the main parsing file. The main idea is that the controller processes
*   the input using helper functions. After attempting to process the input in
*   different ways, the controller checks if err has been set. If so, the error_message
*   function is called, an appropriate message is sent, and parsing is terminated.
*   If everything is ok, the parser finishes parsing and redirects parsing output to
*   either a) a variable, or b) to stdout.
*/

// Possible errors. Defaults to nil (no errors)
enum errors {
    nil,
    bad_expression_character,
    bad_expression_formulation,
    undfined_variable,
    no_lambda_parameters,
    poor_variable_name,
    poor_parameter_name,
    unused_parameter,
    poor_lambda_evaluation,
    imaginary_exponent
};

// global error information
errors err;
char offending_char;
string offending_string;

// sentinel string value
string sentinel = SENTINEL;

// global information about possible output variable
bool has_output;
string output_name;
rat output;

// collection of special characters
const string special_num = "~.";
const string operators = "/-+*^";
const string variable_ok = "_";

// pointers to global collections of lambda expressions and variables
vector<rat>* variable_vec;
vector<lambda>* lamda_vec;

// stacks for parsing infix expressions
stack<rat> values;
stack<char> ops;

// helper variables
rat cur;
string number;
char top;

// possible commands
string commands[] = {
    "clear",
    "history",
    "show",
    "exit",
    "frac",
    "dec"
};

// static precedence_map created at start
struct precedence {
    static map<char,int> create_map() {
          map<char,int> m;
          m['-'] = 1;
          m['+'] = 1;
          m['/'] = 2;
          m['*'] = 2;
          m['^'] = 3;
          m[SPECIAL_POW_CHAR] = 3;
          m[SPECIAL_ROOT_CHAR] = 3;
          m['('] = 0;
          m[')'] = 0;
          return m;
        }
    static map<char,int> precedence_map;
};

map<char,int> precedence::precedence_map = precedence::create_map();


// commands
//============================================================================//
//============================================================================//
//============================================================================//

// exists uno
void __exit(string& arg) {
    cout << "Goodbye" << endl;
    exit(0);
}

// displays history
void __history() {

}

// displays number as a decimal
void __dec(string& arg) {
    if (arg == SENTINEL) {
        // print most recent output
        cout << rational_repr_decimal(output) << endl;
        return;
    }

    if (arg == "-h" || arg == "--help") {
        // TODO, SHOW HELP
    }

    rat num;
    // is variable
    if (isalpha(arg[0])) {
        for (auto it = variable_vec->begin(); it != variable_vec->end(); ++it) {
            if (it->name == arg) {
                cout << rational_repr_decimal(*it) << endl;
                return;
            }
        }
        cout << "unrecognized token " << arg << endl;
    }
    // is number, parse
    else if (isdigit(arg[0]) || arg[0] == '-') {

        // either a fraction, or a number literal

        // must be a fraction
        if (arg.find('/') != string::npos) {
            rational_types out_type = positive;

            // check if well formed fraction
            if (!well_formed_fraction(arg)) {
                cout << "bad fraction " << arg << endl;
                return;
            }
            int index = arg.find('/');
            num.numerator = lexical_cast<uno_int>(arg.substr(0, index));
            num.denominator = lexical_cast<uno_int>(arg.substr(index + 1, arg.size() - index - 1));
            num.type = out_type;

            cout << rational_repr_decimal(num) << endl;
        }
        // else, must be a number literal
        else {
            num = parse_number(arg);
            if (err) {
                cout << "unrecognized token " << arg << endl;
                return;
            }
            cout << rational_repr_decimal(num) << endl;
        }
    } else {
        cout << "unrecognized token " << arg << endl;
    }
}

// displays number as fraction
void __frac(string& arg) {
    if (arg == SENTINEL) {
        // print most recent output
        cout << rational_repr_fraction(output) << endl;
        return;
    }

    if (arg == "-h" || arg == "--help") {
        // TODO, SHOW HELP
    }

    rat num;
    // is variable
    if (isalpha(arg[0])) {
        for (auto it = variable_vec->begin(); it != variable_vec->end(); ++it) {
            if (it->name == arg) {
                cout << rational_repr_fraction(*it) << endl;
                return;
            }
        }
        cout << "unrecognized token " << arg << endl;
    }
    // is number
    else if (isdigit(arg[0]) || arg[0] == '-') {
        // either a fraction, or a number literal

        // must be a fraction
        if (arg.find('/') != string::npos) {
            rational_types out_type = positive;

            // check if well formed fraction
            if (!well_formed_fraction(arg)) {
                cout << "bad fraction " << arg << endl;
                return;
            }
            int index = arg.find('/');
            num.numerator = lexical_cast<uno_int>(arg.substr(0, index));
            num.denominator = lexical_cast<uno_int>(arg.substr(index + 1, arg.size() - index - 1));
            num.type = out_type;

            cout << rational_repr_fraction(num) << endl;
        }
        // else, must be a number literal
        else {
            num = parse_number(arg);
            if (err) {
                cout << "unrecognized token " << arg << endl;
                return;
            }
            cout << rational_repr_fraction(num) << endl;
        }
    } else {
        cout << "unrecognized token " << arg << endl;
    }
}

// process each command accordingly
void process_command(string& command, vector<string>& args) {
    if (command == "clear") {

    } else if (command == "show") {

    } else if (command == "history") {

    } else if (command == "exit") {
        if (args.size() == 1)
            __exit(sentinel);

        else __exit(args[1]);
    } else if (command == "dec") {
        if (args.size() == 1)
            __dec(sentinel);

        else __dec(args[1]);
    } else if (command == "frac") {
        if (args.size() == 1)
            __frac(sentinel);

        else __frac(args[1]);
    }
}


//============================================================================//
//============================================================================//
//============================================================================//
// Error message function. Sends appropriate error message to stdout, sometimes
// using offending_char or offending_string
void error_message() {
    switch (err) {
        case bad_expression_character:
            cout << "bad character " << offending_char << endl;
            break;
        case bad_expression_formulation:
            cout << "poor expression formulation with term " << offending_char << endl;
            break;
        case undfined_variable:
            cout << "undefined variable " << offending_string << endl;
            break;
        case no_lambda_parameters:
            cout << "lambda must have at least one parameter" << endl;
            break;
        case poor_variable_name:
            cout << "poor variable name " << offending_string << endl;
            break;
        case poor_parameter_name:
            cout << "poor parameter name " << offending_string << endl;
            break;
        case unused_parameter:
            cout << "unused_parameter " << offending_string << endl;
            break;
        case poor_lambda_evaluation:
            cout << "poor lambda evaluation with lamda: " << offending_string << endl;
            break;
        default:
            cout << "Something went wrong" << endl;
    }
}

// computes rational number operation on 2 rats, returns the new rat
rat operation(rat r1, rat r2, char op) {
    switch (op) {
        case '-':
            return rational_subtract(r1, r2);
        case '+':
            return rational_addition(r1, r2);
        case '/':
            return rational_divide(r1, r2);
        case '*':
            return rational_multiply(r1, r2);
        case '^':
            return rational_exponent(r1, r2);
        case SPECIAL_POW_CHAR:
            return rational_exponent(r1, r2);
        case SPECIAL_ROOT_CHAR:
            return rational_exponent_root(r1, r2);
        default:
            return rational_multiply(r1, r2);
    }
}

// checks to make sure the fraction is well formed, if not, sets err and returns false
// if all is well, err is not set and returns true

bool well_formed_fraction(string& frac) {
    bool div = false;
    for (auto&& c : frac) {
        if (!(isdigit(c) || c == '/')) return false;
        if (c == '/') {
            if (div) return false;
            div = true;
        }
    }
    return true;
}

// checks to make sure the decimal is well formed, if not, sets err and returns false
// if all is well, err is not set and returns true
bool well_formed_decimal(string& dec) {
    // end cannot be tilda
    if (dec.back() == '~') {
        err = bad_expression_character;
        offending_char = '~';
        return false;
    }
    // period and tilda should only be used once
    bool period = false;
    bool tilda = false;
    for (auto&& c : dec) {
        if (c == '.') {
            if (period) {
                err = bad_expression_character;
                offending_char = '.';
                return false;
            } period = true;
        } else if (c == '~') {
            if (tilda) {
                err = bad_expression_character;
                offending_char = '~';
                return false;
            } tilda = true;
        } else {
            if (!isdigit(c)) {
                err = bad_expression_character;
                offending_char = c;
                return false;
            }
        }
    }
    return true;
}

// same thing as well formed decimal, but for integers
bool well_formed_integer(string& num) {
    for (string::const_iterator it = num.cbegin(); it != num.cend(); ++it) {
        // if its not all digits, something is up
        if (!isdigit(*it)) {
            err = bad_expression_character;
            offending_char = *it;
            return false;
        }
    }
    return true;
}

// converts a decimal string to a rat number
rat dec_to_rat(string& num) {
    rat out;
    out.type = positive;
    // check if it is zero
    for (string::const_iterator it = num.cbegin(); it != num.cend(); ++it) {
        if (*it != '0' && *it != '.') break;
        if ((it+1) == num.cend()) {
            out.type = zero;
            return out;
        }
    }

    // remove extraneous zeros on front
    int i = 0;
    for (; i < num.size(); i++) {
        if (num[i] != '0' || num[i] == '.') break;
    }
    if (i) num.substr(i, string::npos);

    // get location of the decimal
    int dec = num.find('.');

    // check if the decimal is the end of the num
    if ((dec-1) == num.size()) {
        out.numerator = lexical_cast<uno_int>(num.substr(num.size()-1));
        out.denominator = 1;
    }
    // else, then sum each decimal place
    else {
        out.type = zero;
        for (int i = 0; i < num.size(); ++i) {
            if (i == dec || num[i] == '0') continue;
            // tilda is found -> rest of number is repeating.
            // final fraction calculated using geometric series
            if (num[i] == '~') {

                int l = 0;
                string a = "";

                for (int j = i + 1; j < num.size(); ++j) {
                    a += num[j];
                    l++;
                }

                int n = i - dec - 1 + l;

                uno_int top = lexical_cast<uno_int>(a);
                uno_int r = 1;
                uno_int offset = 1;

                for (int j = 0; j < l; ++j) r *= 10;
                for (int j = 0; j < n; ++j) offset *= 10;

                rat temp;
                temp.type = positive;
                temp.numerator = top * r;
                temp.denominator = (r - 1) * offset;
                out = rational_addition(out, temp);
                simplify(out);
                return out;
            }
            cur.type = positive;
            if (dec > i) {
                cur.numerator = uno_int((int)num[i] - '0')
                    * boost::multiprecision::pow(uno_int(10), dec - i - 1);
                cur.denominator = 1;
            } else {
                cur.numerator = (int)num[i] - '0';
                cur.denominator = boost::multiprecision::pow(uno_int(10), i - dec);
            }
            out = rational_addition(out, cur);
        }
    }
    simplify(out);
    return out;
}

// Processes item from infix stack. Pops the top operator, pops two top values,
// and returns v1 op v2.
void process_infix() {
    top = ops.top(); ops.pop();

    // make sure the stack isn't messed up
    if (values.size() < 2) {
        err = bad_expression_formulation;
        offending_char = top;
        return;
    }

    rat r2 = values.top(); values.pop();
    rat r1 = values.top(); values.pop();

    values.push(operation(r1, r2, top));
}

// Processes specific operator using process_infix. While there are ops left and
// the top of the ops stack has greater or the same precendence as our current_op,
// processes the top of the op stack. Finally, pushes our operator to the op stack
void process_operator(char current_op) {
    while (!ops.empty() && precedence::precedence_map[ops.top()] >= precedence::precedence_map[current_op])
        process_infix();
    ops.push(current_op);

}

// Takes a number string, and returns a rat. First, checks to see the sign of the
// number. Then, checks to see if its a decimal. If not, processes in fractional form
rat parse_number(string& num) {
    rational_types t = positive;

    // negative?
    if (num[0] == '-') {
        t = negative;
        num = num.substr(1, string::npos);
    }

    rat out;
    out.type = positive;

    // it is a decimal, parse appropriately
    if (num.find('.') != string::npos) {
        // make sure it is well formed
        if (!well_formed_decimal(num)) return out;
        out = dec_to_rat(num);
        // set sign
        if (!(out.type == zero || out.type == undefined))
            out.type = t;
        return out;
    }

    // not a decimal, parsing in fractional form
    else {
        // make sure it actually makes sense as a number
        if (!well_formed_integer(num)) return out;

        // create rat with numer as the int and denom 1, assuming its not zero
        out.numerator = lexical_cast<uno_int>(num);
        if (out.numerator == 0) out.type = zero;
        else {
            out.type = t;
            out.denominator = 1;
        }
        return out;
    }
}

// helper function that makes sure the current character can be used in a variable name

bool good_variable_character(char check) {
    return isdigit(check) || isalpha(check) || (variable_ok.find(check) != string::npos);
}

/**
*   This is the main infixing parsing function. Follows the infix expression
*   evaluation algorithm as laid out in
*   http://csis.pace.edu/~murthy/ProgrammingProblems/16_Evaluation_of_infix_expressions
*   Must also check to see if operands are variables, or if lambda expressions are
*   imbedded in the expression
*/
void infix_parse(string& line) {
    values = stack<rat>();
    ops = stack<char>();

    top = ' ';

    for (string::const_iterator it = line.cbegin(); it < line.cend(); ++it) {
        number = "";

        // if char is ' ', ignore
        if (*it == ' ') continue;

        // if char is '(', push onto stack
        else if (*it == '(') {
            ops.push(*it);
        }

        // if char starts with an alpha, then assume its a variable or lambda
        else if (isalpha(*it)) {
            // if no variables or LAMBDAS, error
            if (variable_vec->empty() && lamda_vec->empty()) {
                err = undfined_variable;
                while (it != line.cend() && good_variable_character(*it)){
                    number += *it;
                    it++;
                }
                offending_string = number;
                return;
            }
            // get full variable name
            number += *it;
            while ((it+1) <= line.cend() && good_variable_character(*(it+1))) {
                it++;
                number += *it;
            }

            bool good = false;
            // check to see if that variable exists
            for (auto i = variable_vec->begin(); i != variable_vec->end(); ++i) {
                if (i->name == number) {
                    values.push(*i);
                    good = true;
                    break;
                }
            }
            // variable processed, continue
            if (good) continue;

            // variable not found, must be lambda
            for (auto i = lamda_vec->begin(); i != lamda_vec->end(); ++i) {
                if (i->name == number) {
                    // we found a lambda, now eval
                    it++;
                    // collect parameters
                    int param_num = i->parameters.size();
                    vector<string> params;
                    string token;
                    while (params.size() < param_num) {
                        token = "";
                        while (it < line.cend()) {
                            if (*it == ' ') {
                                if (token != "") break;
                            } else if (good_variable_character(*it) || *it == '~' || *it == '.') {
                                token += *it;
                            } else break;
                            it++;
                        }
                        params.push_back(token);
                    }
                    // eval, this lambda with collected params, check to make sure
                    // everything is ok
                    eval_lambda(*i, params);
                    if (!err)
                        good = true;
                    break;
                }
            }
            // neither variable nor lambda collected, ERROR
            if (!good) {
                err = undfined_variable;
                offending_string = number;
                return;
            }
        }

        // char starts with a digit or '.', must be a number literal
        else if (isdigit(*it) || *it == '.') {
            // keeps parsing until number is complete
            number += *it;
            if ((it+1) <= line.cend()) {
                while (isdigit(*(it+1)) || (special_num.find(*(it+1)) != string::npos)) {
                    it++;
                    number += *it;
                }
            }
            values.push(parse_number(number));
        }

        // if char is an operator
        else if (operators.find(*it) != string::npos) {
            // If char is a '-' then we deal with is specially
            // it could be either an operator, or represent a negative #
            if (*it == '-') {
                // if the '-' is the first character, or the character before isn't an operator,
                // assume that its a negative number
                if ((it == line.cbegin() || operators.find(*(it-1)) != string::npos)
                && (it != line.cend() && *(it+1) != '(' && *(it+1) != ' ')) {
                    // must be a variable
                    if (isalpha(*(it+1))) {
                        it++;
                        number += *it;
                        while (isdigit(*(it+1)) || isalpha(*(it+1)) || (variable_ok.find(*(it+1)) != string::npos)) {
                            it++;
                            number += *it;
                        }
                        for (auto i = variable_vec->begin(); i < variable_vec->end(); ++i) {
                            if (i->name == number) {
                                rat temp = *i;
                                if (temp.type == negative) temp.type = positive;
                                else if (temp.type == positive) temp.type = negative;
                                values.push(temp);
                                break;
                            }
                            if ((i+1) == variable_vec->end()) {
                                err = undfined_variable;
                                offending_string = number;
                                return;
                            }
                        }
                    }
                    // must be a number literal
                    else {
                        number += *it;
                        while (isdigit(*(it+1)) || (special_num.find(*(it+1)) != string::npos)) {
                            it++;
                            number += *it;
                        }
                        values.push(parse_number(number));
                    }
                }
                // if next character is '(', then negative means -1 * (...
                else if (it != line.cend() && *(it+1) == '(') {
                    rat temp;
                    temp.type = negative;
                    temp.numerator = 1;
                    temp.denominator = 1;
                    values.push(temp);
                    process_operator('*');
                }
                // if not, then assume its an operator
                else process_operator(*it);
            }
            // all others must be for sure operators
            else {
                // check for special ** and // operators
                if (*it == '*' && it != line.cend() && *(it+1) == '*') {
                    it++;
                    process_operator(SPECIAL_POW_CHAR);
                } else if (*it == '/' && it != line.cend() && *(it+1) == '/') {
                    it++;
                    process_operator(SPECIAL_ROOT_CHAR);
                }
                else process_operator(*it);
            }
        }

        // If char is a ')', pop infix until corresponding '(' is found
        else if (*it == ')') {
            while (ops.top() != '(') {
                process_infix();
            }
            ops.pop();
        }

        // if it is anything else, throw an error
        else {
            offending_char = *it;
            err = bad_expression_character;
            return;
        }
    }

    // continue looping through operand stack
    while (ops.size() > 0)
        process_infix();

    // make sure only one operand is left
    if (values.size() != 1) {
        err = bad_expression_formulation;
        offending_char = line[0];
        return;
    }

    // set output and leave
    output = values.top();
}

// Check if output is set to a variable (true), or stdout (false). If true,
// must set the output as specified
bool get_assignment(string& line) {
    // if it has an '=', must be trying to do some sort of assignment
    if (line.find('=') != string::npos) {
        if (!isalpha(line[0])) {
            err = bad_expression_formulation;
            offending_char = line[0];
            return false;
        }
        string name = "";

        int i = 0;
        for (; good_variable_character(line[i]); ++i)
            name += line[i];

        char next;
        while (line[i] != ' ') i++;
        next = line[i+1];

        if (next == '=') {
            output_name = name;
            line = line.substr(i+2, string::npos);
            return true;
        } else {
            err = bad_expression_formulation;
            offending_char = next;
            return false;
        }
    }
    return false;
}

// after parsing, print output as needed
void make_output() {

    // if output redirected to a variable
    if (has_output) {
        for (auto&& it : *variable_vec) {
            if (it.name == output_name) {
                it.type = output.type;
                it.numerator = output.numerator;
                it.denominator = output.denominator;
                return;
            }
        }
        output.name = output_name;
        variable_vec->push_back(output);
    }
    // if not, direct to stdout
    else {
        cout << print_rat(output) << endl;
    }
}

// static returns a string with all instaces of `from` changed to `to`
string replace(string str, const string& from, const string& to) {
    size_t start_pos;
    while (str.find(from) != string::npos) {
        start_pos = str.find(from);
        str.replace(start_pos, from.length(), to);
    }
    return str;
}

// vector of strings split by whitespace
vector<string> split(string l) {
   vector<string> tokens;
   string token;
   istringstream tokenStream(l);

   while (getline(tokenStream, token, ' '))
      tokens.push_back(token);

   return tokens;
}

// make sure variable name is allowable
bool allowable_variable_name(string variable) {
    if (!isalpha(variable[0])) return false;

    for (auto i = variable.cbegin() + 1; i < variable.cend(); ++i) {
        if (!good_variable_character(*i)) return false;
    }
    return true;
}

// Validate the lambda. This function is used when a lambda is created.
// Makes sure that all parameters are used, and the expression can actually
// be used.
bool validate_lambda(vector<string>& parameters, string expression) {
    string test = expression;
    // check to see if all parameters are used
    for (auto&& i : parameters) {
        if (expression.find(i) == string::npos) {
            err = unused_parameter;
            offending_string = i;
            return false;
        }
        test = replace(test, i, "5");
    }
    // test to make sure dummy use case doesn't break
    infix_parse(test);
    if (err) {
        err = bad_expression_formulation;
        offending_string = expression;
        return false;
    }
    return true;
}

// Validates lambda parameters. This is used when an instance of the lambda
// is being evaluated, making sure that all parameters used are valid
bool validate_lambda_parameters(vector<string>& params) {
    for (auto&& p : params) {
        // if it is a digit, should be a number
        if (isdigit(p[0])) {
            parse_number(p);
            if (err) {
                return false;
            }
        }
        // if not, its a variable
        else if (isalpha(p[0])) {
            bool good = false;
            for (auto i = variable_vec->begin(); i != variable_vec->end(); i++) {
                if (i->name == p) {
                    good = true;
                    break;
                }
            }
            return good;
        } else return false;
    }
    return true;
}

// evaluate the lambda
rat eval_lambda(const lambda& l, vector<string>& params) {
    rat out;

    // make sure parameters make sense
    if (!validate_lambda_parameters(params)) {
        err = poor_lambda_evaluation;
        offending_string = l.name;
        return out;
    }

    string expression = l.expression;

    // replace values with given parameters
    for (int i = 0; i < params.size(); ++i) {
        expression = replace(expression, l.parameters[i], params[i]);
    }
    // parse the expression
    infix_parse(expression);
    return output;
}

// create a lambda expression from given input
void create_lambda(string& line) {

    // check to make sure lambda has at least one parameter (otherwise, should be variable)
    vector<string> tokens = split(line);
    if (tokens[1] == ":=") {
        err = no_lambda_parameters;
        return;
    }

    // set the name to be the first token, and make sure it is an allowed name
    string name;
    name = tokens[0];
    if (!allowable_variable_name(name)) {
        err = poor_variable_name;
        offending_string = name;
        return;
    }
    // collect parameters, making sure that each is allowed
    vector<string> parameters;
    for (int i = 1; tokens[i] != ":="; ++i) {
        if (!allowable_variable_name(tokens[i])) {
            err = poor_parameter_name;
            offending_string = tokens[i];
            return;
        }
        parameters.push_back(tokens[i]);
    }

    // parse the lambda expression, and validate the expression
    string expression = line.substr(line.find(":=") + 2, string::npos);
    if (validate_lambda(parameters, expression)) {
        lambda l;
        l.name = name;
        l.expression = expression;
        l.parameters = parameters;

        lamda_vec->push_back(l);
    }
}

/*
controller job:

1. check if its a command
2. check if it is a lambda definition

else -> we expect it to be some sort of expression eval

1. check if we direct an output (ie x = )
2. evaluate expression
*/

void controller(string line, vector<rat>& rational_vec, vector<lambda>& l_vec) {
    cout << fixed << setprecision(numeric_limits<uno_float>::digits10);

    // reset error variables
    err = nil;
    offending_char = ' ';
    offending_string = " ";

    // if it is a command, process accordingly
    string command = "";

    // trim the fat
    int i = 0;
    while (line[i] == ' ')
        i++;
    if (i) line = line.substr(i, string::npos);

    // get first word, see if it is a command
    for (string::const_iterator it = line.cbegin(); (*it != ' ') && (it != line.cend()); ++it)
        command += *it;

    if (find(begin(commands), end(commands), command) != end(commands)) {
        // command is one of known commands, must be command or be broken
        vector<string> args = split(line);
        process_command(command, args);
        if (err)
            error_message();
        return;
    }

    // if not command, check if it is a lambda expression (and set lamda and rat vectors)
    lamda_vec = &l_vec;
    variable_vec = &rational_vec;

    if (line.find(":=") != string::npos) {
        // has lambda operator, must be a lambda or a broken command
        create_lambda(line);
        if (err)
            error_message();
        return;
    }

    // not a lambda expression or command, result must be expression
    // get assignment if applicable
    has_output = get_assignment(line);
    if (err) {
        error_message();
        return;
    }

    // process the expression
    infix_parse(line);
    if (err) {
        error_message();
        return;
    }

    // make the output -> either set to stdout, or to a variable name
    make_output();
}
