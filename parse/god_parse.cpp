#include "../lib/number.hpp"

#include <iostream>

unsigned int err = 0;

void error_message() {

}

void controller(std::string line) {
    err = 0;
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
