/**
  @file Book.cc
  @brief Class for the Book definition
*/

#include "Book.hh"
#include <algorithm>
#include <queue>
#include <sstream>
using namespace std;

Book::Book() {
    bookWords = 0;
    dirtyFrequency = true;
}

Book::Book(string title, string author) {
    bookTitle = title;
    authorName = author;
    bookWords = 0;
    dirtyFrequency = true;
}

Book::~Book() {
    // no-op
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
    while (query[0] == ' ') query.erase(0, 1);
    while (query[query.length() - 1] == ' ') query.erase(query.length() - 1, 1);
}

struct frequencyComparator {
    bool operator() (const pair<string, int>& a, const pair<string, int>& b) {
        // Special case: Same frequency
        if (a.second == b.second) {
            // Special case: Same length
            if (a.first.length() == b.first.length()) {
                return a.first < b.first;
            }
            // Base case: Order by length in asc order
            return a.first.length() < b.first.length();
        }
        // Base case: Order by frequency in desc order
        return a.second > b.second;
    }
};

void Book::readBookContent() {
    string input, content, word;
    bool error = false;
    while (getline(cin, input) && input != "****") {
        istringstream iss(input);
        while (iss >> word) {
            if (!content.empty()) content += " ";
            content += word;
            bookWords += 1;
            if (word.find_last_of(",;:") == word.length() - 1) {
                if (word.length() > 0) {
                    word.erase(word.length() - 1, 1);
                    if (word.find_last_of(",;:.?!") == word.length() - 1) error = true;
                }
            } else if (word.find_last_of(".?!") == word.length() - 1) {
                bookContent.push_back(content);
                content.clear();
                if (word.length() > 0) {
                    word.erase(word.length() - 1, 1);
                    if (word.find_last_of(",;:.?!") == word.length() - 1) error = true;
                }
                lineDictionary[word].push_back(bookContent.size());
            } else {
                lineDictionary[word].push_back(bookContent.size() + 1);
            }
            wordFrequencyMap[word] += 1;
        }
    }
    if (input == "****" and !content.empty()) {
        bookContent.push_back(content);
        lineDictionary[word].push_back(bookContent.size());
    }
    if (error) bookContent.clear();
}

string Book::getTitle() const {
    return bookTitle;
}

string Book::getAuthor() {
    return authorName;
}

int Book::getLineCount() {
    return bookContent.size();
}

int Book::getWordCount() {
    return bookWords;
}

void Book::replaceWords(string oldWord, string newWord) {
    // Edit the contents of the book
    map<string, list<int> >::const_iterator it1 = lineDictionary.find(oldWord);
    if (it1 != lineDictionary.end()) {
        list<int>::const_iterator it2 = it1->second.begin();
        while (it2 != it1->second.end()) {
            istringstream iss(bookContent[*it2 - 1]);
            string word, line;
            while (iss >> word) {
                if (word == oldWord) line += newWord;
                else line += word;
                line += ' ';
            }
            trimString(line);
            bookContent[*it2 - 1] = line;
            it2++;
        }
    }
    // Edit the line dictionary
    lineDictionary[newWord] = lineDictionary[oldWord];
    lineDictionary.erase(oldWord);
    // Edit the frequency Map
    wordFrequencyMap[newWord] = wordFrequencyMap[oldWord];
    wordFrequencyMap.erase(oldWord);
    dirtyFrequency = true;
}

bool Book::findWord(string word) {
    return wordFrequencyMap.find(word) != wordFrequencyMap.end();
}

bool Book::isFrequencyDirty() {
    return dirtyFrequency;
}

void Book::generateFrequencyTable() {
    // Check if list was previously generated
    dirtyFrequency = false;
    wordFrequencyList.clear();
    for (map<string, int>::iterator it = wordFrequencyMap.begin();
         it != wordFrequencyMap.end(); ++it) {
        wordFrequencyList.push_back(make_pair(it->first, it->second));
    }
    wordFrequencyList.sort(frequencyComparator());
}

set<string> Book::getBookQuotes() {
    return bookQuotes;
}

vector<string> Book::getLines(int start, int end) {
    vector<string> vector(end - start + 1);
    for (int i = start; i <= end; ++i) {
        vector[i - start] = bookContent[i - 1];
    }
    return vector;
}

