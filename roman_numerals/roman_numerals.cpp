// Convert Roman numerals to decimal values and vice versa
//
// See https://en.wikipedia.org/wiki/Roman_numerals
//
// Note that when converting a Roman numeral string to a decimal value it is
// easier to process the string from right-to-left rather than left-to-right:
//
//  right-to-left : only need the current and previous numeral to decide whether
//                  to add or subtract
//
//  left-to-right : need the current and next two numerals to decide whether to
//                  add or subtract

#include <iomanip>      // For std:setw
#include <iostream>     // For std::cout etc
#include <map>          // For std::map
#include <stdexcept>    // For std::invalid_argument
#include <string>       // For std::string

// A trivial class dealing with Roman numerals
class Roman {
public:
    Roman(std::string roman);
    Roman(unsigned int decimal);

    std::string string() const;
    unsigned int decimal() const;

private:
    std::string str;

    unsigned int string2decimal(std::string roman) const;
    std::string decimal2string(unsigned int decimal) const;
};

// Construct a Roman numeral from a string
Roman::Roman(std::string roman) : str("") {
    // Validate the string by converting to decimal and back again
    str = decimal2string(string2decimal(roman));
}

// Construct a Roman numeral from a decimal number
Roman::Roman(unsigned int decimal) : str("") {
    str = decimal2string(decimal);
}

// Get a string representation of the Roman numeral
std::string Roman::string() const {
    return str;
}

// Get a decimal representation of the Roman numeral
unsigned int Roman::decimal() const {
    return string2decimal(str);
}

// Convert a Roman numeral to a decimal number
unsigned int Roman::string2decimal(std::string roman) const {
    const std::map<char, unsigned int> numerals {
        { 'I',    1 },
        { 'V',    5 },
        { 'X',   10 },
        { 'L',   50 },
        { 'C',  100 },
        { 'D',  500 },
        { 'M', 1000 }
    };

    // Check the input
    if(roman == "") {
        throw(std::invalid_argument("string2decimal: empty string"));
    }

    // Work backwards through the string
    unsigned int decimal {0};
    unsigned int curr    {0}; // value of the current character
    unsigned int prev    {0}; // value of the previous character
    for(auto iter = roman.rbegin(); iter != roman.rend(); iter++) {
        curr = numerals.at(*iter);

        // Additive notation
        if(curr >= prev) {
            decimal += curr;
        }
        // Subtractive notation
        else {
            // Ratio of prev to curr should be 10 or less
            if((curr * 10) < prev) {
                throw(std::invalid_argument("string2decimal: invalid combination (ratio)"));
            }

            // VX, VL, LC, LD and DM are invalid
            if((curr == 5) || (curr == 50) || (curr == 500)) {
                throw(std::invalid_argument("string2decimal: invalid combination (fives)"));
            }

            decimal -= curr;
        }

        // Next iteration
        prev = curr;
    }
    return decimal;
}

// Convert a decimal number to a Roman numeral
std::string Roman::decimal2string(unsigned int decimal) const {
    const std::map<unsigned int, std::string> numerals {
        {    1, "I" },
        {    5, "V" },
        {   10, "X" },
        {   50, "L" },
        {  100, "C" },
        {  500, "D" },
        { 1000, "M" },
    };

    // Check the input
    if(decimal == 0) {
        throw(std::invalid_argument("decimal2string: no Roman numeral for zero"));
    }

    // Repeatedly subtract values, working from largest to smallest
    std::string roman {""};
    for(auto iter = numerals.rbegin(); iter != numerals.rend() && decimal > 0; iter++) {
        // Additive notation - use the current numeral as many times as possible
        while(decimal >= iter->first) {
            roman   += iter->second;
            decimal -= iter->first;
        }

        // Try subtractive notation before moving to the next lower numeral...

        // Subtractive notation using non-adjacent numerals e.g. IX, XC, CM
        if((std::distance(iter, numerals.rend()) > 2) &&
           (iter->second != "D") && (iter->second != "L") && // VL and LD are invalid
           (decimal >= (iter->first - next(iter, 2)->first))) {
            roman   += next(iter, 2)->second;
            roman   += iter->second;
            decimal -= (iter->first - next(iter, 2)->first);
        }

        // Subtractive notation using adjacent numerals e.g. IV, XL, CD
        if((std::distance(iter, numerals.rend()) > 1) &&
           (iter->second != "X") && (iter->second != "C") && (iter->second != "M") && // VX, LC and DM are invalid
           (decimal >= (iter->first - next(iter, 1)->first))) {
            roman   += next(iter, 1)->second;
            roman   += iter->second;
            decimal -= (iter->first - next(iter, 1)->first);
        }
    }
    return roman;
}

// Common test function
void test(std::string roman, unsigned int decimal) {
    std::cout << std::setw(13) << roman << " : ";
    try {
        // Convert decimal number to Roman numeral and vice-versa
        Roman d2r(decimal);
        Roman r2d(roman);
        if((d2r.string() == roman) && (d2r.decimal() == decimal) &&
           (r2d.string() == roman) && (r2d.decimal() == decimal)) {
            std::cout << decimal;
        }
        else {
            std::cout << "bad conversion"; // this should never occur
        }
        std::cout << std::endl;
    }
    catch(std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

int main() {
    // Individual numerals
    std::cout << "Individual numerals:" << std::endl;
    test("I", 1);
    test("V", 5);
    test("X", 10);
    test("L", 50);
    test("C", 100);
    test("D", 500);
    test("M", 1000);
    std::cout << std::endl;

    // Valid combinations for subtractive notation
    std::cout << "Valid combinations for subtractive notation:" << std::endl;
    test("IV", 4);
    test("IX", 9);
    test("XL", 40);
    test("XC", 90);
    test("CD", 400);
    test("CM", 900);
    std::cout << std::endl;

    // Numbers 1 to 10
    std::cout << "Numbers 1 to 10:" << std::endl;
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
    std::cout << std::endl;

    // Various years
    std::cout << "Various years:" << std::endl;
    test("MDCCCLXXXVIII", 1888); // a very long year
    test("MCMIV",         1904); // from Wikipedia
    test("MCMLIV",        1954); // from Wikipedia - as in the trailer for the movie The Last Time I Saw Paris
    test("MCMXC",         1990); // from Wikipedia - used as the title of musical project Enigma's debut album MCMXC a.D., named after the year of its release.
    test("MMXIV",         2014); // from Wikipedia - the year of the games of the XXII (22nd) Olympic Winter Games (in Sochi)
    std::cout << std::endl;

    // Invalid numbers
    std::cout << "Invalid numbers:" << std::endl;
    test("", 0);    // no Roman numeral to represent 0
    std::cout << std::endl;

    // Invalid combinations for subtractive notation
    std::cout << "Invalid combinations for subtractive notation:" << std::endl;
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
    std::cout << std::endl;

    // Valid counterparts to the invalid combinations
    std::cout << "Valid counterparts to the invalid combinations:" << std::endl;
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
    std::cout << std::endl;
}
