/**
  @file Author.hh
  @brief Data model that hosts information about an Author
*/

#ifndef PRO2_PRAC_AUTHOR_HH
#define PRO2_PRAC_AUTHOR_HH

#ifndef NO_DIAGRAM
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

    string authorName; // Name of the author

    // Size of Author's collection
    int totalBooks;
    int totalLines;
    int totalWords;

    set<string> authorBooks; // Ordered collection of books
                             // Value: the ID of the parent bookCollection


    set<string> authorQuotes; // Ordered collection of quotes
                              // Value: the ID of the parent quoteCollection

public:
    /** @brief Creates an empty Author
        \pre True
        \post Returns an implicit empty author
    */
    Author();
    
    /** @brief Creates an empty Author
        \param name = Name of the Author
        \pre True
        \post Returns an implicit author with name
    */
    Author(string name);

    /** @brief Destructs the implicit Author
        \pre An implicit Author
        \post Deletes the implicit author
    */
    ~Author();
    
    void incrementBookCount(int value);
    
    void incrementLineCount(int value);
    
    void incrementWordCount(int value);
    
    void addBook(string title);
    
    void addQuote();
    
    void deleteBook(string title);
    
    void deleteQuote(string id);
    
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

    /** @brief Prints information about the Quotes
        \pre An implicit Author
        \post True
    */
    void printQuotes();

};

#endif //PRO2_PRAC_AUTHOR_HH