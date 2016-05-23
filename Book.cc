/**
  @file Book.cc
  @brief Class for the Book definition
*/

#include "Book.hh"
using namespace std;

Book::Book() {
    bookWords = 0;
    dirtyFrequency = true;
    deleted = false;
}

Book::Book(string title, string author) {
    bookTitle = title;
    authorName = author;
    bookWords = 0;
    dirtyFrequency = true;
    deleted = false;
}

Book::~Book() {
    // no-op
}

void Book::readBookContent() {
    string input, line;
    while (getline(cin, input) and input != "****") {
        istringstream iss(input);
        string word;
        while (iss >> word) {
            line += ' ' + word;
            if (word.find_last_of(".?!") == word.length() - 1) {
                utils::trimString(line);
                bookContent.push_back(line);
                line.clear();
                word.erase(word.length() - 1, 1);
            } else if (word.find_last_of(",;:.?!") == word.length() - 1) {
                word.erase(word.length() - 1, 1);
            }
            if (!word.empty()) {
                if (line.empty()) lineDictionary[word].push_back(bookContent.size());
                else lineDictionary[word].push_back(bookContent.size() + 1);
                wordFrequencyMap[word] += 1;
                bookWords += 1;
            }
        }
    }
}

string Book::getTitle() const {
    return bookTitle;
}

string Book::getAuthor() const {
    return authorName;
}

int Book::getLineCount() const {
    return bookContent.size();
}

int Book::getWordCount() const {
    return bookWords;
}

void Book::replaceWords(string oldWord, string newWord) {
    // TODO: newWord empty?
    if (oldWord == newWord or oldWord.empty()) return;
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
                                   lineDictionary[oldWord].begin(),
                                   lineDictionary[oldWord].end());
    lineDictionary.erase(oldWord);
    // Edit the frequency Map
    if (newWord.empty()) bookWords -= wordFrequencyMap[oldWord];
    else wordFrequencyMap[newWord] += wordFrequencyMap[oldWord];
    wordFrequencyMap.erase(oldWord);
    dirtyFrequency = true;
}

bool Book::findWord(string word) {
    return wordFrequencyMap.find(word) != wordFrequencyMap.end();
}

bool Book::isFrequencyDirty() {
    return dirtyFrequency;
}

bool Book::isDeleted() {
    return deleted;
}

void Book::generateFrequencyTable() {
    // Reset dirty boolean
    dirtyFrequency = false;
    // Clear the list
    wordFrequencyList.clear();
    // Copy from the Map to the List
    for (map<string, int>::iterator it = wordFrequencyMap.begin();
         it != wordFrequencyMap.end(); ++it) {
        wordFrequencyList.push_back(make_pair(it->first, it->second));
    }
    // Sort the list with our custom comparator struct
    wordFrequencyList.sort(utils::frequencyComparator());
}

set<string, utils::stringNaturalComparator> Book::getBookQuotes() {
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

void Book::deleteBook() {
    deleted = true;
}

void Book::findExpression(string query, set<int>& pos) {
    // Trim spaces of the query
    utils::trimString(query);
    if (query.find_first_of('{') == string::npos and query.find_first_of('}') == string::npos) {
        // Base case: Malformed expression (not found any word to find)
    } else if (query.find_last_of('{') == 0 and query.find_first_of('}') == query.length() - 1
            and query.find_first_of('&') == string::npos and query.find_first_of('|') == string::npos) {
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
        // Find the first & operator outside parentheses
        int posAnd = query.find_first_of('&');
        while (posAnd != string::npos and utils::betweenPar(query, posAnd)) {
            posAnd = query.find_first_of('&', posAnd + 1);
        }
        // If found call the recursivity on both sides of the expression
        if (posAnd != string::npos) {
            // Recursive case: Call recursion of both expressions and intersect them
            set<int> set1, set2;
            findExpression(query.substr(0, posAnd), set1);
            findExpression(query.substr(posAnd + 1), set2);
            set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(), inserter(pos, pos.begin()));
        } else {
            // If no outer & operators, find the first | operator outside parentheses
            int posOr = query.find_first_of('|');
            while (posOr != string::npos and utils::betweenPar(query, posOr)) {
                posOr = query.find_first_of('|', posOr + 1);
            }
            if (posOr != string::npos) {
                // Recursive case: Call recursion of both expressions and union them
                set<int> set1, set2;
                findExpression(query.substr(0, posOr), set1);
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
    for (int i = 1; i <= bookContent.size(); ++i) {
        cout << i << " " << bookContent[i - 1] << endl;
    }
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
        utils::printError();
        return;
    }
    for (int i = start; i <= end; ++i) {
        cout << i << " " << bookContent[i - 1] << endl;
    }
}

void Book::printFrequencyTable() {
    if (dirtyFrequency) generateFrequencyTable();
    list<pair<string, int> >::const_iterator it = wordFrequencyList.begin();
    while (it != wordFrequencyList.end()) {
        if (it->second > 0 and !it->first.empty())
            cout << it->first << " " << it->second << endl;
        it++;
    }
}
