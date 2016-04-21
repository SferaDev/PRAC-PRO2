/**
  @file Book.cc
  @brief Class for the Book definition
*/

#include "Book.hh"
#include <sstream>
using namespace std;

Book::Book() {
    // TODO
}

Book::Book(string title, string author) {
    bookTitle = title;
    authorName = author;
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
            if (word.find_last_of(",;:") == word.length() - 1)
                word.erase(word.length() - 1, 1);
            if (word.find_last_of(".?!") == word.length() - 1) {
                bookContent.push_back(content);
                content.clear();
                word.erase(word.length() - 1, 1);
            }
            bookDictionary[word.length()][word] += 1;
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
    return bookLines;
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

void Book::printAllLines() {
    printSelectLines(1, bookContent.size());
}

void Book::printLines(string query) {
    // TODO
}

void Book::printSelectLines(int start, int end) {
    for ( int i = x; i <= y; ++i) {
        cout <<  bookContent[i - 1] << endl;
    }
    // TODO
}

void Book::printFrequencyTable() {
    // TODO
}