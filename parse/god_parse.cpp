#include "god_parse.hpp"

stack<rational_number> operand_stack;
stack<char> operator_stack;

bool has_output;
string output_name;
rational_number output;

rational_number cur;

string number;
char top;

string commands[] = {
    "clear",
    "history",
    "show",
    "exit"
};

const string special_num  = "~.";
const string operators = "/-+*";
const string variable_ok = "_";

enum errors {
    nil,
    bad_expression_character,
    bad_expression_formulation,
    undfined_variable,
    no_lambda_parameters,
    poor_variable_name,
    poor_parameter_name,
    unused_parameter,
    poor_lambda_evaluation
};

errors err;
char offending_char;
string offending_string;

vector<rational_number> lambda_temp;

vector<rational_number>* rat_vec;
vector<lambda>* lam_vec;

struct precedence {
    static map<char,int> create_map() {
          map<char,int> m;
          m['-'] = 1;
          m['+'] = 1;
          m['/'] = 2;
          m['*'] = 2;
          m['^'] = 3;
          m['('] = 0;
          m[')'] = 0;
          return m;
        }
    static map<char,int> precedence_map;
};

map<char,int> precedence::precedence_map = precedence::create_map();

// error message function
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

// computes operation
rational_number operation(rational_number r1, rational_number r2, char op) {
    switch (op) {
        case '-':
            return rational_subtract(r1, r2);
        case '+':
            return rational_addition(r1, r2);
        case '/':
            return rational_divide(r1, r2);
        case '*':
            return rational_multiply(r1, r2);
        default:
            return rational_multiply(r1, r2);
    }
}

// converts decimal to rational number
rational_number dec_to_rat(string& num) {
    rational_number out;
    out.type = positive;
    // check if it is zero
    for (string::const_iterator it = num.cbegin(); it != num.cend(); ++it) {
        if (*it != '0' && *it != '.') break;
        if ((it+1) == num.cend()) {
            out.type = zero;
            return out;
        }
    }

    // remove 0's at the front
    for (int i = 0; i < num.size(); i++) {
        if (num[i] != '0' || num[i] == '.') break;
        num.substr(1, num.size());
    }

    int dec = num.find('.');

    if ((dec-1) == num.size()) {
        out.numerator = lexical_cast<uint128_t>(num.substr(num.size()-1));
        out.denominator = 1;
    } else {
        out.type = zero;
        for (int i = 0; i < num.size(); i++) {
            if (i == dec || num[i] == '0') continue;
            cur.type = positive;
            if (dec > i) {
                cur.numerator = ((int)num[i] - '0') * (int)pow(10, dec - i - 1);
                cur.denominator = 1;
            } else {
                cur.numerator = ((int)num[i] - '0');
                cur.denominator = (int)pow(10, i - dec);
            }
            out = rational_addition(out, cur);
        }
    }
    return out;
}

// processes item from stack
void process() {
    top = operator_stack.top(); operator_stack.pop();
    if (operand_stack.size() < 2) {
        err = bad_expression_formulation;
        offending_char = top;
        return;
    }
    rational_number r2 = operand_stack.top(); operand_stack.pop();
    rational_number r1 = operand_stack.top(); operand_stack.pop();

    operand_stack.push(operation(r1, r2, top));
}

// processes operator from stack
void process_operator(char front) {
    while (!operator_stack.empty() && precedence::precedence_map[operator_stack.top()] >= precedence::precedence_map[front])
        process();
    operator_stack.push(front);

}

// parses number
rational_number parse_number(string& num) {
    rational_types t = positive;
    if (num[0] == '-') {
        t = negative;
        num = num.substr(1, num.size());
    }

    rational_number out;
    out.type = positive;

    // it is a decimal, parse appropriately
    if (num.find('.') != string::npos) {
        out = dec_to_rat(num);
        if (!(out.type == zero || out.type == undefined))
            out.type = t;
        return out;
    } else {
        for (string::const_iterator it = num.cbegin(); it != num.cend(); ++it) {
            // if its not all digits, something is up
            if (!isdigit(*it)) {
                err = bad_expression_character;
                offending_char = *it;
                return out;
            }
        }
        if (!(out.type == zero || out.type == undefined))
            out.type = t;
        out.numerator = lexical_cast<uint128_t>(num);
        if (out.numerator == 0)
            out.type = zero;
        out.denominator = 1;
        return out;
    }
}

