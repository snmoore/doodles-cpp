// Print a diamond for a character between A and Z
//
// E.g. the diamond constructed for 'C' prints:
//      A
//     B B
//    C   C
//     B B
//      A
//
// And the diamond constructed for 'E' prints:
//        A
//       B B
//      C   C
//     D     D
//    E       E
//     D     D
//      C   C
//       B B
//        A

// Further considerations:
//
// What if the caller supplies a whitespace or digit or punctation character?
// - the diamond may not make much sense
//
// This is currently only valid for ASCII due to use of char and curr - 'A' etc
// - consider UTF8, UTF16, UCS2 etc
//
// Consider the performance implications
// - lots of string operations, possibly lots of creation and copying
// - use a reverse loop for the lower half, rather than std::reverse then loop
// - reflect left/right as well as upper/lower
//
// Other approaches
// - line building could be done in 1 or 2 steps using sprintf and %*s or similar
// - allocate a 2-d array, initialise with spaces, then just fill in the diagonals

#include <algorithm>
#include <iostream>
#include <vector>
#include "Diamond.hpp"

int main()
{
    Diamond diamond('E');
    std::cout << diamond.Print();
}

Diamond::Diamond(char c)
{
    this->c = c;
}

std::string Diamond::Print()
{
    // Stores the lines in the upper half of the diamond
    std::vector<std::string> lines;

    // Generate and store each line for the upper half of the diamond
    for(char curr = 'A'; curr <= this->c; curr++)
    {
        std::string line;

        // Inset before the 1st letter on a line
        int inset = this->c - curr;

        // Level below the 1st line: A=0, B=1, C=2, D=3, E=4 etc
        int level = curr - 'A';
        if(level == 0)
        {
            // Generate the whole line - it contains only 1 letter
            line += std::string(inset, ' ') + curr + "\n";
        }
        else
        {
            // Generate the left side of the line
            line += std::string(inset, ' ') + curr;

            // Gap between the 1st and second letters on a line
            int gap = (2 * level) - 1;

            // Generate the right side of the line
            line += std::string(gap, ' ') + curr + "\n";
        }

        // Store the line
        lines.push_back(line);
    }

    // Build the upper half of the diamond
    std::string diamond;
    for(auto line : lines)
    {
        diamond += line;
    }

    // Avoid duplicating the middle line
    lines.pop_back();

    // Build the lower half of the diamond, as a mirror image of the upper half
    std::reverse(lines.begin(), lines.end());
    for(auto line : lines)
    {
        diamond += line;
    }

    return diamond;
}
