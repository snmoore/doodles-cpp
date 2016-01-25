// Convert Roman numerals to decimal values and vice versa
//
// See https://en.wikipedia.org/wiki/Roman_numerals
//
// Note that when converting a Roman numeral string to a decimal value it is
// easier to the string from right-to-left rather than left-to-right:
//
//  right-to-left : only need the current and previous numeral to decide whether
//                  to add or subtract
//
//  left-to-right : need the current and next two numerals to decide whether to
//                  add or subtract

#include <iomanip>      // For setw
#include <iostream>     // For cout etc
#include <map>          // For map

using namespace std;

// Roman numerals
class Roman {
private:
    string str;
    unsigned int char_to_decimal(char numeral) const; // convert a single Roman numeral to decimal

public:
    Roman(string str) :str(str) {}
    Roman(unsigned int decimal);        // construct a Roman numeral from a decimal value
    unsigned int getDecimal() const;    // get the decimal representation of the Roman numerals
    string getString() const;           // get the string representation of the Roman numerals
};

// Convert a single Roman numeral to decimal
unsigned int Roman::char_to_decimal(char numeral) const {
  map<char,unsigned int> numerals {
      { 'I', 1    },
      { 'V', 5    },
      { 'X', 10   },
      { 'L', 50   },
      { 'C', 100  },
      { 'D', 500  },
      { 'M', 1000 },
  };

  // Using at() - throws out_of_range if the key was not found
  return numerals.at(numeral);

  // Using find() - returns iter.end() if the key was not found
#if 0
  auto iter = numerals.find(numeral);
  if(iter == numerals.end()) {
      throw runtime_error("Invalid Roman numeral: " + string(1, numeral) + "\n");
  }
  return iter->second;
#endif

  // Using [] - this inserts a new (key,value) pair if the key was not found
#if 0
  unsigned int result = numerals[numeral];
  if(result == 0) {
      throw runtime_error("Invalid Roman numeral: " + string(1, numeral) + "\n");
  }
  return result;
#endif
}

// Construct a Roman numeral from a decimal value
Roman::Roman(unsigned int decimal) {
    if(decimal == 0) {
        throw runtime_error("0 cannot be represented in Roman numerals");
    }

    // Note that map is ordered, so listing M first has no benefit
    map<unsigned int,char> numerals {
        { 1,    'I' },
        { 5,    'V' },
        { 10,   'X' },
        { 50,   'L' },
        { 100,  'C' },
        { 500,  'D' },
        { 1000, 'M' },
    };

    // Work from M to I, subtracting numeral values whilst building the string
    for(auto iter = numerals.rbegin(); iter != numerals.rend() && decimal > 0; iter++) {
        // Use the current numeral as many times as possible
        while(iter->first <= decimal) {
            str     += iter->second;
            decimal -= iter->first;
        }

        // Try subtractive notation before moving to the next lower numeral...

        // Subtractive notation using non-adjacent numerals e.g. IX, XC, CM
        if((distance(iter, numerals.rend()) > 2) &&
           ((iter->first != 50)  && (iter->first != 500)) && // VL and LD are not valid
           (decimal >= iter->first - next(iter, 2)->first)) {
            str += next(iter, 2)->second;
            str += iter->second;
            decimal -= iter->first - next(iter, 2)->first;
        }
        // Subtractive notation using adjacent numerals e.g. IV, XL or CD
        else if((distance(iter, numerals.rend()) > 1) &&
                ((iter->first / next(iter, 1)->first) == 5) && // VX, LC and DM are not valid
                (decimal >= iter->first - next(iter, 1)->first)) {
            str += next(iter, 1)->second;
            str += iter->second;
            decimal -= iter->first - next(iter, 1)->first;
        }
    }
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
    // Convert in both directions
    string d2s {};
    unsigned int s2d {};
    try {
        d2s = Roman(decimal).getString();
        s2d = Roman(str).getDecimal();
        if((s2d == decimal) && (d2s == str)) {
            cout << setw(13) << d2s << " " << s2d << endl;
        }
        else {
            cout << setw(13) << str << " - bad conversion, should be " << d2s << endl;
        }
    }
    catch(runtime_error& e) {
        cout << setw(13) << str << " - bad conversion, should be " << d2s << endl;
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
    test("MDCCCLXXXVIII", 1888); // a very long year
    test("MCMIV",         1904); // from Wikipedia
    test("MCMLIV",        1954); // from Wikipedia - as in the trailer for the movie The Last Time I Saw Paris
    test("MCMXC",         1990); // from Wikipedia - used as the title of musical project Enigma's debut album MCMXC a.D., named after the year of its release.
    test("MMXIV",         2014); // from Wikipedia - the year of the games of the XXII (22nd) Olympic Winter Games (in Sochi)
    printf("\n");

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
