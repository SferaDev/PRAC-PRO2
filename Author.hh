/**
  @file Author.hh
  @brief Data model that hosts information about an Author
*/

#ifndef PRO2_PRAC_AUTHOR_HH
#define PRO2_PRAC_AUTHOR_HH

#include <set>
#include <string>
using namespace std;

class Author {

private:
    // Name of the author
    string authorName;

    // Size of Author's collection
    int totalBooks;
    int totalLines;
    int totalWords;

    // Ordered collection of books
    // The value of the item is the ID of the parent bookCollection
    set<string> authorBooks;

    // Ordered collection of quotes
    // The value of the item is the ID of the parent quoteCollection
    set<string> authorQuotes;

public:
    // Constructor
    Author();

    // Destructor
    ~Author();

};

#endif //PRO2_PRAC_AUTHOR_HH