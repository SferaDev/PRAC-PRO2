/**
  @file Quote.cc
  @brief Class for the Quote definition
*/

#include "Quote.hh"
#include <sstream>

using namespace std;

Quote::Quote() {
    // TODO
}

Quote::Quote(string reference, string author, string book) {
    quoteReference = reference;
    quoteAuthor = author;
    quoteBook = book;
}

Quote::~Quote() {
    // no-op
}

string Quote::getReference() const {
    return quoteReference;
}

string Quote::getAuthor() const {
    return quoteAuthor;
}

string Quote::getBookTitle() const {
    return quoteBook;
}

int Quote::getStartLine() const {
    return quoteStart;
}

int Quote::getEndLine() const {
    return quoteEnd;
}

void Quote::setQuoteLines(int start, int end) {
    quoteStart = start;
    quoteEnd = end;
}

void Quote::setContent(vector<string> content) {
    // FIXME: Copy of a vector (slow?)
    quoteContent = content;
}

void Quote::printInformation(bool reference, bool startend) {
    if (!quoteBook.empty()) {
        if (reference) cout << quoteReference << endl;
        if (startend) cout << quoteStart << "-" << quoteEnd << endl;
        for (int i = 0; i < quoteContent.size(); ++i) {
            cout << i + quoteStart << " " << quoteContent[i] << endl;
        }
    }
}

void Quote::printInformationComplex(bool showAuthorName) {
    if (!quoteBook.empty()) {
        printInformation(true, false);
        if (showAuthorName) cout << quoteAuthor << " ";
        cout << "\"" << quoteBook << "\"" << endl;
    }
}