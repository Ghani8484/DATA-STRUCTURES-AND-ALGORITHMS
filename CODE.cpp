#include <iostream>
#include <unordered_map>
#include<vector>
#include <string>
using namespace std;

// TrieNode class represents a node in the Trie
class TrieNode {
public:
    unordered_map<char, TrieNode*> children;  // Map to store child nodes
    bool is_end_of_word;  // Flag to indicate the end of a word

    // Constructor to initialize the TrieNode
    TrieNode() : is_end_of_word(false) {}
};

// Trie class represents a Trie data structure
class Trie {
    TrieNode* root;  // Root node of the Trie

public:
    // Constructor to initialize the Trie
    Trie() {
        root = new TrieNode();
    }

    // Function to insert a word into the Trie
    void insertWord(const string& word) {
        TrieNode* node = root;
        for (char ch : word) {
            // If the character is not present in children, add a new node
            if (node->children.find(ch) == node->children.end()) {
                node->children[ch] = new TrieNode();
            }
            node = node->children[ch];
        }
        node->is_end_of_word = true;  // Mark the end of the inserted word
    }

    // Function to search for a word in the Trie
    bool searchWord(const string& word) {
        TrieNode* node = root;
        for (char ch : word) {
            // If the character is not present in children, the word is not in the Trie
            if (node->children.find(ch) == node->children.end()) {
                return false;
            }
            node = node->children[ch];
        }
        return node->is_end_of_word;  // Check if the last node represents the end of a word
    }

    // Helper function for auto-completion suggestions
    void autoCompleteHelper(TrieNode* node, string& current, vector<string>& result) {
        // If the current node represents the end of a word, add it to the result
        if (node->is_end_of_word) {
            result.push_back(current);
        }
        // Recursively explore children nodes
        for (auto& child : node->children) {
            current.push_back(child.first);
            autoCompleteHelper(child.second, current, result);
            current.pop_back();
        }
    }

    // Function to get auto-completion suggestions based on a prefix
    vector<string> autoComplete(const string& prefix) {
        TrieNode* current = root;
        // Traverse the Trie to the node representing the last character of the prefix
        for (int i = 0; i < prefix.length(); ++i) {
            char ch = tolower(prefix[i]);
            if (current->children.find(ch) == current->children.end()) {
                return vector<string>();  // Prefix not found, return empty suggestions
            }
            current = current->children[ch];
        }

        vector<string> result;
        string currentWord = prefix;
        autoCompleteHelper(current, currentWord, result);  // Get suggestions
        return result;
    }
};

// Function to display menu options
void displayOptions() {
    cout << "\nOptions:\n";
    cout << "1. Add a word to the Custom Dictionary\n";
    cout << "2. Search for a word in the Custom Dictionary\n";
    cout << "3. Get word suggestions based on a prefix\n";
    cout << "4. Exit\n";
}

int main() {
    Trie customDictionary;
    char option;
    do {
        displayOptions();
        cout << "Enter your option (1-4): ";
        cin >> option;

        switch (option) {
            case '1': {
                cout << "Enter a word to add to the Custom Dictionary: ";
                string word;
                cin >> word;
                customDictionary.insertWord(word);
                break;
            }
            case '2': {
                cout << "Enter a word to search: ";
                string word;
                cin >> word;
                cout << "Is '" << word << "' in the Custom Dictionary? " << boolalpha << customDictionary.searchWord(word) << endl;
                break;
            }
            case '3': {
                cout << "Enter a prefix to get word suggestions: ";
                string prefix;
                cin >> prefix;
                auto suggestions = customDictionary.autoComplete(prefix);
                cout << "Word suggestions for '" << prefix << "': " << endl;
                for (const auto& suggestion : suggestions) {
                    cout << suggestion << endl;
                }
                cout << endl;
                break;
            }
            case '4':
                cout << "Exiting the application.\n";
                break;
            default:
                cout << "Invalid option. Please enter a valid choice.\n";
        }

    } while (option != '4');

    return 0;
}
