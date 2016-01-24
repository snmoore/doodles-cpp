// Convert Roman numerals to decimal values
//
// See https://en.wikipedia.org/wiki/Roman_numerals
//
// Note that it is easier to process a Roman numeral string from right-to-left
// rather than left-to-right:
//
//  right-to-left : only need the current and previous numeral to decide whether
//                  to add or subtract
//
//  left-to-right : need the current and next two numerals to decide whether to
//                  add or subtract

#include <iomanip>      // For setw
#include <iostream>     // For cout etc

using namespace std;

// Roman numerals
class Roman {
private:
    string str;
    unsigned int char_to_decimal(char numeral) const; // convert a single Roman numeral to decimal

public:
    Roman(string str) :str(str) {}
    unsigned int getDecimal() const;    // get the decimal representation of the Roman numerals
    string getString() const;           // get the string representation of the Roman numerals
};

// Convert a single Roman numeral to decimal
unsigned int Roman::char_to_decimal(char numeral) const {
    unsigned int result = 0;

    switch(numeral) {
    case 'I': result = 1;    break;
    case 'V': result = 5;    break;
    case 'X': result = 10;   break;
    case 'L': result = 50;   break;
    case 'C': result = 100;  break;
    case 'D': result = 500;  break;
    case 'M': result = 1000; break;
    default: throw runtime_error("Invalid Roman numeral: " + string(1, numeral) + "\n");
    }

    return result;
}

// Get the decimal representation of the Roman numerals
unsigned int Roman::getDecimal() const {
    unsigned int curr = 0;
    unsigned int prev = 0;
    unsigned int sum  = 0;
    for(auto c = str.rbegin(); c != str.rend(); c++) {
        curr = char_to_decimal(*c);
        if(curr >= prev) {
            // E.g. XI => curr=10, prev=1 => 10+1 => 11
            sum += curr;
        }
        else {
            // Vn, Ln and Dn are all invalid combinations
            if(curr == 5 || curr == 50 || curr == 500) {
                throw runtime_error("invalid combination");
            }

            // Ratio of prev to curr should be 10 or less
            if((curr * 10) < prev) {
                throw runtime_error("invalid combination");
            }

            // E.g. IX => curr=1, prev=10 => 10-1 => 9
            sum -= curr;
        }

        // Next iteration
        prev = curr;
    }

    return sum;
}

// Get the string representation of the Roman numerals
string Roman::getString() const {
    return str;
}

// Common test function
void test(string str, unsigned int decimal) {
    Roman roman = Roman(str);
    try {
        if(roman.getDecimal() == decimal) {
            cout << setw(6) << roman.getString() << " " << decimal << endl;
        }
        else {
            cout << setw(6) << roman.getString() << " - bad conversion" << endl;
        }
    }
    catch(runtime_error& e) {
        cout << setw(6) << roman.getString() << " - " << e.what() << endl;
    }
}

int main() {
    // Individual numerals
    cout << "Individual numerals:" << endl;
    test("I", 1);
    test("V", 5);
    test("X", 10);
    test("L", 50);
    test("C", 100);
    test("D", 500);
    test("M", 1000);
    cout << endl;

    // Valid combinations for subtractive notation
    cout << "Valid combinations for subtractive notation:" << endl;
    test("IV", 4);
    test("IX", 9);
    test("XL", 40);
    test("XC", 90);
    test("CD", 400);
    test("CM", 900);
    cout << endl;

    // Numbers 1 to 10
    cout << "Numbers 1 to 10:" << endl;
    test("I",    1);
    test("II",   2);
    test("III",  3);
    test("IV",   4);
    test("V",    5);
    test("VI",   6);
    test("VII",  7);
    test("VIII", 8);
    test("IX",   9);
    test("X",    10);
    cout << endl;

    // Various years
    cout << "Various years:" << endl;
    test("MCMIV",  1904); // from Wikipedia
    test("MCMLIV", 1954); // from Wikipedia - as in the trailer for the movie The Last Time I Saw Paris
    test("MCMXC",  1990); // from Wikipedia - used as the title of musical project Enigma's debut album MCMXC a.D., named after the year of its release.
    test("MMXIV",  2014); // from Wikipedia - the year of the games of the XXII (22nd) Olympic Winter Games (in Sochi)
    cout << endl;

    // Invalid combinations for subtractive notation
    cout << "Invalid combinations for subtractive notation:" << endl;
    test("IL", 49);  // should be XLIX
    test("IC", 99);  // should be XCIX
    test("ID", 499); // should be CDXCIX
    test("IM", 999); // should be CMXCIX
    test("VX", 5);   // should be V
    test("VL", 45);  // should be XLV
    test("VC", 95);  // should be XCV
    test("VD", 495); // should be CDXCV
    test("VM", 995); // should be CMXCV
    test("XD", 490); // should be CDXC
    test("XM", 990); // should be CMXC
    test("LC", 50);  // should be L
    test("LD", 450); // should be CDL
    test("LM", 950); // should be CML
    test("DM", 500); // should be D
    cout << endl;

    // Valid counterparts to the invalid combinations
    cout << "Valid counterparts to the invalid combinations:" << endl;
    test("XLIX",   49);
    test("XCIX",   99);
    test("CDXCIX", 499);
    test("CMXCIX", 999);
    test("V",      5);
    test("XLV",    45);
    test("XCV",    95);
    test("CDXCV",  495);
    test("CMXCV",  995);
    test("CDXC",   490);
    test("CMXC",   990);
    test("L",      50);
    test("CDL",    450);
    test("CML",    950);
    test("D",      500);
    cout << endl;
}