void infix_parse(string& line) {
    operand_stack = stack<rational_number>();
    operator_stack = stack<char>();

    top = ' ';

    for (string::const_iterator it = line.cbegin(); it < line.cend(); ++it) {
        number = "";

        if (*it == ' ') continue;
        // if char is '('
        else if (*it == '(') {
            operator_stack.push(*it);
        }

        // if char is a variable, or a LAMBDA EXPRESSION
        else if (isalpha(*it)) {
            // if no variables or LAMBDAS, error
            if (rat_vec->empty() && lam_vec->empty()) {
                err = undfined_variable;
                offending_string = number;
                return;
            }
            // get full variable name
            number += *it;
            if ((it+1) != line.cend()) {
                while (isdigit(*(it+1)) || isalpha(*(it+1)) || (variable_ok.find(*(it+1)) != string::npos)) {
                    it++;
                    number += *it;
                    if (it == line.cend()) break;
                }
            }

            bool good = false;
            // check to see if that variable exists
            for (auto i = rat_vec->begin(); i != rat_vec->end(); ++i) {
                if (i->name == number) {
                    operand_stack.push(*i);
                    good = true;
                    break;
                }
            }

            // check to see if a lambda exists
            for (auto i = lam_vec->begin(); i != lam_vec->end(); ++i) {
                if (i->name == number) {
                    // we found a lambda, now eval
                    it++;
                    int param_num = i->parameters.size();
                    vector<string> params;
                    string token;
                    while (params.size() < param_num) {
                        token = "";
                        while (it < line.cend()) {
                            if (*it == ' ') {
                                if (token != "") break;
                            } else if (isalpha(*it) || isdigit(*it) || variable_ok.find(*it) != string::npos){
                                token += *it;
                            } else break;
                            it++;
                        }
                        params.push_back(token);
                    }
                    eval_lambda(*i, params);
                    if (!err)
                        good = true;
                    break;
                }
            }
            if (!good) {
                cout << "here" << endl;
                err = undfined_variable;
                offending_string = number;
                return;
            }

            // check to see if
        }
        // if char is a digit
        else if (isdigit(*it) || *it == '.') {
            // keeps parsing until number is complete
            number += *it;
            if ((it+1) != line.cend()) {
                while (isdigit(*(it+1)) || (special_num.find(*(it+1)) != string::npos)) {
                    it++;
                    number += *it;
                }
            }
            operand_stack.push(parse_number(number));
        }

        // if char is an operator
        else if (operators.find(*it) != string::npos) {
            // if char is a '-'
            if (*it == '-') {
                if (it == line.cbegin() || operators.find(*(it-1)) != string::npos)  {
                    if (isalpha(*(it+1))) {
                        it++;
                        number += *it;
                        while (isdigit(*(it+1)) || isalpha(*(it+1)) || (variable_ok.find(*(it+1)) != string::npos)) {
                            it++;
                            number += *it;
                        }
                        for (auto i = rat_vec->begin(); i < rat_vec->end(); ++i) {
                            if (i->name == number) {
                                rational_number temp = *i;
                                if (temp.type == negative) temp.type = positive;
                                else if (temp.type == positive) temp.type = negative;
                                operand_stack.push(temp);
                                break;
                            }
                            if ((i+1) == rat_vec->end()) {
                                err = undfined_variable;
                                offending_string = number;
                                return;
                            }
                        }
                    } else {
                        number += *it;
                        while (isdigit(*(it+1)) || (special_num.find(*(it+1)) != string::npos)) {
                            it++;
                            number += *it;
                        }
                        operand_stack.push(parse_number(number));
                    }
                }
                else process_operator(*it);
            }
            // if char is not a '-'
            else process_operator(*it);
        }

        // if char is a ')'
        else if (*it == ')') {
            while (operator_stack.top() != '(') {
                process();
            }
            operator_stack.pop();
        }

        // if it is anythig else, throw an error
        else {
            offending_char = *it;
            err = bad_expression_character;
            return;
        }
    }

    // continue looping through operand stack
    while (operator_stack.size() > 0) {
        process();
    }

    // make sure only one operand is left
    if (operand_stack.size() != 1) {
        cout << rational_repr_fraction(operand_stack.top()) << endl;
        err = bad_expression_formulation;
        offending_char = line[0];
        return;
    }

    // set output and leave
    output = operand_stack.top();
}

