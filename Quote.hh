#ifndef PRO2_PRAC_QUOTE_HH
#define PRO2_PRAC_QUOTE_HH

class Quote {

private:
    // Identifier of the Quote
    string quoteReference;

    // Identifier of the Author
    string quoteAuthor;

    // Identifier of the Book
    string quoteBook;

    // Identifier of the lines
    int quoteStart, quoteEnd;

    // Content of the Quote
    // Position is the line ID and value is the content
    vector<string> quoteContent;

public:
    // Constructor
    Quote();

    // Destructor
    ~Quote();

    // Print all the info related (info cita "<referencia>" ?)
    void printQuoteInformation();
};

#endif //PRO2_PRAC_QUOTE_HH
