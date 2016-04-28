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

string Quote::getReference() {
    return quoteReference;
}

string Quote::getAuthor() {
    return quoteAuthor;
}

string Quote::getBookTitle() {
    return quoteBook;
}

int Quote::getStartLine() {
    return quoteStart;
}

int Quote::getEndLine() {
    return quoteEnd;
}

void Quote::setQuoteLines(int start, int end) {
    quoteStart = start;
    quoteEnd = end;
}

void Quote::setContent(vector<string> content) {
    // Copy of a vector FIXME
    quoteContent = content;
}

void Quote::printInformation(bool reference, bool startend) {
    if (reference) cout << quoteReference << endl;
    if (startend) cout << quoteStart << "-" << quoteEnd << endl;
    for (int i = 0; i < quoteContent.size(); ++i) {
        cout << i + quoteStart << " " << quoteContent[i] << endl;
    }
}

void Quote::printInformationComplex() {
    printInformation(true, false);
    cout << quoteAuthor << " \"" << quoteBook << "\" " << endl;
}