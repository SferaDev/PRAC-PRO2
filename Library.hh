/**
  @file Library.hh
  @brief Main structure of our Library with several dependant data childs.
*/

#ifndef PRO2_PRAC_LIBRARY_HH
#define PRO2_PRAC_LIBRARY_HH

#include "Author.hh"
#include "Book.hh"
#include "Quote.hh"

#include <iostream>
#include <map>
#include <string>
using namespace std;

class Library {

private:
    // Collection of Books
    map<string, Book> bookCollection;

    // Collection of Authors
    map<string, Author> authorCollection;

    // Collection of Quotes
    map<string, Quote> quoteCollection;

    // Current book iterator
    map<string, Book>::iterator currentBook;

public:
    // Constructor
    Library();

    // Destructor
    ~Library();

    // Inserts a new book to the bookCollection
    void readBook(string title, string author);

    // Returns whether we have a chosen book or not
    bool isBookSelected();

    // Selects a book from the collection at currentBook iterator
    // foreach Author find on its dictionary by size
    void selectBook(string query);

    // Deletes currentBook iterator from the bookCollection
    void deleteBook();

    // Replaces currentBook words
    void replaceWordsOnBook(string input);

    // Deletes a quote from the quoteCollection
    void deleteQuote(string id);

    // Get implicit currentBook
    Book getBook();

    // Get a Quote by reference
    Quote getQuote(string id);

    // Print Author's info
    void printAuthors();

    // Print Books info stored on bookCollection
    // foreach Author bring its books (already ordered)
    void printBooks();

    // Print Quotes info stored on quoteCollection
    void printQuotes();

    // Print Books by Author
    void printBooksByAuthor(string author);

    // Print Quotes by Author
    void printQuotesByAuthor(string author);
};

#endif //PRO2_PRAC_LIBRARY_HH