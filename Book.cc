/**
  @file Book.cc
  @brief Class for the Book definition
*/

#include "Book.hh"
using namespace std;

Book::Book() {
    // TODO
}

Book::~Book() {
    // no-op
}

string Book::getBookName() {
    return bookName;
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
    // Edit the contents of the book
    for (int i = 0; i < bookContent.size(); ++i) {
        bookContent[i].replace(oldWord, newWord);
    }
    // TODO: Edit the dictionary
}

void Book::printAllLines() {
    // TODO
}

void Book::printLines(string query) {
    // TODO
}

void Book::printSelectLines(int start, int end) {
    // TODO
}

void Book::printFrequencyTable() {
    // TODO
}