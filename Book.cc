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
    while (getline(cin, input) && input != "****") {
        string word;
        istringstream iss(input);
        while (iss >> word) {
            if (!content.empty()) content += " ";
            content += word;
            bookWords += 1;
            if (word.find_last_of(",;:") == word.length() - 1)
                word.erase(word.length() - 1, 1);
            if (word.find_last_of(".?!") == word.length() - 1) {
                bookContent.push_back(content);
                content.clear();
                word.erase(word.length() - 1, 1);
                lineDictionary[word].push_back(bookContent.size());
            } else {
                lineDictionary[word].push_back(bookContent.size() + 1);
            }
            wordDictionary[word.length()].insert(word);
            wordFrequencyMap[word] += 1;
        }
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
    wordFrequencyMap.erase(oldWord);
    // FIXME: Update the frequency vector (slow?)
    generateFrequencyTable();
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
    cout << authorName << " \"" <<  bookTitle << "\" " << endl;
}

void Book::printAllLines() {
    printSelectLines(1, bookContent.size());
}

void Book::printLines(string query) {
    // TODO: JORDI
    // TODO: Call the immersive recursive: bool found with items query and int[] with the lines where found
}

/*bool findExpression(string query, set<int>& pos) {
    // IF () are found then call recursively with the substr and replace with 1 or 0.
    int pPos = query.find_first_of('(');
    if (pPos != string::npos) {
        int ePos = query.find_last_of(')');
        // ePos - pPos < 0 or ePos == npos -> error
        query.replace(pPos, ePos - pPos, " " + findExpression(query.substr(pPos + 1, ePos - pPos)) + " ");
    }
    // Split string on & and | and add to queue reducing query
    queue<string> queryQueue;
    while (!query.empty()) {
        //
    }
    // Evaluate expressions in order queue

}*/

void Book::printWordsConsecutivesLines(string query){
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
        cout <<  i << " " << bookContent[i - 1] << endl;
    }
}

void Book::printFrequencyTable() {
    for (int i = 0; i < wordFrequencyVector.size(); ++i) {
        cout << wordFrequencyVector[i].first << " " << wordFrequencyVector[i].second << endl;
    }
}