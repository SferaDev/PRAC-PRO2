/**
  @file Book.hh
  @brief Data model that hosts information about a Book
*/

#ifndef PRO2_PRAC_BOOK_HH
#define PRO2_PRAC_BOOK_HH

#ifndef NO_DIAGRAM

#include "Utils.hh"

#include <algorithm>
#include <list>
#include <map>
#include <set>
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
    /** @brief ID: parent authorCollection */
    string authorName;

    /** @brief Name of the book */
    /** @brief ID: current element */
    string bookTitle;

    /** @brief Content of the book */
    /** @brief ID: position and value: content of the book */
    vector <string> bookContent;

    /** @brief Content dictionary by words with lines
        \param string: Key of the main map that it is a word
        \param list<int>: All the lines with that contents a determinate word (without marks)
    */
    map <string, list<int> > lineDictionary;

    /** @brief Content dictionary with frequencies
        \param string: Key of the identifier
        \param int: Frequencies of the words
    */
    map<string, int> wordFrequencyMap;

    /** @brief Content dictionary with frequencies in correct order
        \param string: A word
        \param int: Frequencies of the words
    */
    list <pair<string, int> > wordFrequencyList;

    /** @brief Tells if we generate the frequency table (not generated previously or modified) */
    bool dirtyFrequency;

    /** @brief Tells if the Book has been deleted */
    bool deleted;

    /** @brief Size of Book's collection */
    int bookWords;

    /** @brief Ordered collection of quotes
        \param string: The ID of the parent quoteCollection
    */
    set <string, utils::stringNaturalComparator> bookQuotes;

public:
    /** @brief Creates an empty Book
        \pre True
        \post Returns an implicit empty Book
    */
    Book();

    /** @brief Creates a Book with title and author
        \param title: Book title
        \param author: Book author
        \pre True
        \post Returns an implicit Book with title and the author
    */
    Book(string title, string author);

    /** @brief Destructs the implicit Book
        \pre An implicit Book
        \post Deletes the implicit Book
    */
    ~Book();

    /** @brief Reads the content of the implicit Book
        \pre An implicit Book
        \post The content of the implicit Book in the input channel
    */
    void readBookContent();

    /** @brief Provides the title of the implicit Book
        \pre An implicit Book
        \post True
        \returns Returns the title of the implicit Book
    */
    string getTitle() const;

    /** @brief Provides the name of the author of the implicit Book
        \pre An implicit Book
        \post True
        \returns Returns the name of the author of the implicit Book
    */
    string getAuthor() const;

    /** @brief Gives back the number of lines of the implicit Book
        \pre An implicit Book
        \post True
        \returns Returns the number of the lines of the implicit Book
    */
    int getLineCount() const;

    /** @brief Gives back the number of words of the implicit Book
        \pre An implicit Book
        \post True
        \returns The words of lines of the implicit Book
    */
    int getWordCount() const;

    /** @brief Replaces one word for another word in the implicit Book
        \param oldWord: Word (old)
        \param newWord: Word (new)
        \pre An implicit Book, the old word that we replaces and the new word
        \post The implicit Book with the old word replaced for the new word
    */
    void replaceWords(string oldWord, string newWord);

    /** @brief Finds if a word is on the content of the implicit Book
         \param word: Word to find on the implicit Book
         \pre The wordFrequencyMap of the implicit Book and a word that we want to find
         \post True
         \returns Returns true if the word is on the content of the implicit Book
     */
    bool findWord(string word);

    /** @brief Tells if a dirtyFrequency is true or false
        \pre An implicit Book
        \post True
        \returns Returns true if the frequency table needs to be updated is true
    */
    bool isFrequencyDirty();

    /** @brief Tells if a deleted is true or false
        \pre An implicit Book
        \post True
        \returns Returns true if the Book has been deleted
    */
    bool isDeleted();

    /** @brief Generates the wordFrequencyList
        \pre An implicit Book
        \post Generates the frequency table ordered
    */
    void generateFrequencyTable();

    /** @brief Provides the bookQuotes of the implicit Book
        \pre An implicit Book
        \post True
        \returns Returns the bookQuotes set
    */
    set <string, utils::stringNaturalComparator> getBookQuotes();

    /** @brief Provides the lines from start to end
        \pre An implicit Book
        \post True
        \returns Returns the content of the lines from the vector (pos - 1)
    */
    vector <string> getLines(int start, int end);

    /** @brief Adds new Quote to the implicit Book
        \pre An implicit Book
        \post bookQuotes has a new element
    */
    void addQuote(string reference);

    /** @brief Removes a Quote from the implicit Book
        \pre An implicit Book
        \post bookQuotes has one less element
    */
    void deleteQuote(string reference);

    /** @brief Marks the book as deleted
        \pre An implicit Book
        \post The book has been deleted
    */
    void deleteBook();

    /** @brief Finds the lines of the implicit Book that keep the logical expression
        \param query: Query to find the lines to print
        \param pos: Set with all the positions that keep the logical expression
        \pre An implicit Book and logical expression match and empty set
        \post The number of lines that keep the logical expression
    */
    void findExpression(string query, set<int> &pos);

    /** @brief Provides the information of the implicit Book
        \pre An implicit Book
        \post Prints the title and author of the Book
    */
    void printInformation();

    /** @brief Provides all lines of the implicit Book, from 1 to bookContent.size()
        \pre An implicit Book
        \post Prints all lines of the content of the implicit Book with its number in increasingly ordered for the number
    */
    void printAllLines();

    /** @brief Provides the lines by logical expression match of the implicit Book
        \param query: Query to find the lines to print of the implicit Book
        \pre An implicit Book and logical expression match
        \post Prints the lines of the implicit Book that keep the logical expression
    */
    void printLines(string query);

    /** @brief Provides the lines of the implicit Book that contains the consecutive words
        \param query: Sequence of words to match on each line of the content
        \pre An implicit Book and sequence of words
        \post Prints the number of the line and the line of the implicit Book that contain all the words of the sequence
    */
    void printLinesConsecutiveWords(string query);

    /** @brief Provides lines of the implicit Book from [start - 1] to [end - 1]
        \param start: Start line of the implicit Book
        \param end: end line of the implicit Book
        \pre An implicit Book, and the range
        \post Prints the lines of the range and its number of the implicit Book
    */
    void printSelectLines(int start, int end);

    /** @brief Provides all words of the content of the implicit Book
        \pre An implicit Book
        \post Prints all words of the content of the implicit Book and its frequencies in decreasingly ordered by frequencies
    */
    void printFrequencyTable();

};

#endif //PRO2_PRAC_BOOK_HH
