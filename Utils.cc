#include "Utils.hh"
#include <iostream>

namespace utils {
    bool contains(string a, string b) {
        if (a.empty() or b.empty()) return false;
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

    bool containsConsecutive(string a, string b) {
        if (a.empty() or b.empty()) return false;
        int pos = a.find(b);
        bool found = false;
        while (pos != string::npos) {
            if (pos > 0 and a[pos - 1] != ' ') found = false;
            else if (pos + b.length() < a.size() and a[pos + b.length()] != ' ') found = false;
            else return true;
            pos = a.find(b, pos + 1);
        }
        return false;
    }

    void stringUppercase(string &input) {
        for (int i = 0; i < input.length(); ++i) {
            if (!isupper(input[i])) input[i] = toupper(input[i]);
        }
    }

    bool startsWith(string a, string b) {
        if (b.size() > a.size()) return false;
        return std::equal(a.begin(), a.begin() + b.size(), b.begin());
    }

    bool betweenPar(string query, int position) {
        int state = 0;
        for (int i = 0; i < position; ++i) {
            if (query[i] == '(') state++;
            if (query[i] == ')') state--;
        }
        return state != 0;
    }

    void trimString(string &query) {
        int pos = query.find("  ");
        while (pos != string::npos) {
            query.erase(pos, 1);
            pos = query.find("  ");
        }
        while (query[0] == ' ') query.erase(0, 1);
        while (query.length() > 0 and query[query.length() - 1] == ' ')
            query.erase(query.length() - 1, 1);
    }

    void trimStringComplex(string &query) {
        while (query[0] == ' ' or query[0] == '\"') query.erase(0, 1);
        while (query.length() > 0 and (query[query.length() - 1] == ' ' or query[query.length() - 1] == '\"'))
            query.erase(query.length() - 1, 1);
    }

    void formatString(string &query) {
        int pos = query.find_first_of(",;:.!?");
        while (pos != string::npos) {
            if (query[pos - 1] == ' ' and (pos + 1 == query.length() or query[pos + 1] == ' '))
                query.erase(pos - 1, 1);
            pos = query.find_first_of(",;:.!?", pos + 1);
        }
    }

    void removeDelimiter(string &line) {
        int pos = line.find_first_of(",;:.!?");
        while (pos != string::npos) {
            if (pos + 1 == line.length() or line[pos + 1] == ' ')
                line[pos] = ' ';
            pos = line.find_first_of(",;:.!?", pos + 1);
        }
        trimString(line);
    }

    bool malformedExpression(string &query) {
        int statePar, stateWords;
        statePar = stateWords = 0;
        for (int i = 0; i < query.length(); ++i) {
            if (stateWords < 0) {
                return true;
            } else if (query[i] == '{') {
                if (stateWords > 0) {
                    query[i] = ' ';
                    stateWords--;
                }
                stateWords++;
            } else if (query[i] == '}') {
                stateWords--;
            } else if (query[i] == '(') {
                statePar++;
            } else if (query[i] == ')') {
                statePar--;
                if (statePar < 0) {
                    query[i] = ' ';
                    statePar++;
                }
            }
        }
        return stateWords < 0 or statePar > 0;
    }

    void printError() {
        cout << "error" << endl;
    }
}