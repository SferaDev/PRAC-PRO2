#ifndef PRO2_PRAC_LIBRARY_HH
#define PRO2_PRAC_LIBRARY_HH

#include "Author.hh"
#include "Book.hh"

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

    //TODO: Set of private actions

public:
    // Constructor
    Library();

    // Destructor
    ~Library();

    // Inserts a new book to the bookCollection
    void insertBook(const Book& book);

    // Selects a book from the collection at currentBook iterator
    // foreach Author find on its dictionary by size
    void selectBook(string query);

    // Deletes currentBook iterator from the collection
    void deleteBook();

    // Get implicit currentBook
    Book getBook();

    // Print Author's info
    void printAuthors();

    // Print Books info stored on bookCollection
    // foreach Author bring its books (already ordered)
    void printBooks();

    // Print Books by Author
    void printBooksByAuthor(string author);
};

#endif //PRO2_PRAC_LIBRARY_HH