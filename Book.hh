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
    /** @brief Name of the author (ID on parent authorCollection) */
    string authorName;

    string bookTitle; // Name of the book (ID of current element)

    vector<string> bookContent; // Content of the book (The line ID: position | Value: content)

    // Content dictionary
    // On the main map the key is the length of the word
    // On the inner map it has a word (without marks)
    map<int, set<string> > wordDictionary;

    // Content dictionary with frequencies
    // The key is the length of the word
    // The value is its frequencies
    map<string, int> wordFrequencyMap;
    vector<pair<string, int> > wordFrequencyVector;

    // Size of Book's collection
    int bookWords;

    set<string> bookQuotes; // Ordered collection of quotes
                            // The value of the item is the ID of the parent quoteCollection

    /** @brief Comparator for the frequencyTable */
    struct frequencyComparator {
        bool operator()(const pair<string, int>& a, const pair<string, int>& b) {
            // Special case: Same frequency
            if (a.second == b.second) {
                // Special case: Same length
                if (a.first.length() == b.first.length()) {
                    // Make a lower case copy of the strings and compare them
                    string aString = a.first;
                    string bString = b.first;
                    // Inv: They have the same length
                    for (int i = 0; i < aString.length(); ++i) {
                        aString[i] = tolower(aString[i]);
                        bString[i] = tolower(bString[i]);
                    }
                    return aString < bString;
                }
                // Base case: Order by length in asc order
                return a.first.length() < b.first.length();
            }
            // Base case: Order by frequency in desc order
            return a.second > b.second;
        }
    };

public:
    /** @brief Creates an empty Book
        \pre True
        \post Returns an implicit empty book
    */
    Book();

    /** @brief Creates a Book with title and author
        \param title = Book title
        \param author = Book author
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
        \post The content of the implicit Book
    */
    void readBookContent();

    /** @brief Returns the title of the implicit Book
        \pre An implicit Book
        \post The title of the implicit book
    */
    string getBookTitle() const;

    /** @brief Returns the name of the author of the implicit Book
        \pre An implicit Book
        \post The name of the author of the implicit book
    */
    string getAuthorName();

    /** @brief Returns the number of lines of the implicit Book
        \pre An implicit Book
        \post The number of the lines of the implicit book
    */
    int getBookLines();

    /** @brief Returns the number of words of the implicit Book
        \pre An implicit Book
        \post The words of lines of the implicit book
    */
    int getBookWords();

    /** @brief Replaces one word for another word in the implicit Book
        \param oldWord = Word (old)
        \param newWord = Word (new)
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
    void getLines(vector<string> vector, int start, int end);

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
        \param query = Query to find the lines to print
        \pre An implicit Book and logical expression match
        \post Prints the number of the line and the line of the implicit book that keep the logical expression
    */
    void printLines(string query);

    /** @brief Prints lines from [start - 1] to [end - 1]
        \param start = Start line
        \param end = end line
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