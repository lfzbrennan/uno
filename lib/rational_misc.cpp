#include "rational_misc.hpp"

using namespace std;

// simplify rational number
void simplify(rat& num) {
    uno_int gcd = boost::integer::gcd(num.denominator, num.numerator);
    if (gcd <= 1) return;
    num.denominator /= gcd;
    num.numerator /= gcd;
}

void invert(rat& num) {
    uno_int temp = num.numerator;
    num.numerator = num.denominator;
    num.denominator = temp;
}

// rat to uno_float
uno_float rat_to_large_float(rat& num) {
    return numeric_cast<uno_float>(num.numerator) / numeric_cast<uno_float>(num.denominator);
}

// uno_float to rat
rat large_float_to_rat(uno_float& num) {
    rat out;
    rat cur;

    ostringstream ss;
    ss << fixed << setprecision(numeric_limits<uno_float>::digits10);
    ss << num;
    string s_num = ss.str();

    int dec = s_num.find('.');

    // not a decimal, can just be cast as an int
    if (dec == string::npos) {
        out.numerator = lexical_cast<uno_int>(s_num);
        out.denominator = 1;
        return out;
    }

    // iterate through string, compiling the number
    out.type = zero;
    for (int i = 0; i < s_num.size(); ++i) {
        if (i == dec || s_num[i] == '0') continue;
        cur.type = positive;
        if (dec > i) {
            uno_int offset = 1;
            int j = 0;
            while (j < (dec - i - 1)) {
                offset *= 10;
                j++;
            }

            cur.numerator = uno_int((int)s_num[i] - '0') * offset;
            cur.denominator = 1;
        } else {
            uno_int offset = 1;
            int j = 0;
            while (j < (i - dec)) {
                offset *= 10;
                j++;
            }

            cur.numerator = ((int)s_num[i] - '0');
            cur.denominator = offset;
        }
        out = rational_addition(out, cur);
    }
    // simply and return
    simplify(out);
    return out;
}

// if the denominator is prime factorable by 2 and 5, then it doesnt repeat.
// if not, then it does repeat
bool repeating_decimal(uno_int b) {
    while (!(b % 2)) b /= 2;
    while (!(b % 5)) b /= 5;

    if (b == 1) return false;
    else return true;
}

// rat to string decimal representation
string rat_to_dec_string(rat& num) {
    // just an integer
    if (num.denominator == 1) {
        return lexical_cast<string>(num.numerator) + ".0";
    }
    // it is a repeating decimal
    else if (repeating_decimal(num.denominator)) {
        string out;
        rat temp = num;
        uno_int a_o = temp.numerator / temp.denominator;
        temp.numerator -= a_o * temp.denominator;

        out += lexical_cast<string>(a_o) + ".";

        vector<char> sequence;
        vector<uno_int> remainders;
        uno_int remainder;

        while (true) {
            temp.numerator *= 10;
            char div = (char)(temp.numerator / temp.denominator);

            remainder = (uno_int)div * temp.denominator;
            temp.numerator -= remainder;

            if (remainder && find(remainders.begin(), remainders.end(), remainder) != remainders.end()) {
                int index = distance(remainders.begin(), find(remainders.begin(), remainders.end(), remainder));
                for (int i = 0; i < sequence.size(); ++i) {
                    if (i == index)
                        out += '~';

                    out += sequence[i];
                }
                return out;
            }
            sequence.push_back(div + '0');
            remainders.push_back(remainder);
        }
        return out;
    }
    // it is a terminating decimal
    else {
        ostringstream ss;
        ss << fixed << setprecision(numeric_limits<uno_float>::digits10);
        ss << numeric_cast<uno_float>(num.numerator) / numeric_cast<uno_float>(num.denominator);
        return ss.str();
    }
}
