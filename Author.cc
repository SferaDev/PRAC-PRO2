/**
  @file Author.cc
  @brief Class for the Author definition
*/

#include "Author.hh"
using namespace std;

Author::Author() {
    totalBooks = 0;
    totalLines = 0;
    totalWords = 0;
}

Author::Author(string name) {
    authorName = name;
    totalBooks = 0;
    totalLines = 0;
    totalWords = 0;
}

Author::~Author() {
    // no-op
}

void Author::incrementBookCount(int value) {
    totalBooks += value;
}

void Author::incrementLineCount(int value) {
    totalLines += value;
}
    
void Author::incrementWordCount(int value) {
    totalWords += value;
}

int Author::getBookCount() const {
    return totalBooks;
}


int Author::getLineCount() const {
    return totalLines;
}


int Author::getWordCount() const {
    return totalWords;
}
    
void Author::addBook(string title) {
    authorBooks.insert(title);
}
    
void Author::addQuote(string reference) {
    authorQuotes.insert(reference);
}
    
void Author::deleteBook(string title) {
    authorBooks.erase(title);
}
    
void Author::deleteQuote(string reference) {
    authorQuotes.erase(reference);
}

set<string> Author::getAuthorQuotes() {
    return authorQuotes;
}

bool Author::isEmpty() {
    return authorBooks.empty();
}

void Author::printInformation() {
    cout << authorName << " " << totalBooks << " " << totalLines << " " << totalWords;
    cout << endl;
}

void Author::printBooks() {
    set<string>::const_iterator it = authorBooks.begin();
    while (it != authorBooks.end()) {
        cout << "\"" << *it << "\"" << endl;
        ++it;
    }
}