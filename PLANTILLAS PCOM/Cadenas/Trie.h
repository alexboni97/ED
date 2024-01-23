#include<vector>
using namespace std;

const int MAXN = 26;

class Trie {
    int prefixes, words;
    vector<Trie *>child;
public:
    Trie() : prefixes(0), words(0), child(MAXN, nullptr) {}
    ~Trie() {
        for (int i = 0; i < MAXN; ++i) 
            delete child[i];
    }
    void add(const char *s) {
        if (*s == '\0') ++words;
        else {
            Trie * t;
            int pos = *s - 'a';
            if (child[pos] == nullptr) {
                t = child[pos] = new Trie();
                t->prefixes = 1;
            }
            else {
                t = child[pos];
                t->prefixes++;
            }
            t->add(s+1);
        }
    }
};