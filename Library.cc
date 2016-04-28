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

void Library::readBook(string title, string authorName) {
    // Add new Book with ID: title-authorName
    Book book(title, authorName);
    book.readBookContent();
    bookCollection[title + "-" + authorName] = book;
    // Add or update Author with ID: authorName
    authorCollection.find(authorName);
    if (it == authorCollection.end()) {
        Author author(authorName);
        author.incrementBookCount(1);
        author.incrementLineCount(book.getBookLines());
        author.incrementWordCount((book.getBookWords());
        authorCollection[authorName] = author;
    } else {
        *it.incrementBookCount(1);
        *it.incrementLineCount(book.getBookLines());
        *it.incrementWordCount((book.getBookWords());
    }
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

void Library::replaceWordsOnBook(string input) {
    if (isBookSelected()) {
        int start = input.find_first_of("\"") + 1;
        int end = input.find_first_of("\"", start);
        string oldWord = input.substr(start, end - start);
        start = input.find_first_of("\"", end + 1) + 1;
        end = input.find_first_of("\"", start);
        string newWord = input.substr(start, end - start);
        currentBook->second.replaceWords(oldWord, newWord);
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
    authorCollection[author].printBooks();
}

void Library::printQuotesByAuthor(string author) {
    // TODO
    authorCollection[author].printQuotes();
}