void Book::addQuote(string reference) {
    bookQuotes.insert(reference);
}

void Book::deleteQuote(string reference) {
    bookQuotes.erase(reference);
}

void Book::printInformation() {
    cout << authorName << " \"" <<  bookTitle << "\"" << endl;
}

void Book::printAllLines() {
    printSelectLines(1, bookContent.size());
}

void Book::printLines(string query) {
    set<int> lines;
    findExpression(query, lines);
    set<int>::const_iterator it = lines.begin();
    while (it != lines.end()) {
        printSelectLines(*it, *it);
        it++;
    }
}

void Book::findExpression(string query, set<int>& pos) {
    trimString(query);
    if (query.find_first_of('{') == string::npos and query.find_first_of('}') == string::npos) {
        // Base case: Malformed expression
    } else if (query.find_last_of('{') == 0 and query.find_first_of('}') == query.length() - 1) {
        query = query.substr(1, query.length() - 2);
        if (query.find_first_of(" ") == string::npos) {
            // Base case: One word, return lines where found
            map<string, list<int> >::const_iterator it1 = lineDictionary.find(query);
            if (it1 != lineDictionary.end()) {
                list<int>::const_iterator it2 = it1->second.begin();
                while (it2 != it1->second.end()) {
                    pos.insert(*it2);
                    it2++;
                }
            }
        } else {
            // Recursive case: More than one word, replace spaces with &
            istringstream iss(query);
            query.clear();
            string word;
            iss >> word;
            query += "{" + word + "}";
            while (iss >> word) {
                query += " & {" + word + "}";
            }
            findExpression(query, pos);
        }
    } else {
        int posAnd = query.find_first_of('&');
        while (posAnd != string::npos and betweenPar(query, posAnd)) {
            posAnd = query.find_first_of('&', posAnd + 1);
        }
        if (posAnd != string::npos) {
            // Recursive case: Call recursion of both expressions and intersect them
            set<int> set1, set2;
            findExpression(query.substr(0, posAnd - 1), set1);
            findExpression(query.substr(posAnd + 1), set2);
            set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(), inserter(pos, pos.begin()));
        } else {
            int posOr = query.find_first_of('|');
            while (posOr != string::npos and betweenPar(query, posOr)) {
                posOr = query.find_first_of('|', posOr + 1);
            }
            if (posOr != string::npos) {
                // Recursive case: Call recursion of both expressions and union them
                set<int> set1, set2;
                findExpression(query.substr(0, posOr - 1), set1);
                findExpression(query.substr(posOr + 1), set2);
                set_union(set1.begin(), set1.end(), set2.begin(), set2.end(), inserter(pos, pos.begin()));
            } else if (!betweenPar(query, query.length())) {
                // Recursive case: Call recursion of inner parentheses expression
                findExpression(query.substr(1, query.length() - 2), pos);
            } // Base case: else: Malformed parentheses/operators
        }
    }
}

void Book::printWordsConsecutiveLines(string query) {
    // FIXME: Check if words are in the dictionary (slow?)
    istringstream issQuery(query);
    string wordQuery;
    while (issQuery >> wordQuery) {
        if (!findWord(wordQuery)) {
            // TODO: cout << "error" << endl;
            return;
        }
    }
    // Loop all the lines
    for (int i = 0; i < bookContent.size(); ++i) {
        if (bookContent[i].find(query) != bookContent[i].npos) {
            printSelectLines(i + 1, i + 1);
        }
    }
}

void Book::printSelectLines(int start, int end) {
    if ((end < start) or (start < 1) or (end > bookContent.size())) {
        cout << "error" << endl;
        return;
    }
    for (int i = start; i <= end; ++i) {
        cout <<  i << " " << bookContent[i - 1] << " " <<  endl;
    }
}

void Book::printFrequencyTable() {
    if (dirtyFrequency) generateFrequencyTable();
    list<pair<string, int> >::const_iterator it = wordFrequencyList.begin();
    while (it != wordFrequencyList.end()) {
        if (it->second > 0) cout << it->first << " " << it->second << endl;
        it++;
    }
}
