/**
  @file Library.hh
  @brief Main structure of our Library with several dependant data childs.
*/

#ifndef PRO2_PRAC_LIBRARY_HH
#define PRO2_PRAC_LIBRARY_HH

#include "Author.hh"
#include "Book.hh"
#include "Quote.hh"

#ifndef NO_DIAGRAM
#include <iostream>
#include <map>
#include <string>
#endif

using namespace std;

class Library {

private:

    map<string, Book> bookCollection;// Collection of Books

    map<string, Author> authorCollection;// Collection of Authors

    map<string, Quote> quoteCollection;// Collection of Quotes

    map<string, Book>::iterator currentBook;// Current book iterator

public:
    /** @brief Creates an empty Library
        \pre True
        \post Returns an implicit empty library
    */
    Library();

    /** @brief Destructs the implicit Library
        \pre An implicit Library
        \post Deletes the implicit library
    */
    ~Library();

    /** @brief Inserts a new book to the bookCollection
        \pre An implicit Library,  the title and the author of the new book
        \post The implicit library with a new book
    */
    void readBook(string title, string author);

    /** @brief Returns whether we have a chosen book or not
        \pre An implicit Library
        \post The result tell us if we choose a book
    */
    bool isBookSelected();

    // TODO
    /** @brief Selects a book from the collection at currentBook iterator foreach Author find on its dictionary by size
        \pre An implicit Library an
        \post The implicit library with a new book
    */
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