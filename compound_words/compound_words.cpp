// Find the longest compound word in a list that is a concatenation of other
// words in the list.
//
// See https://github.com/NodePrime/quiz (from which word.list was obtained).
//
// This solution is valid for simple compounds words of the form xxxyyy
// where xxx, yyy and xxxyyy are all present in the list of words.
//
// This solution is not valid for complex compounds words such as xxxyyyzzz
// where xxx, yyy, zzz and xxxyyyzzz are all present in the list of words, but
// neither xxxyyy nor yyyzzz are present.
//
// Given the file word.list as input, this returns the following typical results
// on a Core i7 3770T with 16GB RAM:
//      Longest compound word: antidisestablishmentarianisms (29)
//
//      Get list of words: 47ms
//      Build trie:        90ms
//      Find candidates:   60ms
//      Find longest:      40ms
//      Clean up:          87ms
//      Total time:        325ms
//
// This solution uses three main steps:
//      1. Build a trie containing all of the words
//      2. Find candidate compound words and put them into a queue
//      3. Find the longest compound word from the candidates.
//
// Step 1
// ------
// Build a 26-ary tree (using the letters a to z) that contains the complete
// list of words. As the trie is built, a flag is set on each letter that marks
// the end of a word.
//
// For example, given xxx, yyy and xxxyyy as the list of words, the trie will
// look something like:
//
//                 root         -- represents the empty string
//                 /  \
//                x    y
//               /      \
//              x        y
//             /          \
//            x!           y!   -- ! marks the end of a word
//           /
//          y
//         /
//        y
//       /
//      y!                      -- ! marks the end of a word
//
// Step 2
// ------
// Compare each word in the list of words against the trie, looking for possible
// compounds words ('candidates') e.g. where a flag (that marks the end of a
// word) is encountered in the trie before the end of the word is reached.
//
// For example, whilst matching xxxyyy against the above tree, an end of word
// flag is encountered at the end of xxx, hence xxxyyy is a candidate compound
// word.
//
// Candidate compound words are added to a queue of candidates, together with
// their suffix portion e.g. for the above example {xxxyyy, yyy} is pushed onto
// the queue.
//
// Step 3
// ------
// Process each candidate in the queue of candidates, checking the suffix
// portion against the trie. If the suffix portion is a valid word in the trie
// then a valid compound word has been identified.
//
// For the above example {xxxyyy, yyy} is a candidate in the queue. The suffix
// portion yyy is checked against the trie - it is present in the trie, and the
// flag is set on the final y marking the end of a word. Hence we now know that
// xxx is a valid word in the trie (from step 2) and yyy is a valid word in the
// trie (from step 3), hence xxxyyy is a valid compound word.
//
// Check the length of each valid compound word against the longest seen so far,
// and update the longest if longer.
//
//
// Issues / to do:
//      1. Use tolower() or similar in case the input word list uses mixed case
//      2. Add some safety checks e.g. check for null trie, queue etc
//      3. Use a dynamic structure instead of the fixed size array of children
//         - minimise the size complexity of the trie
//         - maybe use a map or list?
//         - might increase runtime?
//      4. Consider sorting candidates by longest length
//         - consider the longest candidate first
//         - discard candidates shorter than the longest valid compound word
//           seen so far
//         - maybe use a map with the length as the key?
//         - maybe not worth it, given the trie creation and deletion times
//           are larger (but see 3)?
//      5. Identify a solution to the complex case outlined above
//         - where xxx, yyy, zzz and xxxyyyzzz are all present in the list of
//           words, but neither xxxyyy nor yyyzzz are present.

#include <chrono>       // For high_resolution_clock
#include <fstream>      // For ifstream
#include <iostream>     // For cout etc
#include <queue>        // For queue
#include <string>       // For string
#include <vector>       // For vector

using namespace std;
using namespace std::chrono;

// A node in a 26-ary trie of words
struct Node {
    char letter;        // a..z
    bool isword;        // flag - true if this letter marks the end of a word
    Node* children[26]; // one element each for a..z

    Node()            : letter{},       isword{false}, children{nullptr} {}
    Node(char letter) : letter{letter}, isword{false}, children{nullptr} {}
    ~Node() { for(auto child : children) { delete child; } }
};

// A candidate compound word and its suffix portion
struct Candidate {
    string word;        // e.g. "greenfield"
    string suffix;      // e.g. "field"
};

// Get the list of words
vector<string>* get_word_list() {
    // Store each word in a vector
    vector<string>* words = new vector<string>;

    // Read words line-by-line from a file
    ifstream file("word.list");
    if(!file) {
        throw("Failed to open word.list");
    }
    string word {};
    while(getline(file, word)) {
        words->push_back(word);
    }
    file.close();

    return words;
}

// Compute array index 0..25 from letter a..z
int index(char letter) {
    if(letter < 'a' || letter > 'z') {
        throw out_of_range("index");
    }
    return letter - 'a';
}

