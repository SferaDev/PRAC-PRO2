/**
  @file Author.hh
  @brief Data model that hosts information about an Author
*/

#ifndef PRO2_PRAC_AUTHOR_HH
#define PRO2_PRAC_AUTHOR_HH

#ifndef NO_DIAGRAM
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
        \param string: the ID of the parent bookCollection
     */
    set<string> authorBooks;

    /** @brief Ordered collection of quotes
        \param string: the ID of the parent quoteCollection
    */
    set<string> authorQuotes;

public:
    /** @brief Creates an empty Author
        \pre True
        \post Returns an implicit empty author
    */
    Author();
    
    /** @brief Creates an empty Author
        \param name: Name of the Author
        \pre True
        \post Returns an implicit author with name
    */
    Author(string name);

    /** @brief Destructs the implicit Author
        \pre An implicit Author
        \post Deletes the implicit author
    */
    ~Author();

    /** @brief Increments the number of books of the implicit author
        \param value: Number of news books
        \pre An implicit Author
        \post The totalBooks of the implicit author increased
    */
    void incrementBookCount(int value);

    /** @brief Increments the number of lines of the implicit author
        \param value: Number of lines of news books
        \pre An implicit Author
        \post The totalLines of the implicit author increased
    */
    void incrementLineCount(int value);

    /** @brief Increments the number of the words of the implicit author
        \param value: Number of words of news books
        \pre An implicit Author
        \post The totalWords of the implicit author increased
    */
    void incrementWordCount(int value);

    int getBookCount();

    int getLineCount();

    int getWordCount();

    /** @brief Adds new Book to Author
        \param title: Book title
        \pre An implicit Author
        \post authorBook has a new element
    */
    void addBook(string title);

    /** @brief Adds new Quote to Author
        \param reference: ID of the Quote
        \pre An implicit Book
        \post authorQuotes has a new element
    */
    void addQuote(string reference);

    /** @brief Removes a Book from Author
        \param title: Book title
        \pre An implicit Author
        \post authorBook has one less element
    */
    void deleteBook(string title);

    /** @brief Removes a Quote from Author
        \param reference: ID of the Quote
        \pre An implicit Book
        \post authorQuotes has one less element
    */
    void deleteQuote(string reference);

    /** @brief Returns the author quotes
        \pre An implicit Author
        \post Returns the authorQuotes set
    */
    set<string> getAuthorQuotes();

    /** @brief Returns if Author has any book
        \pre An implicit Author
        \post Returns true if books is not empty
    */
    bool isEmpty();
    
    /** @brief Prints information about the Author
        \pre An implicit Author
        \post True
    */
    void printInformation();

    /** @brief Prints information about the Books
        \pre An implicit Author
        \post True
    */
    void printBooks();

};

#endif //PRO2_PRAC_AUTHOR_HH