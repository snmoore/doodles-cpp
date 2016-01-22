// Determine if two rectangles overlap
//
// Note that the simple, classic approach treats touching rectangles as
// overlapping i.e. the edges have finite thickness. The bounding box approach
// treats touching rectangles as non-overlapping i.e. the edges have no
// thickness.

#include <iostream>     // For cout etc
#include <vector>       // For vector

using namespace std;

// A rectangle defined by diametrically opposite corners
class Rect {
private:
    struct Corner {
        unsigned int x;
        unsigned int y;
    };

    Corner a;   // [0,0] is the upper left
    Corner b;   // with a.x <= b.x and a.y <= b.y

public:
    Rect() :a({0, 0}), b({0, 0}) {};                        // construct an empty rectangle
    Rect(Corner a, Corner b) :a(a), b(b) {};                // construct a rectangle defined by diametrically opposite corners

    static void draw(const Rect& r1, const Rect& r2);       // draw two rectangles using simple ASCII art
    void draw(vector<vector<char>>& grid) const;            // draw a rectangle into a simple ASCII art grid

    static bool overlap(const Rect& r1, const Rect& r2);    // do the rectangles r1 and r2 overlap? (simple, classic approach)
    static bool overlap_bounding(const Rect& r1, const Rect& r2);   // do the rectangles r1 and r2 overlap? (using a bounding box approach)
};

// Draw two rectangles using simple ASCII art
void Rect::draw(const Rect& r1, const Rect& r2) {
    // Will draw from [0, 0] even if neither r1 nor r2 is located there
    int width  = max(r1.b.x, r2.b.x) + 1;
    int height = max(r1.b.y, r2.b.y) + 1;

    // Create a two dimensional grid with origin [0, 0] at the upper left
    vector<vector<char>> grid(height, vector<char>(width, ' '));

    // Draw both rectangles into the grid
    r1.draw(grid);
    r2.draw(grid);

    // Display the grid
    for(auto row : grid) {
        for(auto col : row) {
            cout << col;
        }
        cout << endl;
    }
}

// Draw a rectangle into a simple ASCII art grid
void Rect::draw(vector<vector<char>>& grid) const {
    // Fill in the horizontal edges
    for(unsigned int col = a.x; col < b.x; col++) {
        grid[a.y][col] = '-';   // upper edge
        grid[b.y][col] = '-';   // lower edge
    }

    // Fill in the vertical edges
    for(unsigned int row = a.y; row < b.y; row++) {
        grid[row][a.x] = '|';   // left edge
        grid[row][b.x] = '|';   // right edge
    }

    // Draw the corners into the grid
    grid[a.y][a.x] = '+';       // upper left
    grid[b.y][b.x] = '+';       // lower right
    grid[a.y][b.x] = '+';       // upper right
    grid[b.y][a.x] = '+';       // lower left
}


// Do the rectangles r1 and r2 overlap? (simple, classic approach)
//
// Note this treats touching rectangles as overlapping i.e. the edges have
// finite thickness
bool Rect::overlap(const Rect& r1, const Rect& r2) {
    // Is one rectangle completely on the left side of the other?
    if((r1.b.x < r2.a.x) || (r1.a.x > r2.b.x)) {
        return false;
    }

    // Is one rectangle completely above the other?
    if((r1.b.y < r2.a.y) || (r1.a.y > r2.b.y)) {
        return false;
    }

    return true;
}

// Do the rectangles r1 and r2 overlap? (using a bounding box approach)
//
// Note this treats touching rectangles as non-overlapping i.e. the edges have
// no thickness
bool Rect::overlap_bounding(const Rect& r1, const Rect& r2) {
    bool overlap_horizontally = false;
    bool overlap_vertically   = false;

    // Find the edges of a bounding box containing both rectangles
    unsigned int left  = r1.a.x < r2.a.x ? r1.a.x : r2.a.x; // left  edge (smallest x value)
    unsigned int right = r1.b.x > r2.b.x ? r1.b.x : r2.b.x; // right edge (largest  x value)
    unsigned int upper = r1.a.y < r2.a.y ? r1.a.y : r2.a.y; // upper edge (smallest y value)
    unsigned int lower = r1.b.y > r2.b.y ? r1.b.y : r2.b.y; // lower edge (largest  y value)

    cout << "Left:  " << left  << endl;
    cout << "Right: " << right << endl;
    cout << "Upper: " << upper << endl;
    cout << "Lower: " << lower << endl;

    // Look for an overlap in the x dimension i.e. horizontal
    // - overlap if width of bounding box < sum of widths of both rectangles
    if((right - left) < ((r1.b.x - r1.a.x) + (r2.b.x - r2.a.x))) {
        overlap_horizontally = true;
        cout << "Overlap horizontally" << endl;
    }

    // Look for an overlap in the y dimension i.e. vertical
    // - overlap if height of bounding box < sum of heights of both rectangles
    if((lower - upper) < ((r1.b.y - r1.a.y) + (r2.b.y - r2.a.y))) {
        overlap_vertically = true;
        cout << "Overlap vertically" << endl;
    }

    return overlap_horizontally && overlap_vertically;
}

