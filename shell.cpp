#include "shell.hpp"

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
    system("cat ./banner.d");

    string line;
    vector<string> tokens;

    while(true) {
        cout << INTERP_TEXT;
        getline(cin, line);
        tokens = comma_split(line);

        for (vector<string>::iterator it = tokens.begin(); it < tokens.end(); ++it) {
            controller(*it, rational_vec);
        }
    }
}
