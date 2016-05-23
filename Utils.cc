#include "Utils.hh"
#include <iostream>

namespace utils {
    bool contains(string a, string b) {
        istringstream issB(b);
        string wordB;
        while (issB >> wordB) {
            istringstream issA(a);
            string wordA;
            bool found = false;
            while (issA >> wordA) {
                if (wordA.find_first_of(".!?,;:") == wordA.length() - 1)
                    wordA.erase(wordA.length() - 1, 1);
                if (wordA == wordB) found = true;
            }
            if (!found) return false;
        }
        return true;
    }

    void stringUppercase(string& input) {
        for (int i = 0; i < input.length(); ++i) {
            if (!isupper(input[i])) input[i] = toupper(input[i]);
        }
    }

    bool startsWith(string a, string b) {
        if (b.size() > a.size()) return false;
        return std::equal(a.begin(), a.begin() + b.size(), b.begin());
    }

    bool startsWithEquals(string a, string b) {
        if (b.size() > a.size()) return false;
        return std::equal(a.begin(), a.begin() + b.size(), b.begin())
               and (a.size() == b.size() or a[b.size()] == ' ');
    }

    bool endsWith(string a, string b) {
        if (b.size() > a.size()) return false;
        return std::equal(a.begin() + a.size() - b.size(), a.end(), b.begin());
    }

    bool betweenPar(string query, int position) {
        int state = 0;
        for (int i = 0; i < position; ++i) {
            if (query[i] == '(') state++;
            if (query[i] == ')') state--;
        }
        return state != 0;
    }

    void trimString(string& query) {
        int pos = query.find("  ");
        while (pos != string::npos) {
            query.erase(pos, 1);
            pos = query.find("  ");
        }
        while (query[0] == ' ') query.erase(0, 1);
        while (query.length() > 0 and query[query.length() - 1] == ' ')
            query.erase(query.length() - 1, 1);
    }

    void trimStringComplex(string& query) {
        while (query[0] == ' ' or query[0] == '\"') query.erase(0, 1);
        while (query[query.length() - 1] == ' '  or query[query.length() - 1] == '\"')
            query.erase(query.length() - 1, 1);
    }

    void printError() {
        cout << "error" << endl;
    }
}