// if there is an assignment, set output
bool get_assignment(string& line) {
    if (line.find('=') != string::npos) {
        if (!isalpha(line[0])) {
            err = bad_expression_formulation;
            offending_char = line[0];
            return false;
        }
        string name = "";
        int i = 0;
        for (; isalpha(line[i]) || isdigit(line[i]) || variable_ok.find(line[i]) != string::npos; ++i) {
            name += line[i];
        }
        char next;
        while (line[i] != ' ') i++;
        next = line[i+1];
        if (next == '=') {
            output_name = name;
            line = line.substr(i+2, line.size());
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
    if (has_output) {
        for (auto&& it : *rat_vec) {
            if (it.name == output_name) {
                it.type = output.type;
                it.numerator = output.numerator;
                it.denominator = output.denominator;
                return;
            }
        }
        output.name = output_name;
        rat_vec->push_back(output);
    } else {
        cout << rational_repr_fraction(output) << endl;
    }
}

// process each command accordingly
void process_command(string& command) {
    if (command == "clear") {

    } else if (command == "show") {

    } else if (command == "history") {

    }
}

string replace(string str, const string& from, const string& to) {
    size_t start_pos;
    while (str.find(from) != string::npos) {
        start_pos = str.find(from);
        str.replace(start_pos, from.length(), to);
    }
    return str;
}

vector<string> split(string l) {
   vector<string> tokens;
   string token;
   istringstream tokenStream(l);
   while (std::getline(tokenStream, token, ' ')) {
      tokens.push_back(token);
   }
   return tokens;
}

bool allowable_variable_name(string variable) {
    if (!isalpha(variable[0])) return false;
    for (auto i = variable.cbegin() + 1; i != variable.cend(); ++i) {
        if (!(isdigit(*i) || isalpha(*i) || variable_ok.find(*i) != string::npos)) return false;
    }
    return true;
}

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
    infix_parse(test);
    if (err) {
        err = bad_expression_formulation;
        offending_string = expression;
        return false;
    }
    return true;
}

bool validate_params(vector<string>& params) {
    for (auto&& p : params) {
        if (isdigit(p[0])) {
            parse_number(p);
            if (err) {
                return false;
            }
        } else if (isalpha(p[0])) {
            bool good = false;
            for (auto i = rat_vec->begin(); i != rat_vec->end(); i++) {
                if (i->name == p) {
                    good = true;
                    break;
                }
            }
            if (!good) return false;
        } else return false;
    }
    return true;
}

rational_number eval_lambda(const lambda& l, vector<string>& params) {
    rational_number out;

    if (!validate_params(params)) {
        err = poor_lambda_evaluation;
        offending_string = l.name;
        return out;
    }

    string expression = l.expression;

    for (int i = 0; i < params.size(); ++i) {
        expression = replace(expression, l.parameters[i], params[i]);
    }
    infix_parse(expression);
    return output;
}

void create_lambda(string& line) {
    string name;
    vector<string> tokens = split(line);
    if (tokens[1] == ":=") {
        err = no_lambda_parameters;
        return;
    }
    name = tokens[0];
    if (!allowable_variable_name(name)) {
        err = poor_variable_name;
        offending_string = name;
        return;
    }
    vector<string> parameters;
    for (int i = 1; tokens[i] != ":="; ++i) {
        if (!allowable_variable_name(tokens[i])) {
            err = poor_parameter_name;
            offending_string = tokens[i];
            return;
        }
        parameters.push_back(tokens[i]);
    }
    string expression = line.substr(line.find(":=") + 2, line.size());
    if (validate_lambda(parameters, expression)) {
        lambda l;
        l.name = name;
        l.expression = expression;
        l.parameters = parameters;

        lam_vec->push_back(l);
    }
}

/*
controller job:

1. check if its a command
2. check if it is a lambda definition

now -> we expect it to be some sort of expression eval

1. check if we direct an output (ie x = )
2. evaluate expression

*/

// parsing controller
void controller(string line, vector<rational_number>& rational_vec, vector<lambda>& lambda_vec) {
    err = nil;
    offending_char = ' ';
    offending_string = " ";

    // if it is a command, process accordingly
    string command = "";

    for (string::const_iterator it = line.cbegin(); *it != ' '; ++it)
        command += *it;

    if (find(begin(commands), end(commands), command) != end(commands)) {
        process_command(command);
        if (err)
            error_message();
        return;
    }
    lam_vec = &lambda_vec;
    rat_vec = &rational_vec;

    // if not command, check if it is a lambda expression
    if (line.find(":=") != string::npos) {
        create_lambda(line);
        if (err)
            error_message();
        return;
    }
    // its not a command, prepare for expression processing: remove whitespace

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

    // make output
    make_output();
}
