/**
  @file Book.cc
  @brief Class for the Book definition
*/

#include "Book.hh"
#include <algorithm>
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
            }
            wordDictionary[word.length()].insert(word);
            wordFrequencyMap[word] += 1;
        }
    }
}

string Book::getBookTitle() const {
    return bookTitle;
}

string Book::getAuthorName() {
    return authorName;
}

int Book::getBookLines() {
    return bookContent.size();
}

int Book::getBookWords() {
    return bookWords;
}

void Book::replaceWords(string oldWord, string newWord) {
    // TODO: Edit the contents of the book
    /*for (int i = 0; i < bookContent.size(); ++i) {
        bookContent[i].replace(oldWord, newWord);
    }*/
    // TODO: Edit the dictionary
}

bool Book::findWord(string word) {
    return wordDictionary[word.length()].find(word) != wordDictionary[word.length()].end();
}

void Book::generateFrequencyTable() {
    // FIXME: Efficiency?
    for (map<string, int>::iterator it = wordFrequencyMap.begin();
         it != wordFrequencyMap.end(); ++it) {
        wordFrequencyVector.push_back(make_pair(it->first, it->second));
    }
    sort(wordFrequencyVector.begin(), wordFrequencyVector.end(), frequencyComparator());
}

void Book::printAllLines() {
    printSelectLines(1, bookContent.size());
}

void Book::printLines(string query) {
    // TODO
}

void Book::printSelectLines(int start, int end) {
    for (int i = start; i <= end; ++i) {
        cout <<  i << " " << bookContent[i - 1] << endl;
    }
}

void Book::printFrequencyTable() {
    for (int i = 0; i < wordFrequencyVector.size(); ++i) {
        cout << wordFrequencyVector[i].first << " " << wordFrequencyVector[i].second << endl;
    }
}