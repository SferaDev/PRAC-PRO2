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

bool contains(string input, string query) {
    istringstream iss(input);
    string word;
    while (iss >> word) {
        if (word == query) return true;
    }
    return false;
}

void stringUppercase(string& input) {
    for (int i = 0; i < input.length(); ++i) {
        if (!isupper(input[i])) input[i] = toupper(input[i]);
    }
}

void Library::readBook(string title, string authorName) {
    // Add new Book with ID: authorName:title
    Book book(title, authorName);
    book.readBookContent();
    // Don't add book if title, author or content is null
    if (title == "" or authorName == "" or book.getLineCount() == 0) return;
    // If same book with same author exists return error!
    map<string, Book>::iterator bookIt = bookCollection.find(authorName + ':' + title);
    if (bookIt == bookCollection.end()) {
        bookCollection[authorName + ':' + title] = book;
    } else {
        cout << "error" << endl;
        return;
    }
    // Add or update Author with ID: authorName
    map<string, Author>::iterator authorIt = authorCollection.find(authorName);
    if (authorIt == authorCollection.end()) {
        Author author(authorName);
        author.incrementBookCount(1);
        author.incrementLineCount(book.getLineCount());
        author.incrementWordCount(book.getWordCount());
        author.addBook(title);
        authorCollection[authorName] = author;
    } else {
        authorIt->second.incrementBookCount(1);
        authorIt->second.incrementLineCount(book.getLineCount());
        authorIt->second.incrementWordCount(book.getWordCount());
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
            string bookId = it->first;
            bookId = bookId.replace(bookId.find_first_of(':'), 1, " ");
            bContinue = (contains(bookId, word) or it->second.findWord(word));
        }
        if (bContinue) {
            if (!isBookSelected()) currentBook = it;
            else {
                error = true;
                currentBook = bookCollection.end();
            }
        }
        it++;
    }
    // Build FrequencyTable Vector upon select
    if (isBookSelected()) {
        if (currentBook->second.isFrequencyDirty()) currentBook->second.generateFrequencyTable();
    } else cout << "error" << endl;
}

void Library::deleteBook() {
    if (isBookSelected()) {
        map<string, Author>::iterator authorIt = authorCollection.find(currentBook->second.getAuthor());
        if (authorIt != authorCollection.end()) {
            // Delete book on Author
            authorIt->second.deleteBook(currentBook->second.getTitle());
            // Decrement author stats (lines/words/...)
            authorIt->second.incrementBookCount(-1);
            authorIt->second.incrementLineCount(-(currentBook->second.getLineCount()));
            authorIt->second.incrementWordCount(-(currentBook->second.getWordCount()));
        }
        // Delete the book
        bookCollection.erase(currentBook);
        // Reset the currentBook iterator
        currentBook = bookCollection.end();
    } else cout << "error" << endl;
}

void Library::replaceWordsOnBook(string oldWord, string newWord) {
    if (isBookSelected()) {
        currentBook->second.replaceWords(oldWord, newWord);
    } else cout << "error" << endl;
}

void Library::insertQuote(int start, int end) {
    // Error conditions if invalid start/end is given
    if ((end < start) or (start < 1) or (end > currentBook->second.getLineCount())) {
        cout << "error" << endl;
        return;
    }
    // Assign new Reference (check what was the last one)
    string reference, aux;
    istringstream iss(currentBook->second.getAuthor());
    while (iss >> aux) reference += aux[0];
    // Pass reference to uppercase
    stringUppercase(reference);
    // Check if there's an existing Quote with these lines of the same book
    map<string, Quote>::iterator it = quoteCollection.begin();
    while (it != quoteCollection.end()) {
        if (it->second.getReference().substr(0, reference.length()) == reference) {
            if (it->second.getBookTitle() == currentBook->second.getTitle()
                    and it->second.getStartLine() == start
                    and it->second.getEndLine() == end) {
                cout << "error" << endl;
                return;
            }
        }
        it++;
    }
    quoteIdentifiers[reference]++;
    // FIXME: Using a stringstream for this doesn't look good  at all
    stringstream ss;
    ss << quoteIdentifiers[reference];
    reference += ss.str();
    // Store them into new Quote
    Quote quote(reference, currentBook->second.getAuthor(),
                currentBook->second.getTitle());
    quote.setContent(currentBook->second.getLines(start, end));
    quote.setQuoteLines(start, end);
    // Store the Quote in quoteCollection
    quoteCollection[reference] = quote;
    // Add ID to Book
    currentBook->second.addQuote(reference);
    // Add ID to Author
    authorCollection[currentBook->second.getAuthor()].addQuote(reference);
}

void Library::deleteQuote(string reference) {
    map<string, Quote>::iterator it = quoteCollection.find(reference);
    if (it == quoteCollection.end()) {
        cout << "error" << endl;
    } else {
        // Remove Quote from Book
        map<string, Book>::iterator bookIt = bookCollection.find(it->second.getBookTitle());
        if (bookIt != bookCollection.end()) bookIt->second.deleteQuote(reference);
        // Remove Quote from Author
        map<string, Author>::iterator authorIt = authorCollection.find(it->second.getAuthor());
        if (authorIt != authorCollection.end()) authorIt->second.deleteQuote(reference);
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
        if (it->second.getBookCount() > 0) it->second.printInformation();
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
    cout << currentBook->second.getAuthor() << " \"";
    cout << currentBook->second.getTitle() << "\" ";
    cout << currentBook->second.getLineCount() << " ";
    cout << currentBook->second.getWordCount() << endl;
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
