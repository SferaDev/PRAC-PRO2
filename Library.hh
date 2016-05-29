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

#include "Utils.hh"

#include <iostream>
#include <map>
#include <string>
#include <sstream>

#endif

using namespace std;

/**
  @class Library
  @brief Main storage of each Book, Author and Quote.
*/
class Library {

private:

    /** @brief Collection of Books
        \param string: Key of the identifier
        \param Book: Books of the Library
    */
    map <string, Book> bookCollection;

    /** @brief Collection of Authors
        \param string: Key of the identifier
        \param Author: Authors of the Library
    */
    map <string, Author> authorCollection;

    /** @brief Collection of Quotes
        \param string: Key of the identifier
        \param Quote: Quotes of the Library
    */
    map <string, Quote, utils::stringNaturalComparator> quoteCollection;

    /** @brief Identifier of Quotes
        \param string: Quote ID (without number)
        \param int: Last integer reference for the Quote ID
    */
    map<string, int> quoteIdentifiers;

    /** @brief Current book iterator */
    map<string, Book>::iterator currentBook;

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
        \param title: The book title
        \param author: The book author
        \pre An implicit Library
        \post The implicit library with a new book (identified by title and author)
    */
    void readBook(string title, string authorName);

    /** @brief Returns whether we have a chosen book or not
        \pre An implicit Library
        \post True
    */
    bool isBookSelected();

    /** @brief Selects a book from the collection
        \param query: Query to select a book
        \pre An implicit Library
        \post currentBook iterator has the desired book
    */
    void selectBook(string query);

    /** @brief Deletes a book from the collection
        \pre An implicit Library and a selected book
        \post The implicit library without the previous currentBook
    */
    void deleteBook();

    /** @brief Replaces a word with anopther one in a book from the collection
        \param input: Pattern from the IO channel to replace words
        \pre An implicit Library and a selected book
        \post The implicit library with the replaced words on currentBook
    */
    void replaceWordsOnBook(string oldWord, string newWord);

    /** @brief Inserts a new quote (currentBook) to the library
        \param start: Start line
        \param end: End line
        \pre An implicit Library and implicit book
        \post The implicit library with a new quote
    */
    void insertQuote(int start, int end);

    /** @brief Deletes a quote from the library
        \param id: Quote ID
        \pre An implicit Library and a quote with that id
        \post The implicit library without the referenced quote
    */
    void deleteQuote(string reference);

    /** @brief Returns the selected book
        \pre An implicit Library and a selected book
        \post Returns currentBook
    */
    Book getBook();

    /** @brief Returns if a quote exists with that reference
        \param id: Quote ID
        \pre An implicit Library and a quote with that id
        \post Returns if it exists
    */
    bool quoteExists(string id);

    /** @brief Returns a quote from its ID
        \param id: Quote ID
        \pre An implicit Library and a quote with that id
        \post Returns the quote referenced by id
    */
    Quote getQuote(string id);

    /** @brief Prints information about the Authors
        \pre An implicit Library
        \post True
    */
    void printAuthors();

    /** @brief Prints information about the Books
        \pre An implicit Library
        \post True
    */
    void printBooks();

    /** @brief Prints information about the Quotes
        \pre An implicit Library
        \post True
    */
    void printQuotes();

    /** @brief Prints information about the Books (by Author)
        \param author: Author name
        \pre An implicit Library
        \post True
    */
    void printBooksByAuthor(string author);

    /** @brief Prints information about the Quotes (by Author)
        \param author: Author name
        \pre An implicit Library
        \post True
    */
    void printQuotesByAuthor(string author);

    /** @brief Prints information about current book
        \pre An implicit Library and currentBook
        \post True
    */
    void printCurrentInformation();

    /** @brief Prints quotes of current book
        \pre An implicit Library and currentBook
        \post True
    */
    void printCurrentQuotes();
};

#endif //PRO2_PRAC_LIBRARY_HH
