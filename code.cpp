#include <iostream>
#include <vector>
#include <string>
using namespace std;

class TrieNode {
public:
    TrieNode* children[26];
    bool isEndOfWord;

    TrieNode() {
        isEndOfWord = false;
        for (int i = 0; i < 26; i++)
            children[i] = nullptr;
    }
};

class Trie {
private:
    TrieNode* root;

    void dfs(TrieNode* node, string prefix, vector<string>& results) {
        if (node->isEndOfWord)
            results.push_back(prefix);

        for (int i = 0; i < 26; i++) {
            if (node->children[i]) {
                char nextChar = 'a' + i;
                dfs(node->children[i], prefix + nextChar, results);
            }
        }
    }

public:
    Trie() {
        root = new TrieNode();
    }

    void insert(const string& word) {
        TrieNode* current = root;
        for (char ch : word) {
            int index = ch - 'a';
            if (!current->children[index])
                current->children[index] = new TrieNode();
            current = current->children[index];
        }
        current->isEndOfWord = true;
    }

    vector<string> autocomplete(const string& prefix) {
        TrieNode* current = root;
        vector<string> results;

        // Traverse the Trie up to the end of prefix
        for (char ch : prefix) {
            int index = ch - 'a';
            if (!current->children[index])
                return results;  // No words found with this prefix
            current = current->children[index];
        }

        // DFS from here to find all words starting with prefix
        dfs(current, prefix, results);
        return results;
    }
};

int main() {
    Trie trie;

    // Insert some sample words
    trie.insert("hello");
    trie.insert("helium");
    trie.insert("help");
    trie.insert("hero");
    trie.insert("heron");
    trie.insert("heap");

    string prefix;
    cout << "Enter prefix to autocomplete: ";
    cin >> prefix;

    vector<string> suggestions = trie.autocomplete(prefix);

    if (suggestions.empty()) {
        cout << "No suggestions found for prefix '" << prefix << "'.\n";
    } else {
        cout << "Suggestions:\n";
        for (const string& word : suggestions) {
            cout << word << endl;
        }
    }

    return 0;
}
