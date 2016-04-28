/**
  @file Quote.hh
  @brief Data model that hosts information about a Quote
*/

#ifndef PRO2_PRAC_QUOTE_HH
#define PRO2_PRAC_QUOTE_HH

#ifndef NO_DIAGRAM
#include <iostream>
#include <string>
#include <vector>
#endif

using namespace std;

/**
  @class Quote
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

    /** @brief Creates an empty Quote
        \param reference = The reference ID
        \param author = The Quote Author
        \param book = The book from the Quote
        \pre True
        \post Returns an implicit quote with the reference, author and book
    */
    Quote(string reference, string author, string book);

    /** @brief Destructs the implicit Quote
        \pre An implicit Quote
        \post Deletes the implicit quote
    */
    ~Quote();

    /** @brief Print all the information of the implicit Quote
        \pre An implicit Quote
        \post Prints all the quote information
    */
    void printInformation();

    /** @brief Update the start/end line values
        \param start = Start line
        \param end = End line
        \pre An implicit Quote
        \post Updates the Quote start/end lines
    */
    void setQuoteLines(int start, int end);

    /** @brief Update the quote content
        \param content = Content of the Quote
        \pre An implicit Quote
        \post Updates the Quote content
    */
    void setContent(vector<string> content);

    };

#endif //PRO2_PRAC_QUOTE_HH
