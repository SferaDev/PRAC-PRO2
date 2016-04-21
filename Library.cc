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

void Library::readBook(string title, string author) {
    Book book(title, author);
    book.readBookContent();
    bookCollection[title] = book;
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
    return currentBook->second;
}

Quote Library::getQuote(string id) {
    return quoteCollection[id];
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