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



using namespace std;


int main(int argc, char** argv) {
    string line = "asdf hell asdf";
    line.erase(remove(line.begin(), line.end(), ' '), line.end());
    cout << line << endl;
}
