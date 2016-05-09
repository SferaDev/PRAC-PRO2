/**
  @file Book.hh
  @brief Data model that hosts information about a Book
*/

#ifndef PRO2_PRAC_BOOK_HH
#define PRO2_PRAC_BOOK_HH

#ifndef NO_DIAGRAM
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
#endif

using namespace std;

/**
  @class Book
  @brief Data model for Books (textos) from Library.
*/
class Book {

private:
    /** @brief Name of the author */
    /** @brief The ID on parent authorCollection */
    string authorName;

    /** @brief Name of the book */
    /** @brief The ID of current element */
    string bookTitle;

    /** @brief Content of the book */
    /** @brief The line ID is the position and the value is the content of the book */
    vector<string> bookContent;

    /** @brief Content dictionary by length with words
        \param int: Key of the main map and the length of the word
        \param set<string>: All the words (without marks)
    */
    map<int, set<string> > wordDictionary;

    /** @brief Content dictionary by words with lines
        \param int: Key of the main map and a word
        \param vector<int>: All the lines with that contents a determinate word (without marks)
    */
    map<string, vector<int> > lineDictionary;

    /** @brief Content dictionary with frequencies
        \param string: Key of the identifier
        \param int: Frequencies of the words
    */
    map<string, int> wordFrequencyMap;

    /** @brief Content dictionary with frequencies in correct order */
    vector<pair<string, int> > wordFrequencyVector;

    /** @brief Size of Book's collection */
    int bookWords;

    /** @brief Ordered collection of quotes
        \param string: The ID of the parent quoteCollection
    */
    set<string> bookQuotes;

public:
    /** @brief Creates an empty Book
        \pre True
        \post Returns an implicit empty book
    */
    Book();

    /** @brief Creates a Book with title and author
        \param title: Book title
        \param author: Book author
        \pre True
        \post Returns an implicit book with title and the author
    */
    Book(string title, string author);

    /** @brief Destructs the implicit Book
        \pre An implicit Book
        \post Deletes the implicit book
    */
    ~Book();

    /** @brief Reads the content of the implicit Book
        \pre An implicit Book
        \post The content of the implicit Book in the input channel
    */
    void readBookContent();

    /** @brief Returns the title of the implicit Book
        \pre An implicit Book
        \post The title of the implicit book
    */
    string getTitle() const;

    /** @brief Returns the name of the author of the implicit Book
        \pre An implicit Book
        \post The name of the author of the implicit book
    */
    string getAuthor();

    /** @brief Returns the number of lines of the implicit Book
        \pre An implicit Book
        \post The number of the lines of the implicit book
    */
    int getLineCount();

    /** @brief Returns the number of words of the implicit Book
        \pre An implicit Book
        \post The words of lines of the implicit book
    */
    int getWordCount();

    /** @brief Replaces one word for another word in the implicit Book
        \param oldWord: Word (old)
        \param newWord: Word (new)
        \pre An implicit Book, the old word that we replaces and the new word
        \post The implicit book with the old word replaced for the new word
    */
    void replaceWords(string oldWord, string newWord);

    /** @brief Finds if a word is on the content of the implicit Book
        \param word = Word to find on the book
        \pre The wordDictionary of the implicit Book and a word that we want to find
        \post Returns true if the word is on the content of the implicit book
    */
    bool findWord(string word);

    /** @brief Generates the FrequencyTable Vector
        \pre An implicit Book
        \post Generates the frequency table ordered
    */
    void generateFrequencyTable();

    /** @brief Returns the book quotes
        \pre An implicit Book
        \post Returns the bookQuotes set
    */
    set<string> getBookQuotes();

    /** @brief Returns the lines from start to end
        \pre An implicit Book
        \post Returns the lines from the vector (pos - 1)
    */
    vector<string> getLines(int start, int end);

    /** @brief Adds new Quote to Book
        \pre An implicit Book
        \post bookQuotes has a new element
    */
    void addQuote(string reference);

    /** @brief Removes a  Quote from Book
        \pre An implicit Book
        \post bookQuotes has one less element
    */
    void deleteQuote(string reference);

    /** @brief Prints the information of the implicit book
        \pre An implicit Book
        \post Prints the title and author of the book
    */
    void printInformation();

    /** @brief Prints all lines of the implicit Book, from 1 to bookContent.size()
        \pre An implicit Book
        \post Prints all lines of the content of the implicit book with its number in increasingly ordered for the number
    */
    void printAllLines();

    /** @brief Prints the lines by logical expression match of the implicit Book
        \param query: Query to find the lines to print
        \pre An implicit Book and logical expression match
        \post Prints the lines that keep the logical expression
    */
    void printLines(string query);

    /** @brief Finds the lines that keep the logical expression
        \param query: Query to find the lines to print
        \param pos: Set with all the positions that keep the logical expression
        \pre An implicit Book and logical expression match and empty set
        \post The number of lines that keep the logical expression
    */
    bool findExpression(string query, set<int>& pos);

    /** @brief Prints the lines that contains the consecutive words of the implicit Book
        \param query: sequence of words to find the lines to print
        \pre An implicit Book and sequence of words
        \post Prints the number of the line and the line of the implicit book that contain all the words of the sequence
    */
    void printWordsConsecutiveLines(string query);

    /** @brief Prints lines from [start - 1] to [end - 1]
        \param start: Start line
        \param end: end line
        \pre An implicit Book, and the range
        \post Prints the lines of the range and its number of the implicit book
    */
    void printSelectLines(int start, int end);

    /** @brief Prints all words of the content of the implicit book
        \pre An implicit Book
        \post Prints all words of the content and its frequencies in decreasingly ordered by frequencies
    */
    void printFrequencyTable();

};

#endif //PRO2_PRAC_BOOK_HH
