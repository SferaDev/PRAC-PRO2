/**
  @file Author.hh
  @brief Data model that hosts information about an Author
*/

#ifndef PRO2_PRAC_AUTHOR_HH
#define PRO2_PRAC_AUTHOR_HH

#ifndef NO_DIAGRAM

#include "Utils.hh"
#include <iostream>
#include <set>
#include <string>

#endif
using namespace std;

/**
  @class Author
  @brief Data model for Authors (autors) from Library.
*/
class Author {

private:

    /** @brief Name of the author */
    string authorName; //

    /** @brief Number of total books of the author */
    int totalBooks;

    /** @brief Number of total lines of all of books of the author */
    int totalLines;

    /** @brief Number of total words of all of books of the author */
    int totalWords;

    /** @brief Ordered collection of books
        \param string: the ID of the parent (Library) bookCollection's
     */
    set <string> authorBooks;

    /** @brief Ordered collection of quotes
        \param string: the ID of the parent (Library) quoteCollection's
    */
    set <string, utils::stringNaturalComparator> authorQuotes;

public:
    /** @brief Creates an empty Author
        \pre True
        \post Returns an implicit empty Author
    */
    Author();

    /** @brief Creates an empty Author
        \param name: Name of the Author
        \pre True
        \post Returns an implicit Author with name
    */
    Author(string name);

    /** @brief Destructs the implicit Author
        \pre An implicit Author
        \post Deletes the implicit author
    */
    ~Author();

    /** @brief Increments the number of books of the implicit Author
        \param value: Number books to add/substract from the implicit Author
        \pre An implicit Author
        \post Updates totalBooks on the implicit Author by increasing by "value"
    */
    void incrementBookCount(int value);

    /** @brief Increments the number of lines of the implicit Author
        \param value: Number of lines to add/substract from the implicit author
        \pre An implicit Author
        \post Updates totalLines on the implicit Author by increasing by "value"
    */
    void incrementLineCount(int value);

    /** @brief Increments the number of words of the implicit Author
        \param value: Number of words to add/substract from the implicit author
        \pre An implicit Author
        \post Updates totalWords on the implicit Author by increasing by "value"
    */
    void incrementWordCount(int value);

    /** @brief Returns the number of books of the implicit Author
        \pre An implicit Author
        \post True
        \returns Returns totalBooks of the implicit Author
    */
    int getBookCount() const;

    /** @brief Returns the number of lines of all books of the implicit Author
        \pre An implicit Author
        \post True
        \returns Returns totalLines of the implicit Author
    */
    int getLineCount() const;

    /** @brief Returns the number of words of all books of the implicit Author
        \pre An implicit Author
        \post Returns the totalWords of the implicit Author
    */
    int getWordCount() const;

    /** @brief Adds new Book to implicit Author
        \param title: Book title
        \pre An implicit Author
        \post Updates authorBook with a new element (ref: title)
    */
    void addBook(string title);

    /** @brief Adds new Quote to the implicit Author
        \param reference: ID of the Quote
        \pre An implicit Book
        \post Updates authorQuotes with a new element (ref: reference)
    */
    void addQuote(string reference);

    /** @brief Removes a Book from the implicit Author
        \param title: Book title
        \pre An implicit Author
        \post Updates authorBook without a book (ref: title)
    */
    void deleteBook(string title);

    /** @brief Removes a Quote from the implicit Author
        \param reference: ID of the Quote
        \pre An implicit Book
        \post Updates authorQuotes without a quote (ref: reference)
    */
    void deleteQuote(string reference);

    /** @brief Delivers the quotes of the implicit Author
        \pre An implicit Author
        \post True
        \returns Returns the authorQuotes set
    */
    set <string, utils::stringNaturalComparator> getAuthorQuotes();

    /** @brief Checks if the implicit Author has any book
        \pre An implicit Author
        \post True
        \returns Returns true if Author is not empty
    */
    bool isEmpty();

    /** @brief Output operation: Prints information about the implicit Author
        \pre An implicit Author
        \post True
    */
    void printInformation();

    /** @brief Output operation: Prints information about the Books of the implicit author
        \pre An implicit Author
        \post True
    */
    void printBooks(bool showAuthor);

};

#endif //PRO2_PRAC_AUTHOR_HH