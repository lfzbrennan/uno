#include "shell.hpp"

using namespace std;

vector<rational_number> rational_vec;
vector<lambda> lambda_vec;

vector<string> comma_split(string l) {
   vector<string> tokens;
   string token;
   istringstream tokenStream(l);

   while (std::getline(tokenStream, token, ','))
      tokens.push_back(token);

   return tokens;
}

int main(int argc, char** argv) {

    cout << fixed << setprecision(numeric_limits<uno_float>::digits10);

    system("cat ./banner.d");

    string line;
    vector<string> tokens;

    while(true) {
        cout << INTERP_TEXT;
        getline(cin, line);
        tokens = comma_split(line);

        for (vector<string>::iterator it = tokens.begin(); it != tokens.end(); ++it) {
            controller(*it, rational_vec, lambda_vec);
        }
    }
}
