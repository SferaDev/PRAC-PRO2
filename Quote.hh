/**
  @file Quote.hh
  @brief Data model that hosts information about a Quote
*/

#ifndef PRO2_PRAC_QUOTE_HH
#define PRO2_PRAC_QUOTE_HH

#ifndef NO_DIAGRAM
#include <string>
#include <vector>
#endif

using namespace std;

/** @class Quote
    @brief Data model for Quotes (cites) from Books.
    */
class Quote {

private:
    string quoteReference; // Identifier of the Quote

    string quoteAuthor; // Identifier of the Author

    string quoteBook; // Identifier of the Book

    int quoteStart, quoteEnd; // Identifier of the lines

    vector<string> quoteContent; // Content of the Quote (ID: position | Value: content)

public:
    /** @brief Creates an empty Quote
        \pre True
        \post Returns an implicit empty quote
    */
    Quote();

    /** @brief Destructs the implicit Quote
        \pre An implicit Quote
        \post Deletes the implicit quote
    */
    ~Quote();

    /** @brief Print all the information of the implicit Quote
        \pre An implicit Quote
        \post Prints all the information
    */
    void printQuoteInformation();
};

#endif //PRO2_PRAC_QUOTE_HH
