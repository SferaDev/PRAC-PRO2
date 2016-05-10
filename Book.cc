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
}

Book::Book(string title, string author) {
    bookTitle = title;
    authorName = author;
    bookWords = 0;
}

Book::~Book() {
    // no-op
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
    string input, content;
    string word;
    while (getline(cin, input) && input != "****") {
        istringstream iss(input);
        while (iss >> word) {
            if (!content.empty()) content += " ";
            content += word;
            bookWords += 1;
            if (word.find_last_of(",;:") == word.length() - 1)
                if (word.length() > 0) word.erase(word.length() - 1, 1);
            if (word.find_last_of(".?!") == word.length() - 1) {
                bookContent.push_back(content);
                content.clear();
                if (word.length() > 0) word.erase(word.length() - 1, 1);
                lineDictionary[word].push_back(bookContent.size());
            } else {
                lineDictionary[word].push_back(bookContent.size() + 1);
            }
            wordDictionary[word.length()].insert(word);
            wordFrequencyMap[word] += 1;
        }
    }
    if (input == "****" and !content.empty()) {
        bookContent.push_back(content);
        lineDictionary[word].push_back(bookContent.size());
    }
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

// FIXME: Jutge fails on private3
void Book::replaceWords(string oldWord, string newWord) {
    // Edit the contents of the book
    for (int i = 0; i < bookContent.size(); ++i) {
        int pos = bookContent[i].find(oldWord);
        while (pos != bookContent[i].npos) {
            bookContent[i].replace(pos, oldWord.length(), newWord);
            pos = bookContent[i].find(oldWord);
        }
    }
    // Edit the word dictionary
    wordDictionary[oldWord.length()].erase(oldWord);
    wordDictionary[newWord.length()].insert(newWord);
    // Edit the line dictionary
    lineDictionary[newWord] = lineDictionary[oldWord];
    lineDictionary[oldWord].clear();
    // Edit the frequency Map
    wordFrequencyMap[newWord] = wordFrequencyMap[oldWord];
    int freq = wordFrequencyMap[oldWord];
    wordFrequencyMap.erase(oldWord);
    // TODO: Don't use two conditions to check the continuity of the for (use while instead)
    bool found = false;
    for (int i = 0; i < wordFrequencyVector.size() and !found; ++i) {
        if (wordFrequencyVector[i].first == oldWord) {
            wordFrequencyVector.erase(wordFrequencyVector.begin() + i);
        } else if (wordFrequencyVector[i].first > newWord) {
            found = true;
            wordFrequencyVector.insert(wordFrequencyVector.begin() + i, make_pair(newWord, freq));
        }
    }
}

bool Book::findWord(string word) {
    return wordDictionary[word.length()].find(word) != wordDictionary[word.length()].end();
}

void Book::generateFrequencyTable() {
    // Check if vector was previously generated
    if (wordFrequencyVector.size() > 0) wordFrequencyVector.clear();
    for (map<string, int>::iterator it = wordFrequencyMap.begin();
         it != wordFrequencyMap.end(); ++it) {
        wordFrequencyVector.push_back(make_pair(it->first, it->second));
    }
    sort(wordFrequencyVector.begin(), wordFrequencyVector.end(), frequencyComparator());
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

void Book::findExpression(string query, set<int>& pos) {
    trimString(query);
    if (query.find_last_of('{') == 0 and query.find_first_of('}') == query.length() - 1) {
        // Base case: Return true/false with positions where found
        query = query.substr(1, query.length() - 2);
        int posSpace = query.find_first_of(" ");
        if (posSpace == string::npos) {
            map<string, vector<int> >::const_iterator it = lineDictionary.find(query);
            if (it != lineDictionary.end()) {
                for (int i = 0; i < it->second.size(); ++i) {
                    pos.insert(it->second[i]);
                }
            }
        } else {
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
                set<int> set1, set2;
                findExpression(query.substr(0, posOr - 1), set1);
                findExpression(query.substr(posOr + 1), set2);
                set_union(set1.begin(), set1.end(), set2.begin(), set2.end(), inserter(pos, pos.begin()));
            } else if (!betweenPar(query, query.length())) {
                findExpression(query.substr(1, query.length() - 2), pos);
            } //TODO: else error
        }
    }
}

void Book::printWordsConsecutiveLines(string query) {
    // FIXME: Check if words are in the dictionary (slow?)
    istringstream issQuery(query);
    string wordQuery;
    while (issQuery >> wordQuery) {
        if (!findWord(wordQuery)) {
            cout << "error" << endl;
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
    for (int i = 0; i < wordFrequencyVector.size(); ++i) {
        cout << wordFrequencyVector[i].first << " " << wordFrequencyVector[i].second << endl;
    }
}
