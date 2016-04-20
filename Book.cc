/**
  @file Book.cc
  @brief Class for the Book definition
*/

#include "Book.hh"
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
    string input;
    int pos = 0;
    getline(cin, input);
    while (input != "") {
        int pos = input.find_first_of(".?!");
        cout << input.substr(0, pos) << endl;
        bookContent.push_back(input.substr(0, pos));
        input = input.substr(pos);
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