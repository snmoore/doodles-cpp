// Reverse words and sentences

#include <algorithm>    // For std::reverse
#include <cctype>       // For isspace
#include <iostream>     // For std:cout etc
#include <sstream>      // For std::stringstream
#include <stack>        // For std::stack
#include <string>       // For std::string
#include <utility>      // For std::swap

// Reverse a word in place, using a temporary variable
std::string& word_inplace_temp(std::string& word) {
    size_t left;
    size_t right;
    char temp;
    for(left = 0, right = word.size() - 1; left < right; left++, right--) {
        temp        = word[right];
        word[right] = word[left];
        word[left]  = temp;
    }

    return word; // allows for reversed = word_inplace_temp(word);
}

// Reverse a word in place, using XOR
std::string& word_inplace_xor(std::string& word) {
    size_t left;
    size_t right;
    for(left = 0, right = word.size() - 1; left < right; left++, right--) {
        word[right] ^= word[left];
        word[left]  ^= word[right];
        word[right] ^= word[left];
    }

    return word; // allows for reversed = word_inplace_xor(word);
}

// Reverse a word in place, using pointers
std::string& word_inplace_pointer(std::string& word) {
    char* left;
    char* right;
    char temp;
    for(left = &word[0], right = left + word.size() - 1; left < right; left++, right--) {
        temp   = *right;
        *right = *left;
        *left  = temp;
    }

    return word; // allows for reversed = word_inplace_pointer(word);
}

// Reverse a word in place, using swap
std::string& word_inplace_swap(std::string& word) {
    size_t left;
    size_t right;
    for(left = 0, right = word.size() - 1; left < right; left++, right--) {
        std::swap(word[left], word[right]);
    }

    return word; // allows for reversed = word_inplace_swap(word);
}

// Reverse a word in place, using reverse
std::string& word_inplace_reverse(std::string& word) {
    std::reverse(word.begin(), word.end());

    return word; // allows for reversed = word_inplace_reverse(word);
}

// Reverse a const word, using an iterator
std::string word_const_iterator(const std::string& word) {
    std::string reversed {""};
    for(auto iter = word.rbegin(); iter != word.rend(); iter++) {
        reversed += *iter;
    }
    return reversed;
}

// Reverse a const word, using reverse
std::string word_const_reverse(const std::string& word) {
    std::string reversed {word};
    std::reverse(reversed.begin(), reversed.end());
    return reversed;
}

// Reverse the order of words in a sentence, in place
std::string& sentence_inplace(std::string& sentence) {
    // Reverse each word in the sentence
    int start {-1};
    for(size_t i = 0; i < sentence.size(); i++) {
        if(isspace(sentence[i])) {
            if(start != -1) {
                // Found the end of a word, reverse it
                std::string word = sentence.substr(start, i - start);
                word_inplace_reverse(word);
                sentence.replace(start, i - start, word);

                // Look for the next word
                start = -1;
            }
        }
        else {
            if(start == -1) {
                // Found the start of a word
                start = i;
            }
        }
    }

    // Reverse the final word
    if(start != -1) {
        std::string word = sentence.substr(start, sentence.size() - 1);
        word_inplace_reverse(word);
        sentence.replace(start, sentence.size() - 1, word);
    }

    // Reverse the entire text
    word_inplace_reverse(sentence);

    return sentence;
}

// Reverse the order of words in a const sentence, using insert
std::string sentence_const_insert(const std::string& sentence) {
    std::string reversed {};

    // Extract each word via a stringstream and prepend to a string
    std::stringstream stream(sentence);
    while(!stream.eof()) {
        std::string word {};
        stream >> word;
        reversed.insert(0, word);
        reversed.insert(0, " ");
    }

    // Remove the extraneous space at the front of the string
    reversed.erase(0, 1);

    return reversed;
}

// Reverse the order of words in a const sentence, using a stack
std::string sentence_const_stack(const std::string& sentence) {
    std::string reversed {};

    // Extract each word via a stringstream and push onto a stack
    std::stack<std::string> words {};
    std::stringstream stream(sentence);
    while(stream) {
        std::string word {};
        stream >> word;
        words.push(word);
    }

    // Build the reversed sentence from the stack
    while(!words.empty()) {
        reversed += words.top();
        reversed += " ";
        words.pop();
    }

    // Remove the extraneous space at the front of the string
    reversed.erase(0, 1);

    return reversed;
}

// Test a given implementation
void test(std::string& (*function)(std::string& text), std::string& text, const std::string& label) {
    std::cout << label << ":" << std::endl;
    std::cout << text << " --> " << function(text) << std::endl;
    std::cout << std::endl;
}
void test(std::string (*function)(const std::string& word), const std::string& text, const std::string& label) {
    std::cout << label << ":" << std::endl;
    std::cout << text << " --> " << function(text) << std::endl;
    std::cout << std::endl;
}

// Test reversing individual words
void test_words() {
    // Test reversing words in place
    std::string word {"Hello"};
    test(word_inplace_temp,    word, "Reverse a word in place, using a temporary variable");
    test(word_inplace_xor,     word, "Reverse a word in place, using XOR");
    test(word_inplace_pointer, word, "Reverse a word in place, using pointers");
    test(word_inplace_swap,    word, "Reverse a word in place, using swap");
    test(word_inplace_reverse, word, "Reverse a word in place, using reverse");

    // Test reversing const words
    test(word_const_iterator, "World", "Reverse a const word, using an iterator");
    test(word_const_reverse,  "World", "Reverse a const word, using reverse");
}

// Test reversing sentences
void test_sentences() {
    // Test reversing sentences in place
    std::string sentence {"Reverse the order of words in a sentence"};
    test(sentence_inplace, sentence, "Reverse the order of words in a sentence, in place");

    // Test reversing const sentences
    test(sentence_const_insert, "Reverse the order of words in a sentence", "Reverse the order of words in a const sentence, using insert");
    test(sentence_const_stack,  "Reverse the order of words in a sentence", "Reverse the order of words in a const sentence, using a stack");
}

int main() {
    // Test reversing individual words
    test_words();

    // Test reversing sentences
    test_sentences();
}
