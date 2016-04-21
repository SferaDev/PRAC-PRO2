/**
  @file Quote.cc
  @brief Class for the Quote definition
*/

#include "Quote.hh"
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

void Quote::setQuoteLines(int start, int end) {
    quoteStart = start;
    quoteEnd = end;
}

void Quote::setContent(vector<string> content) {
    // Copy of a vector FIXME
    quoteContent = content;
}

void Quote::printQuoteInformation() {
    // TODO
}