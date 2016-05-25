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
        \post Deletes the implicit quote
    */
    ~Quote();

    /** @brief Return Quote reference
        \pre An implicit Quote
        \post Returns quoteReference
    */
    string getReference() const;

    /** @brief Return Quote's author name
        \pre An implicit Quote
        \post Returns bookAuthor
    */
    string getAuthor() const;

    /** @brief Return Quote's book title
        \pre An implicit Quote
        \post Returns bookTitle
    */
    string getBookTitle() const;

    /** @brief Return Quote start line
        \pre An implicit Quote
        \post Returns quoteStart
    */
    int getStartLine() const;

    /** @brief Return Quote end line
        \pre An implicit Quote
        \post Returns quoteEnd
    */
    int getEndLine() const;

    /** @brief Update the start/end line values
        \param start: Start line
        \param end: End line
        \pre An implicit Quote
        \post Updates the Quote start/end lines
    */
    void setQuoteLines(int start, int end);

    /** @brief Update the quote content
        \param content: Content of the Quote
        \pre An implicit Quote
        \post Updates the Quote content
    */
    void setContent(vector <string> content);

    /** @brief Print content of the implicit Quote
        \pre An implicit Quote
        \post Prints quote content
    */
    void printInformation(bool reference, bool startend);

    /** @brief Print all the information of the implicit Quote
        \pre An implicit Quote
        \post Prints all the quote information
    */
    void printInformationComplex(bool showAuthorName);

};

#endif //PRO2_PRAC_QUOTE_HH
