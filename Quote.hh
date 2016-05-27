/**
  @file Quote.hh
  @brief Data model that hosts information about a Quote
*/

#ifndef PRO2_PRAC_QUOTE_HH
#define PRO2_PRAC_QUOTE_HH

#ifndef NO_DIAGRAM

#include <iostream>
#include <vector>

#endif

using namespace std;

/**
  @class Quote
  @brief Data model for Quotes (cites) from Book.
*/
class Quote {

private:

    /** @brief Identifier of the Quote */
    string quoteReference;

    /** @brief Identifier of the Author */
    string quoteAuthor;

    /** @brief Identifier of the Book */
    string quoteBook;

    /** @brief Identifier of the lines */
    int quoteStart, quoteEnd;

    /** @brief Content of the Quote */
    /** @brief: The ID is the position and the value is the content of the Quote */
    vector <string> quoteContent;

public:
    /** @brief Creates an empty Quote
        \pre True
        \post Returns an implicit empty quote
    */
    Quote();

    /** @brief Creates an empty Quote
        \param reference: The reference ID
        \param author: The Quote Author
        \param book: The book from the Quote
        \pre True
        \post Returns an implicit quote with the reference, author and book
    */
    Quote(string reference, string author, string book);

    /** @brief Destructs the implicit Quote
        \pre An implicit Quote
        \post Deletes the implicit Quote
    */
    ~Quote();

    /** @brief Provides the reference of the implicit Quote
        \pre An implicit Quote
        \post True
        \returns Returns quoteReference
    */
    string getReference() const;

    /** @brief Provides the author name of the implicit Quote
        \pre An implicit Quote
        \post True
        \returns Returns bookAuthor
    */
    string getAuthor() const;

    /** @brief Provides the book title of the implicit Quote
        \pre An implicit Quote
        \post True
        \returns Returns bookTitle
    */
    string getBookTitle() const;

    /** @brief Provides the start line of the implicit Quote
        \pre An implicit Quote
        \post True
        \returns Returns quoteStart
    */
    int getStartLine() const;

    /** @brief Provides the end line of the implicit Quote
        \pre An implicit Quote
        \post True
        \returns Returns quoteEnd
    */
    int getEndLine() const;

    /** @brief Update the start/end line values
        \param start: Start line
        \param end: End line
        \pre An implicit Quote
        \post Updates the quoteStart and quoteEnd
    */
    void setQuoteLines(int start, int end);

    /** @brief Update the content of the implicit Quote
        \param content: New content of the implicit Quote
        \pre An implicit Quote
        \post Updates the quoteContent
    */
    void setContent(vector <string> content);

    /** @brief Provides the content of the implicit Quote
        \param reference: Option to show the reference ID on the print operation
        \param startend: Option to show the start/end line on the print operation
        \pre An implicit Quote
        \post Prints quoteContent
    */
    void printInformation(bool reference, bool startend);

    /** @brief Provides all the information of the implicit Quote
        \param showAuthorName: Option to show the Author Name on the print operation
        \pre An implicit Quote
        \post Prints all the quote information
    */
    void printInformationComplex(bool showAuthorName);

};

#endif //PRO2_PRAC_QUOTE_HH
