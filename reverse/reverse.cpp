// Reverse words and sentences

#include <algorithm>    // For reverse
#include <cctype>       // For isspace
#include <iostream>     // For cout etc
#include <sstream>      // For stringstream
#include <string>       // For string
#include <vector>       // For vector

using namespace std;

// Reverse a word using swap
string word_swap(string s) {
    for(size_t left = 0, right = s.size() - 1; left < right; left++, right--) {
        swap(s[left], s[right]);
    }
    return s;
}

// Reverse a word using an iterator
string word_iterator(string s) {
    // Note: could just use auto rather than string::iterator
    string reversed;
    for(string::iterator iter = s.end(); iter != s.begin(); iter--) {
        reversed += *iter;
    }
    reversed += *s.begin();
    return reversed;
}

// Reverse a word using a reverse iterator
string word_riterator(string s) {
    // Note: could just use auto rather than string::iterator
    string reversed;
    for(string::reverse_iterator iter = s.rbegin(); iter != s.rend(); iter++) {
        reversed += *iter;
    }
    return reversed;
}

// Reverse a word using algorithm
string word_algorithm(string s) {
    reverse(s.begin(), s.end());
    return s;
}
string& word_algorithm_in_place(string& s) {
    reverse(s.begin(), s.end());
    return s;
}

// Reverse the order of words in a sentence by splitting into words and recombining
string sentence_split(string s) {
    // Split the sentence into words and add to a vector
    stringstream stream(s);
    vector<string> words {};
    while(stream) {
        string word {};
        stream >> word;
        words.push_back(word);
    }

    // Reverse the vector
    reverse(words.begin(), words.end());

    // Recombine into a single string
    string reversed;
    for(auto word : words) {
        reversed += word + " ";
    }

    return reversed;
}

// Reverse the order of words in a sentence by looping
string sentence_loop(string s) {
    // Find each word in the sentence and reverse it
    int start = -1;
    for(size_t i = 0; i < s.size(); i++) {
        if(isspace(s[i])) {
            if(start == -1) {
                // In the middle of whitespace
                continue;
            }
            else {
                // Found the end of a word, reverse it
                string word = s.substr(start, i - start);
                string rword = word_algorithm_in_place(word);
                s.replace(start, i - start, rword);

                // Look for a new word
                start = -1;
            }
        }
        else {
            if(start == -1) {
                // Found the start of a word
                start = i;
            }
            else {
                // In the middle of a word
                continue;
            }
        }
    }

    // Reverse the final word
    if(start != -1) {
        string word = s.substr(start, s.size() - start);
        string rword = word_algorithm_in_place(word);
        s.replace(start, s.size() - start, rword);
    }

    // Reverse all of the characters in the sentence
    return word_algorithm(s);
}

int main() {
    string word     = "Hello";
    string sentence = "Reverse the order of words in a sentence";

    cout << "Reverse a word using swap:" << endl;
    cout << word << " -> " << word_swap(word) << endl << endl;

    cout << "Reverse a word using an iterator:" << endl;
    cout << word << " -> " << word_iterator(word) << endl << endl;

    cout << "Reverse a word using a reverse iterator:" << endl;
    cout << word << " -> " << word_riterator(word) << endl << endl;

    cout << "Reverse a word using algorithm:" << endl;
    cout << word << " -> " << word_algorithm(word) << endl << endl;

    cout << "Reverse the order of words in a sentence by splitting into words and recombining:" << endl;
    cout << sentence << " -> " << sentence_split(sentence) << endl << endl;

    cout << "Reverse the order of words in a sentence by looping:" << endl;
    cout << sentence << " -> " << sentence_loop(sentence) << endl << endl;
}
