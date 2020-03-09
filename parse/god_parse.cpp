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
    "show"
};

const string special_num  = "~.";
const string operators = "/-+*";
const string variable_ok = "_";

enum errors {nil, bad_expression_character, bad_expression_formulation};

errors err;
char offending_char;

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
        default:
            cout << "Something went wrong" << endl;
    }
}

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

rational_number dec_to_rat(string& num) {
    rational_number out;

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

void process_operator(char front) {
    if (operator_stack.size() == 0) {
        operator_stack.push(front);
    }
    else if (precedence::precedence_map[operator_stack.top()] < precedence::precedence_map[front]) {
        operator_stack.push(front);
    } else {
        process();
    }
}

rational_number parse_number(string& num) {
    rational_types t = positive;
    if (num[0] == '-') {
        t = negative;
        num = num.substr(1, num.size());
    }

    rational_number out;

    // it is a decimal, parse appropriately

    if (num.find('.') != string::npos) {
        out = dec_to_rat(num);
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
        out.type = t;
        out.numerator = lexical_cast<uint128_t>(num);
        out.denominator = 1;
        return out;
    }
}

void infix_parse(string& line) {
    operand_stack = stack<rational_number>();
    operator_stack = stack<char>();

    top = ' ';

    for (string::const_iterator it = line.cbegin(); it != line.cend(); ++it) {
        number = "";
        // if char is '('
        if (*it == '(') {
            operator_stack.push(*it);
        }

        // if char is a digit
        else if (isdigit(*it) || *it == '.') {
            // keeps parsing until number is complete
            number += *it;
            while (isdigit(*(it+1)) || (special_num.find(*(it+1)) != string::npos)) {
                it++;
                number += *it;
            }
            operand_stack.push(parse_number(number));
        }

        // if char is an operator
        else if (operators.find(*it) != string::npos) {
            // if char is a '-'
            if (*it == '-') {
                if (it == line.cbegin() || operators.find(*(it-1)) != string::npos)  {
                    number += *it;
                    while (isdigit(*(it+1)) || (special_num.find(*(it+1)) != string::npos)) {
                        it++;
                        number += *it;
                    }
                    operand_stack.push(parse_number(number));
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
        err = bad_expression_formulation;
        offending_char = top;
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
        if (line[i] == '=') {
            output_name = name;
            line = line.substr(i+1, line.size());
            return true;
        } else {
            err = bad_expression_formulation;
            offending_char = line[i];
            return false;
        }
    }
    return false;
}

// after parsing, print output as needed
void make_output(vector<rational_number>& rat_vec) {
    if (has_output) {
        for (auto&& it : rat_vec) {
            if (it.name == output_name) {
                it.type = output.type;
                it.numerator = output.numerator;
                it.denominator = output.denominator;
                return;
            }
        }
        output.name = output_name;
        rat_vec.push_back(output);
    } else {
        cout << rational_repr_fraction(output) << endl;
    }
}

// parsing controller
void controller(string line, vector<rational_number>& rat_vec) {
    err = nil;
    offending_char = ' ';

    // remove whitespace
    line.erase(remove(line.begin(), line.end(), ' '), line.end());

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
    make_output(rat_vec);
}
