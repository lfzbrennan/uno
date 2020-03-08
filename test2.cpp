#include <iostream>

using namespace std;


int main(int argc, char** argv) {
    string line = "asdf hell asdf";
    line.erase(remove(line.begin(), line.end(), ' '), line.end());
    cout << line << endl;
}
