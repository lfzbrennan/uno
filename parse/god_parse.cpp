#include "../lib/number.hpp"

#include <iostream>
#include <stack>

using namespace std;

#include <stdlib.h>
#include <unistd.h>

stack<rational_number> operand_stack;
stack<char> operator_stack;


const string special_num  = "~.";
const string operators = "/-+*";

enum errors {nil, bad_expression_character, };
errors err;
char offending_char;

void error_message() {
    switch (err) {
        default:
            cout << "Something went wrong" << endl;

    }

}

rational_number parse_number(const string& num) {

}

void infix_parse(const string& line) {
    operand_stack = stack<rational_number>();
    operator_stack = stack<char>();

    string number;
    for (auto it = line.cbegin(); it != line.cend(); ++it) {
        number = "";
        if (*it == '(') {
            operator_stack.push(*it);
        } else if (isdigit(*it)) {
            // keeps parsing until number is complete
            number += *it;
            while (true) {
                if (isdigit(*(it+1)) || special_num.find(*(it+1))) {
                    it++;
                    number += *it;
                }
            }
            operand_stack.push(parse_number(number));
        } else if (operators.find(*it)) {

        } else if (*it == ')') {

        } else {
            offending_char = *it;
            err = bad_expression_character;
            return;
        }

    }
}

void controller(string line) {
    err = nil;
    offending_char = ' ';

    infix_parse(line);
    exit(0);
    // check if command?
    // check errno
    if (err) {
        error_message();
        return;
    }

    // check if assignment? ie x =
    if (err) {
        error_message();
        return;
    }

    // now parse expression

    /*

    rational_number parsed = parse(expression)

    either:
        x = rational_number
    or:
        cout << rational_expression << endl;


    */

}
