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
    // Add new Book with ID: authorName-title
    Book book(title, authorName);
    book.readBookContent();
    bookCollection[authorName + "-" + title] = book;
    // Add or update Author with ID: authorName
    map<string, Author>::iterator it = authorCollection.find(authorName);
    if (it == authorCollection.end()) {
        Author author(authorName);
        author.incrementBookCount(1);
        author.incrementLineCount(book.getBookLines());
        author.incrementWordCount(book.getBookWords());
        authorCollection[authorName] = author;
    } else {
        (it->second).incrementBookCount(1);
        (it->second).incrementLineCount(book.getBookLines());
        (it->second).incrementWordCount(book.getBookWords());
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
    // Build FrequencyTable Vector upon select
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

void Library::insertQuote(int start, int end) {
    // Assign new Reference (check what was the last one)
    string reference, aux;
    istringstream iss(currentBook->second.getAuthorName());
    while (iss >> aux) reference += aux[0];
    // Check if there's an existing Quote with these lines of the same book
    map<string, Quote>::iterator it = quoteCollection.begin();
    int pos = 1;
    while (it != quoteCollection.end() and it->second.getReference() < reference) {
        if (it->second.getReference().substr(0, reference.length()) == reference) {
            if (it->second.getBookTitle() == currentBook->second.getBookTitle()
                    and it->second.getStartLine() == start
                    and it->second.getEndLine() == end) {
                cout << "error" << endl;
                return;
            } else pos += 1;
        }
    }
    // Set position on the reference
    reference += pos;
    // Get lines from book vector<string> (1-size)
    vector<string> lines(end - start + 1);
    currentBook->second.getLines(lines, start, end);
    // Store them into new Quote
    Quote quote(reference, currentBook->second.getAuthorName(),
                currentBook->second.getBookTitle());
    quote.setContent(lines);
    quote.setQuoteLines(start, end);
    // Store the Quote in quoteCollection
    quoteCollection[reference] = quote;
    // Add ID to Book
    currentBook->second.addQuote(reference);
    // Add ID to Author
    authorCollection[currentBook->second.getAuthorName()].addQuote(reference);
}

void Library::deleteQuote(string reference) {
    map<string, Quote>::iterator it = quoteCollection.find(reference);
    if (it == quoteCollection.end()) {
        cout << "error" << endl;
    } else {
        // Remove Quote from Book
        currentBook->second.deleteQuote(reference);
        // Remove Quote from Author
        authorCollection[currentBook->second.getAuthorName()].deleteQuote(reference);
        // Delete the Quote from the collection
        quoteCollection.erase(it);
    }
}

Book Library::getBook() {
    return currentBook->second;
}

Quote Library::getQuote(string id) {
    return quoteCollection[id];
}

void Library::printAuthors() {
    map<string, Author>::iterator it = authorCollection.begin();
    while (it != authorCollection.end()) {
        (it->second).printInformation();
    }
}

void Library::printBooks() {
    map<string, Book>::iterator it = bookCollection.begin();
    while (it != bookCollection.end()) {
        (it->second).printInformation();
    }
}

void Library::printQuotes() {
    // TODO
}

void Library::printBooksByAuthor(string author) {
    authorCollection[author].printBooks();
}

void Library::printQuotesByAuthor(string author) {
    authorCollection[author].printQuotes();
}

void Library::printCurrentInformation() {
    cout << currentBook->second.getAuthorName();
    cout << currentBook->second.getBookTitle();
    cout << currentBook->second.getBookLines();
    cout << currentBook->second.getBookWords() << endl;
    cout << "Cites Associades:" << endl;
    set<string> quotes = currentBook->second.getBookQuotes();
    set<string>::iterator it = quotes.begin();
    while (it != quotes.end()) {
        quoteCollection[*it].printInformation();
    }
}