// Build a trie containing all of the words
Node* build_trie(const vector<string>& words) {
    // The root node represents the empty string
    Node* root = new Node;

    // Insert each word into the trie
    for(auto word : words) {
        // Insert each letter of the word into the trie
        Node* node = root;
        for(size_t i = 0; i < word.size(); i++) {
            // Get the index into the array of children i.e. 0..25 for a..z
            int idx = index(word[i]);

            // Create new child nodes as necessary
            if(node->children[idx] == nullptr) {
                node->children[idx] = new Node(word[i]);
            }

            // Set a flag in the trie if this is the end of the word
            if(i == (word.size() - 1)) {
                node->children[idx]->isword = true;
            }

            // Move down the trie
            node = node->children[idx];
        }
    }

    return root;
}

// Recursively print nodes in the trie
void print_node(const Node* node) {
    if(node != nullptr) {
        // Print this node
        cout << node->letter;
        if(node->isword) {
            cout << endl;
        }

        // Recursively print the child nodes
        for(auto child : node->children) {
            print_node(child);
        }
    }
}

// Find a word in the trie and update candidate compound words
bool find_word_update_candidates(const string& word, const Node& trie, queue<Candidate>* candidates) {
    // Match each letter of the word against the trie
    const Node* node = &trie;
    for(size_t i = 0; i < word.size(); i++) {
        // Get the index into the array of children i.e. 0..25 for a..z
        int idx = index(word[i]);

        // The letter must match against the trie
        if((node->children[idx]         == nullptr) ||
           (node->children[idx]->letter != word[i])) {
            return false;   // word is not present in the tree
        }

        // Reached the end of the word?
        if(i == (word.size() - 1)) {
            // If the flag is not set in the trie to mark the end of a word,
            // then this word is not really in the trie
            return node->children[idx]->isword;
        }
        // Look for possible compound words (see check_suffix)?
        else if(candidates) {
            // Does the current letter in the trie mark the end of a word?
            if (node->children[idx]->isword) {
                // Found a new candidate compound word, add it to the queue
                string suffix = word.substr(i+1, word.size()-1);
                candidates->push({word, suffix});
            }
        }

        // Move down the trie
        node = node->children[idx];
    }

    throw("Should never get here");
}

// Find candidate compound words in the trie, storing candidates in a queue
queue<Candidate>* find_candidates(const vector<string>& words, const Node& trie) {
    // Store candidate compound words in a queue
    queue<Candidate>* candidates = new queue<Candidate>;

    // Compare each word against the trie, looking for possible compound words
    for(auto word : words) {
        find_word_update_candidates(word, trie, candidates);
    }

    return candidates;
}

// Check a word suffix exists in the trie
bool check_suffix(const string& suffix, const Node& trie) {
    // To avoid code duplication, re-use find_word_update_candidates(), but do
    // not look for new compounds words nor update the candidates queue
    return find_word_update_candidates(suffix, trie, nullptr);
}

// Find the longest compound word from the candidates
string find_longest(queue<Candidate>* candidates, const Node& trie) {
    string longest {};
    while(!candidates->empty()) {
        // Pop the candidate compound word from the queue
        Candidate candidate = candidates->front();
        candidates->pop();

        // Check its suffix is also in the trie
        bool found = check_suffix(candidate.suffix, trie);
        if(found) {
            // Word and its suffix are both in the queue, is it the longest?
            if(candidate.word.size() > longest.size()) {
                longest = candidate.word;
            }
        }
    }

    return longest;
}

int main() {
    auto t0 = high_resolution_clock::now();

    // Preparation: Get the list of words
    vector<string>* words = get_word_list();

    auto t1 = high_resolution_clock::now();

    // Step 1: Build a trie containing all of the words
    Node* trie = build_trie(*words);

    auto t2 = high_resolution_clock::now();

    // Step 2: Find candidate compound words and put them into a queue
    queue<Candidate>* candidates = find_candidates(*words, *trie);

    auto t3 = high_resolution_clock::now();

    // Step 3: Find the longest compound word from the candidates
    string longest = find_longest(candidates, *trie);

    auto t4 = high_resolution_clock::now();

    // Clean up
    delete words;
    delete trie;
    delete candidates;

    auto t5 = high_resolution_clock::now();

    // Results
    cout << endl << "Longest compound word: " << longest << " (" << longest.size() << ")" << endl << endl;
    cout << "Get list of words: " << duration_cast<milliseconds>(t1-t0).count() << "ms" << endl;
    cout << "Build trie:        " << duration_cast<milliseconds>(t2-t1).count() << "ms" << endl;
    cout << "Find candidates:   " << duration_cast<milliseconds>(t3-t2).count() << "ms" << endl;
    cout << "Find longest:      " << duration_cast<milliseconds>(t4-t3).count() << "ms" << endl;
    cout << "Clean up:          " << duration_cast<milliseconds>(t5-t4).count() << "ms" << endl;
    cout << "Total time:        " << duration_cast<milliseconds>(t5-t0).count() << "ms" << endl;
}
