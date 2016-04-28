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

void Quote::printInformation() {
    cout << quoteReference << endl;
    for (int i = 0; i < quoteContent.size(); ++i) {
        cout << i + quoteStart << " ";
        cout << quoteContent[i] << endl;
    }
}

void Quote::printInformationComplex() {
    printInformation();
    cout << quoteAuthor << " " << quoteBook;
}