int main() {
    Rect r1;
    Rect r2;
    bool result;

    // No overlap in any dimension
    r1 = { {0, 0}, {2, 3} };
    r2 = { {5, 4}, {8, 6} };
    cout << endl << "No overlap in any dimension:" << endl;
    Rect::draw(r1, r2);
    result = Rect::overlap(r1, r2);
    cout << "Overlap: " << boolalpha << result << endl;

    // Touching at a corner
    r1 = { {0, 0}, {2, 3} };
    r2 = { {2, 3}, {8, 6} };
    cout << endl << "Touching at a corner:" << endl;
    Rect::draw(r1, r2);
    result = Rect::overlap(r1, r2);
    cout << "Overlap: " << boolalpha << result << endl;

    // Touching along a horizontal edge
    r1 = { {0, 0}, {2, 3} };
    r2 = { {1, 3}, {4, 6} };
    cout << endl << "Touching along a horizontal edge:" << endl;
    Rect::draw(r1, r2);
    result = Rect::overlap(r1, r2);
    cout << "Overlap: " << boolalpha << result << endl;

    // Touching along a vertical edge
    r1 = { {0, 0}, {2, 3} };
    r2 = { {2, 1}, {4, 6} };
    cout << endl << "Touching along a vertical edge:" << endl;
    Rect::draw(r1, r2);
    result = Rect::overlap(r1, r2);
    cout << "Overlap: " << boolalpha << result << endl;

    // Partial overlap in the x dimension i.e. horizontal
    r1 = { {0, 0}, {2, 3} };
    r2 = { {1, 4}, {4, 6} };
    cout << endl << "Partial overlap in the x dimension i.e. horizontal:" << endl;
    Rect::draw(r1, r2);
    result = Rect::overlap(r1, r2);
    cout << "Overlap: " << boolalpha << result << endl;

    // Partial overlap in the y dimension i.e. vertical
    r1 = { {0, 0}, {2, 3} };
    r2 = { {5, 2}, {8, 4} };
    cout << endl << "Partial overlap in the y dimension i.e. vertical:" << endl;
    Rect::draw(r1, r2);
    result = Rect::overlap(r1, r2);
    cout << "Overlap: " << boolalpha << result << endl;

    // Complete overlap in the x dimension i.e. horizontal
    r1 = { {0, 0}, {10, 4} };
    r2 = { {2, 6}, {8, 9} };
    cout << endl << "Complete overlap in the x dimension i.e. horizontal:" << endl;
    Rect::draw(r1, r2);
    result = Rect::overlap(r1, r2);
    cout << "Overlap: " << boolalpha << result << endl;

    // Complete overlap in the y dimension i.e. vertical
    r1 = { {0, 0}, {4, 10} };
    r2 = { {6, 3}, {9, 7} };
    cout << endl << "Complete overlap in the y dimension i.e. vertical:" << endl;
    Rect::draw(r1, r2);
    result = Rect::overlap(r1, r2);
    cout << "Overlap: " << boolalpha << result << endl;

    // Overlap in both x and y dimensions i.e. horizontal and vertical
    r1 = { {2, 1}, {10, 6} };
    r2 = { {1, 4}, {8, 8} };
    cout << endl << "Overlap in both x and y dimensions i.e. horizontal and vertical:" << endl;
    Rect::draw(r1, r2);
    result = Rect::overlap(r1, r2);
    cout << "Overlap: " << boolalpha << result << endl;

    // Coincident rectangles
    r1 = { {1, 1}, {4, 4} };
    r2 = { {1, 1}, {4, 4} };
    cout << endl << "Coincident rectangles:" << endl;
    Rect::draw(r1, r2);
    result = Rect::overlap(r1, r2);
    cout << "Overlap: " << boolalpha << result << endl;

    // Empty rectangles
    r1 = { {0, 0}, {0, 0} };
    r2 = { {0, 0}, {0, 0} };
    cout << endl << "Empty rectangles:" << endl;
    Rect::draw(r1, r2);
    result = Rect::overlap(r1, r2);
    cout << "Overlap: " << boolalpha << result << endl;
}
