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

/** @class Book
    @brief Data model for Books (textos) from Library.
    */
class Book {

private:

    string authorName; // Name of the author (ID on parent authorCollection)

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
    int bookLines;
    int bookWords;

    set<string> bookQuotes; // Ordered collection of quotes
                            // The value of the item is the ID of the parent quoteCollection

    // Comparator for the frequency sort
    struct frequencyComparator {
        bool operator()(const pair<string, int>& a, const pair<string, int>& b) {
            // CHECKME: I'm a blind ninja
            if (a.second == b.second) return a.first < b.first;
            return a.second > b.second;
        }
    };

public:
    /** @brief Creates an empty Book
        \pre True
        \post Returns an implicit empty book
    */
    Book();

    /** @brief Creates a Book
        \pre True
        \post Returns an implicit book with the title and the author
    */
    Book(string title, string author);

    /** @brief Destructs the implicit Book
        \pre An implicit Book
        \post Deletes the implicit book
    */
    ~Book();

    /** @brief Read the content of the implicit Book
        \pre An implicit Book
        \post The content of the implicit Book
    */
    void readBookContent();

    /** @brief Return the title of the implicit Book
        \pre An implicit Book
        \post The title of the implicit book
    */
    string getBookTitle() const;

    /** @brief Return the name of the author of the implicit Book
        \pre An implicit Book
        \post The name of the author of the implicit book
    */
    string getAuthorName();

    // Returns bookLines
    /** @brief Return the number of the lines of the implicit Book
        \pre An implicit Book
        \post The number of the lines of the implicit book
    */
    int getBookLines();

    // Returns bookWords
    /** @brief Return the number of words of the implicit Book
        \pre An implicit Book
        \post The words of the lines of the implicit book
    */
    int getBookWords();

    // Replace contents on currentBook
    /** @brief Replace one word for another word in the implicit Book
        \pre An implicit Book, the old word that we replace and the new word
        \post The implicit book with the old word replaced for the new word
    */
    void replaceWords(string oldWord, string newWord);

    // Finds if a word is on the content
    bool findWord(string word);

    // Generates the FrequencyTable Vector
    void generateFrequencyTable();

    // Calls printSelectLines from 1 to bookContent.size()
    /** @brief Print all the lines of the implicit Book, from 1 to bookContent.size()
        \pre An implicit Book
        \post Prints all lines of the content of the implicit book with its number in increasingly ordered for the number
    */
    void printAllLines();

    // Print lines by logical expression match
    // RECURSIVE
    /** @brief Print lines by logical expression match of the implicit Book
        \pre An implicit Book and logical expression match
        \post Prints the number of the line and the line of the implicit book that keep the logical expression
    */
    void printLines(string query);

    // Prints foreach the bookcontent pos + bookContent string
    // From [start - 1] to [end - 1]
    /** @brief Print the lines from [start - 1] to [end - 1]
        \pre An implicit Book, and the range
        \post Prints the lines of the range and its number of the implicit book
    */
    void printSelectLines(int start, int end);

    // Prints the frequency table
    /** @brief Prints a table with the frequencies' words
        \pre An implicit Book
        \post Prints all words of the content ordered decreasingly by frequencies
    */
    void printFrequencyTable();

};

#endif //PRO2_PRAC_BOOK_HH