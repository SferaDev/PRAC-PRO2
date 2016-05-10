/**
  @file Book.cc
  @brief Class for the Book definition
*/

#include "Book.hh"
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
            if (wordFrequency.find(word) != wordFrequency.end()) {
                wordFrequencyOrdered.erase(make_pair(word, wordFrequency[word]));
            }
            wordFrequency[word] += 1;
            wordFrequencyOrdered.insert(make_pair(word, wordFrequency[word]));
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
    list<string>::iterator it = bookContent.begin();
    while (it != bookContent.end()) {
        int pos = (*it).find(oldWord);
        while (pos != string::npos) {
            (*it).replace(pos, oldWord.length(), newWord);
            pos = (*it).find(oldWord);
        }
        it++;
    }
    // Edit the word dictionary
    wordDictionary[oldWord.length()].erase(oldWord);
    wordDictionary[newWord.length()].insert(newWord);
    // Edit the line dictionary
    lineDictionary[newWord] = lineDictionary[oldWord];
    lineDictionary[oldWord].clear();
    // Edit the frequency
    wordFrequency[newWord] = wordFrequency[oldWord];
    wordFrequencyOrdered.erase(make_pair(oldWord, wordFrequency[oldWord]));
    wordFrequencyOrdered.insert(make_pair(newWord, wordFrequency[newWord]));
    wordFrequency.erase(oldWord);
}

bool Book::findWord(string word) {
    return wordDictionary[word.length()].find(word) != wordDictionary[word.length()].end();
}

set<string> Book::getBookQuotes() {
    return bookQuotes;
}

vector<string> Book::getLines(int start, int end) {
    vector<string> vector(end - start + 1);
    list<string>::const_iterator it = bookContent.begin();
    advance(it, start - 1);
    for (int i = start; i <= end; ++i) {
        vector[i - start] = *it;
        it++;
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
    if (query.find_first_of('{') == string::npos and query.find_first_of('}') == string::npos) {
        // noop: Error, malformed
    } else if (query.find_last_of('{') == 0 and query.find_first_of('}') == query.length() - 1) {
        // Base case: Return true/false with positions where found
        query = query.substr(1, query.length() - 2);
        if (query.find_first_of(" ") == string::npos) {
            map<string, list<int> >::const_iterator it1 = lineDictionary.find(query);
            if (it1 != lineDictionary.end()) {
                list<int>::const_iterator it2 = it1->second.begin();
                while (it2 != it1->second.end()) {
                    pos.insert(*it2);
                    it2++;
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
            }
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
    list<string>::iterator it = bookContent.begin();
    while (it != bookContent.end()) {
        if ((*it).find(query) != string::npos) {
            int line = distance(bookContent.begin(), it) + 1;
            printSelectLines(line, line);
        }
        it++;
    }
}

void Book::printSelectLines(int start, int end) {
    if ((end < start) or (start < 1) or (end > bookContent.size())) {
        cout << "error" << endl;
        return;
    }
    list<string>::iterator it = bookContent.begin();
    advance(it, start - 1);
    list<string>::iterator endIt = bookContent.begin();
    advance(endIt, end);
    while (it != endIt) {
        cout <<  distance(bookContent.begin(), it) + 1 << " " << *it << " " <<  endl;
        it++;
    }
}

void Book::printFrequencyTable() {
    set<pair<string, int> >::const_iterator it = wordFrequencyOrdered.begin();
    while (it != wordFrequencyOrdered.end()) {
        cout << it->first << " " << it->second << endl;
        it++;
    }
}
