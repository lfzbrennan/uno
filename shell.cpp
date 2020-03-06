#include <boost/multiprecision/cpp_int.hpp>

#include "lib/number.hpp"
#include "lib/rational_repr.cpp"
#include "lib/rational_misc.cpp"
#include "lib/rational_operations.cpp"

#include "parse/god_parse.cpp"

#include "config.hpp"

#include <iostream>
#include <vector>

#include <stdio.h>

typedef std::vector<rational_number> rational_vec;

/*
char* commands[] = {
    "clear",
};
*/

using namespace std;

vector<string> comma_split(string l) {
   vector<string> tokens;
   string token;
   istringstream tokenStream(l);
   while (std::getline(tokenStream, token, ',')) {
      tokens.push_back(token);
   }
   return tokens;
}

int main(int argc, char** argv) {

    printf("WELCOME\n");

    string line;
    vector<string> tokens;

    while(true) {

        cout << INTERP_TEXT;
        getline(cin, line);
        tokens = comma_split(line);

        for (vector<string>::iterator it = tokens.begin(); it < tokens.end(); ++it) {
            controller(*it);
        }

    }
}
