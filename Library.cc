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
    // TODO
}

void Library::selectBook(string query) {
    // TODO
}

void Library::deleteBook() {
    // TODO
}

void Library::deleteQuote(string id) {
    // TODO
}

Book Library::getBook() {
    // TODO
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