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
    // If same book with same author exists return error!
    map<string, Book>::iterator bookIt = bookCollection.find(authorName + "-" + title);
    if (bookIt == bookCollection.end()) {
        bookCollection[authorName + "-" + title] = book;
    } else {
        cout << "error" << endl;
        return;
    }
    // Add or update Author with ID: authorName
    map<string, Author>::iterator authorIt = authorCollection.find(authorName);
    if (authorIt == authorCollection.end()) {
        Author author(authorName);
        author.incrementBookCount(1);
        author.incrementLineCount(book.getBookLines());
        author.incrementWordCount(book.getBookWords());
        author.addBook(title);
        authorCollection[authorName] = author;
    } else {
        authorIt->second.incrementBookCount(1);
        authorIt->second.incrementLineCount(book.getBookLines());
        authorIt->second.incrementWordCount(book.getBookWords());
        authorIt->second.addBook(title);
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
    else cout << "error" << endl;
}

void Library::deleteBook() {
    if (isBookSelected()) {
        // Delete book on Author
        authorCollection[currentBook->second.getAuthorName()].deleteBook(currentBook->second.getBookTitle());
        // If author has no books delete it too
        if (authorCollection[currentBook->second.getAuthorName()].isEmpty())
            authorCollection.erase(currentBook->second.getAuthorName());
        // Delete the book
        bookCollection.erase(currentBook);
        // Reset the currentBook iterator
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
    // Error conditions if invalid start/end is given
    if ((end < start) or (start < 1) or (end > currentBook->second.getBookLines())) {
        cout << "error" << endl;
        return;
    }
    // Assign new Reference (check what was the last one)
    string reference, aux;
    istringstream iss(currentBook->second.getAuthorName());
    while (iss >> aux) reference += aux[0];
    // Check if there's an existing Quote with these lines of the same book
    map<string, Quote>::iterator it = quoteCollection.begin();
    while (it != quoteCollection.end()) {
        if (it->second.getReference().substr(0, reference.length()) == reference) {
            if (it->second.getBookTitle() == currentBook->second.getBookTitle()
                    and it->second.getStartLine() == start
                    and it->second.getEndLine() == end) {
                cout << "error" << endl;
                return;
            }
        }
        it++;
    }
    // Set position on the reference (FIXME)
    quoteIdentifiers[reference]++;
    stringstream ss;
    ss << quoteIdentifiers[reference];
    reference += ss.str();
    // Store them into new Quote
    Quote quote(reference, currentBook->second.getAuthorName(),
                currentBook->second.getBookTitle());
    quote.setContent(currentBook->second.getLines(start, end));
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
        bookCollection[it->second.getBookTitle()].deleteQuote(reference);
        // Remove Quote from Author
        authorCollection[it->second.getAuthor()].deleteQuote(reference);
        // Delete the Quote from the collection
        quoteCollection.erase(it);
    }
}

Book Library::getBook() {
    return currentBook->second;
}

bool Library::quoteExists(string id) {
    map<string, Quote>::const_iterator it = quoteCollection.find(id);
    return it != quoteCollection.end();
}

Quote Library::getQuote(string id) {
    return quoteCollection[id];
}

void Library::printAuthors() {
    map<string, Author>::iterator it = authorCollection.begin();
    while (it != authorCollection.end()) {
        it->second.printInformation();
        it++;
    }
}

void Library::printBooks() {
    map<string, Book>::iterator it = bookCollection.begin();
    while (it != bookCollection.end()) {
        it->second.printInformation();
        it++;
    }
}

void Library::printQuotes() {
    map<string, Quote>::iterator it = quoteCollection.begin();
    while (it != quoteCollection.end()) {
        it->second.printInformationComplex();
        it++;
    }
}

void Library::printBooksByAuthor(string author) {
    authorCollection[author].printBooks();
}

void Library::printQuotesByAuthor(string author) {
    set<string> quotes = authorCollection[author].getAuthorQuotes();
    set<string>::iterator it = quotes.begin();
    while (it != quotes.end()) {
        quoteCollection[*it].printInformationComplex();
        it++;
    }
}

void Library::printCurrentInformation() {
    cout << currentBook->second.getAuthorName() << " \"";
    cout << currentBook->second.getBookTitle() << "\" ";
    cout << currentBook->second.getBookLines() << " ";
    cout << currentBook->second.getBookWords() << endl;
    cout << "Cites Associades:" << endl;
    set<string> quotes = currentBook->second.getBookQuotes();
    set<string>::iterator it = quotes.begin();
    while (it != quotes.end()) {
        quoteCollection[*it].printInformation(true, false);
        it++;
    }
}

void Library::printCurrentQuotes() {
    set<string> quotes = currentBook->second.getBookQuotes();
    set<string>::iterator it = quotes.begin();
    while (it != quotes.end()) {
        quoteCollection[*it].printInformationComplex();
        it++;
    }
}