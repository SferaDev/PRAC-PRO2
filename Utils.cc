#include "Utils.hh"
#include <iostream>

namespace utils {
    bool contains(string input, string query) {
        formatString(input);
        istringstream iss(input);
        string word;
        while (iss >> word) {
            if (word.find_first_of(".!?,;:") == word.length() - 1)
                word.erase(word.length() - 1, 1);
            if (word == query) return true;
        }
        return false;
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

    void formatString(string& query) {
        trimString(query);
        int pos = query.find_first_of(".!?,;:", 1);
        while (pos != string::npos) {
            if (pos + 1 < query.length() and query[pos + 1] != ' ')
                query.insert(pos + 1, " ");
            while (query[pos - 1] == ' ') query.erase(pos - 1, 1);
            pos = query.find_first_of(".!?,;:", pos + 1);
        }
    }

    void printError() {
        cout << "error" << endl;
    }
}