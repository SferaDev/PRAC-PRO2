/**
  @file Library.cc
  @brief Class for the Library methods
*/

#include "Library.hh"
using namespace std;

Library::Library() {
    currentBook = bookCollection.begin();
}

Library::~Library() {
    // no-op
}

void Library::insertBook(const Book& book) {
    bookCollection.insert(pair<string, Book>(book.getBookName(), book));
}

void Library::selectBook(string query) {
    // TODO
}

void Library::deleteBook() {
    bookCollection.erase(currentBook);
}

void Library::deleteQuote(string id) {
    quoteCollection.erase(id);
}

Book Library::getBook() {
    return *currentBook;
}

void Library::printAuthors() {
    // TODO
}

void Library::printBooks() {
    // TODO
}

void Library::printQuotes() {
    // TODO
}

void Library::printBooksByAuthor(string author) {
    // TODO
}

void Library::printQuotesByAuthor(string author) {
    // TODO
}