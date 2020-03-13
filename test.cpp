#include <iostream>
#include "shell.hpp"

using namespace std;


int main() {
    uno_int top = 21234323;
    uno_int bot = 100;
    uno_float x = numeric_cast<uno_float>(top) / numeric_cast<uno_float>(bot);
    cout << setprecision(50) << endl;
    cout << x << endl;
}
