/**
  @file Book.cc
  @brief Class for the Book definition
*/

#include "Book.hh"
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
    while (getline(cin, input) and input != "****") {
        content += ' ' + input;
        int posDelimiter = content.find_first_of(".?!");
        while (posDelimiter != string::npos) {
            string line = content.substr(0, posDelimiter + 1);
            content = content.substr(posDelimiter + 1);
            utils::trimString(line);
            utils::formatString(line);
            utils::trimString(content);
            // TODO: Empty lines should be added or we shouldn't add the text?
            if (!line.substr(0, line.length() - 1).empty()) bookContent.push_back(line);
            string word;
            istringstream iss(line);
            while (iss >> word) {
                int posSeparator = word.find_first_of(",;:");
                while (posSeparator != string::npos) {
                    string subWord = word.substr(0, posSeparator);
                    lineDictionary[subWord].push_back(bookContent.size());
                    wordFrequencyMap[subWord] += 1;
                    bookWords += 1;
                    word = word.substr(posSeparator + 1);
                    posSeparator = word.find_first_of(",;:");
                }
                while (word.size() > 0 and word.find_last_of(".?!") == word.length() - 1)
                    word.erase(word.length() - 1, 1);
                if (word.size() > 0) {
                    lineDictionary[word].push_back(bookContent.size());
                    wordFrequencyMap[word] += 1;
                    bookWords += 1;
                }
            }
            posDelimiter = content.find_first_of(".?!");
        }
    }
    if (input == "****" and !content.empty()) {
        // TODO: FIXME: HALP
        // OPTION 0: Do nothing: Ignore them
        // OPTION 1: Do not add the book
        bookContent.clear();
        /* OPTION 2: Add newline with pendingWords
        bookContent.push_back(content);
        string word;
        istringstream iss(content);
        while (iss >> word) {
            while (word.find_last_of(",;:.?!") == word.length() - 1) {
                word.erase(word.length() - 1, 1);
            }
            lineDictionary[word].push_back(bookContent.size());
            wordFrequencyMap[word] += 1;
            bookWords += 1;
        }*/
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

void Book::replaceWords(string oldWord, string newWord) {
    // Edit the contents of the book
    map<string, list<int> >::const_iterator it1 = lineDictionary.find(oldWord);
    if (it1 != lineDictionary.end()) {
        list<int>::const_iterator it2 = it1->second.begin();
        while (it2 != it1->second.end()) {
            istringstream iss(bookContent[*it2 - 1]);
            string word, line;
            while (iss >> word) {
                string auxWord;
                if (word.find_first_of(",;:.?!") == word.length() - 1) {
                    auxWord = word[word.length() - 1];
                    word.erase(word.length() - 1, 1);
                }
                if (word == oldWord) auxWord = newWord + auxWord;
                else auxWord = word + auxWord;
                line += auxWord + ' ';
            }
            utils::trimString(line);
            bookContent[*it2 - 1] = line;
            it2++;
        }
    }
    // Edit the line dictionary
    lineDictionary[newWord].insert(lineDictionary[newWord].end(),
                                   lineDictionary[oldWord].begin(), lineDictionary[oldWord].end());
    lineDictionary.erase(oldWord);
    // Edit the frequency Map
    wordFrequencyMap[newWord] += wordFrequencyMap[oldWord];
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

void Book::findExpression(string query, set<int>& pos) {
    utils::trimString(query);
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
        while (posAnd != string::npos and utils::betweenPar(query, posAnd)) {
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
            while (posOr != string::npos and utils::betweenPar(query, posOr)) {
                posOr = query.find_first_of('|', posOr + 1);
            }
            if (posOr != string::npos) {
                // Recursive case: Call recursion of both expressions and union them
                set<int> set1, set2;
                findExpression(query.substr(0, posOr - 1), set1);
                findExpression(query.substr(posOr + 1), set2);
                set_union(set1.begin(), set1.end(), set2.begin(), set2.end(), inserter(pos, pos.begin()));
            } else if (!utils::betweenPar(query, query.length())) {
                // Recursive case: Call recursion of inner parentheses expression
                findExpression(query.substr(1, query.length() - 2), pos);
            } // Base case: else: Malformed parentheses/operators
        }
    }
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

void Book::printLinesConsecutiveWords(string query) {
    set<int> lines;
    findExpression('{' + query + '}', lines);
    set<int>::const_iterator it = lines.begin();
    while (it != lines.end()) {
        if (bookContent[*it - 1].find(query) != string::npos) {
            printSelectLines(*it, *it);
        }
        it++;
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
