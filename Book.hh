/**
  @file Book.hh
  @brief Data model that hosts information about a Book
*/

#ifndef PRO2_PRAC_BOOK_HH
#define PRO2_PRAC_BOOK_HH

#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
using namespace std;

class Book {

private:
    // Name of the author (ID on parent authorCollection)
    string authorName;

    // Name of the book (ID of current element)
    string bookTitle;

    // Content of the book
    // Position is the line ID and value is the content
    vector<string> bookContent;

    // Content dictionary with frequencies
    // On the main map the key is the length of the word
    // On the inner map it has a word (without marks) and its frequencies
    map<int, map<string, int> > bookDictionary;

    // Size of Book's collection
    int bookLines;
    int bookWords;

    // Ordered collection of quotes
    // The value of the item is the ID of the parent quoteCollection
    set<string> bookQuotes;

public:
    // Constructor
    Book();
    Book(string title, string author);

    // Destructor
    ~Book();

    // Read bookContent
    void readBookContent();

    // Returns bookName
    string getBookTitle() const;

    // Returns authorName
    string getAuthorName();

    // Returns bookLines
    int getBookLines();

    // Returns bookWords
    int getBookWords();

    // Replace contents on currentBook
    void replaceWords(string oldWord, string newWord);

    // Calls printSelectLines from 1 to bookContent.size()
    void printAllLines();

    // Print lines by logical expression match
    // RECURSIVE
    void printLines(string query);

    // Prints foreach the bookcontent pos + bookContent string
    // From [start - 1] to [end - 1]
    void printSelectLines(int start, int end);

    // Prints the frequency table
    void printFrequencyTable();

};

#endif //PRO2_PRAC_BOOK_HH