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

    /** @brief Destructs the implicit Author
        \pre An implicit Author
        \post Deletes the implicit author
    */
    ~Author();

};

#endif //PRO2_PRAC_AUTHOR_HH