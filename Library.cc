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

bool Library::isBookSelected() {
    return currentBook != bookCollection.end();
}

void Library::selectBook(string query) {
    // Erase currentBook iterator (end position is erased)
    currentBook = bookCollection.end();
    map<string, Book>::iterator it = bookCollection.begin();
    bool error = false;
    // Loop through all books while there're no errors
    while (it != bookCollection.end() and !error) {
        istringstream iss(query);
        string word;
        bool bContinue = true;
        // Loop through all words (each word must be on the text)
        while (iss >> word and bContinue) {
            // Check if author/title contains or content contains
            bContinue = (it->first.find(word, 0) != word.npos) or
                    (it->second.findWord(word));
        }
        if (bContinue) {
            if (!isBookSelected()) currentBook = it;
            else {
                cout << "error" << endl;
                error = true;
            }
        }
        it++;
    }
    // TODO: FIXME: Build FrequencyTable Vector upon select
    if (isBookSelected()) currentBook->second.generateFrequencyTable();
}

void Library::deleteBook() {
    if (isBookSelected()) {
        bookCollection.erase(currentBook);
        currentBook = bookCollection.end();
    } else cout << "error" << endl;
}

void Library::deleteQuote(string id) {
    if (!quoteCollection.erase(id)) {
        cout << "error" << endl;
    }
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