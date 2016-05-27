/**
  @file Library.hh
  @brief Main structure of our Library with several dependant data childs.
*/

#ifndef PRO2_PRAC_LIBRARY_HH
#define PRO2_PRAC_LIBRARY_HH

#include "Author.hh"
#include "Book.hh"
#include "Quote.hh"

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
        \post Deletes the implicit Library
    */
    ~Library();

    /** @brief Inserts a new book to the bookCollection
        \param title: The book title
        \param author: The book author
        \pre An implicit Library
        \post The implicit Library with a new book (identified by title and author)
    */
    void readBook(string title, string authorName);

    /** @brief Provides whether we have a chosen book or not
        \pre An implicit Library
        \post True
        \returns Returns true if there is a book chosen
    */
    bool isBookSelected();

    /** @brief Selects a book from the collection
        \param query: Query to select a book
        \pre An implicit Library
        \post currentBook iterator has the desired book
    */
    void selectBook(string query);

    /** @brief Deletes a book from the collection of the implicit Library
        \pre An implicit Library and a selected book
        \post The implicit library without the previous currentBook
    */
    void deleteBook();

    /** @brief Replaces a word with another one in a book from the collection of the implicit Library
        \param input: Pattern from the IO channel to replace words
        \pre An implicit Library and a selected book
        \post The implicit Library with the replaced words on currentBook
    */
    void replaceWordsOnBook(string oldWord, string newWord);

    /** @brief Inserts a new quote (currentBook) to the implicit Library
        \param start: Start line
        \param end: End line
        \pre An implicit Library and implicit Book
        \post The implicit Library with a new quote
    */
    void insertQuote(int start, int end);

    /** @brief Deletes a Quote from the implicit Library
        \param id: Quote ID
        \pre An implicit Library and a quote with that ID
        \post The implicit Library without the referenced quote
    */
    void deleteQuote(string reference);

    /** @brief Provides the selected Book
        \pre An implicit Library and a selected Book
        \post True
        \returns Returns currentBook
    */
    Book getBook();

    /** @brief Tells if a quote exists with that reference
        \param id: Quote ID
        \pre An implicit Library and a Quote with that ID
        \post True
        \returns Returns if it exists
    */
    bool quoteExists(string id);

    /** @brief Provides a Quote from its ID
        \param id: Quote ID
        \pre An implicit Library and a Quote with that ID
        \post True
        \returns Returns the Quote referenced by ID
    */
    Quote getQuote(string id);

    /** @brief Provides information about the Authors
        \pre An implicit Library
        \post True
    */
    void printAuthors();

    /** @brief Provides information about the Books
        \pre An implicit Library
        \post True
    */
    void printBooks();

    /** @brief Provides information about the Quotes
        \pre An implicit Library
        \post True
    */
    void printQuotes();

    /** @brief Provides information about the Books (by Author)
        \param author: Author name
        \pre An implicit Library
        \post True
    */
    void printBooksByAuthor(string author);

    /** @brief Provides information about the Quotes (by Author)
        \param author: Author name
        \pre An implicit Library
        \post True
    */
    void printQuotesByAuthor(string author);

    /** @brief Provides information about current book
        \pre An implicit Library and currentBook
        \post True
    */
    void printCurrentInformation();

    /** @brief Provides quotes of current book
        \pre An implicit Library and currentBook
        \post True
    */
    void printCurrentQuotes();
};

#endif //PRO2_PRAC_LIBRARY_HH
