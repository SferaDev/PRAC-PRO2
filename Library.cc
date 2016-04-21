/**
  @file Library.cc
  @brief Class for the Library methods
*/

#include "Library.hh"
#include <sstream>
using namespace std;

Library::Library() {
    currentBook = bookCollection.end();
}

Library::~Library() {
    // no-op
}

void Library::readBook(string title, string author) {
    Book book(title, author);
    book.readBookContent();
    bookCollection[title + "-" + author] = book;
}

void Library::selectBook(string query) {
    currentBook = bookCollection.end();
    map<string, Book>::iterator it = bookCollection.begin();
    bool error = false;
    while (it != bookCollection.end() and !error) {
        istringstream iss(query);
        string word;
        bool bContinue = true;
        while (iss >> word and bContinue) {
            bContinue = (it->first.find(word, 0) != string::npos) or
                    (it->second.findWord(word));
        }
        if (bContinue) {
            if (currentBook == bookCollection.end()) currentBook = it;
            else {
                cout << "error" << endl;
                error = true;
            }
        } else cout << "error" << endl;
        it++;
    }
    // TODO: FIXME: Build FrequencyTable Vector upon select
    if (!error) currentBook->second.generateFrequencyTable();
}

void Library::deleteBook() {
    if (currentBook != bookCollection.end()) {
        bookCollection.erase(currentBook);
    } else cout << "error" << endl;
}

void Library::deleteQuote(string id) {
    if (!quoteCollection.erase(id)) {
        cout << "error" << endl;
    }
}

Book Library::getBook() {
    // TODO: Throw exception
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