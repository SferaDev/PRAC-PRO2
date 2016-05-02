/**
  @file Book.cc
  @brief Class for the Book definition
*/

#include "Book.hh"
#include <algorithm>
#include <sstream>
using namespace std;

Book::Book() {
    bookWords = 0;
}

Book::Book(string title, string author) {
    bookTitle = title;
    authorName = author;
    bookWords = 0;
}

Book::~Book() {
    // no-op
}

void Book::readBookContent() {
    string input, content;
    while (getline(cin, input) && input != "****") {
        string word;
        istringstream iss(input);
        while (iss >> word) {
            if (!content.empty()) content += " ";
            content += word;
            bookWords += 1;
            if (word.find_last_of(",;:") == word.length() - 1)
                word.erase(word.length() - 1, 1);
            if (word.find_last_of(".?!") == word.length() - 1) {
                bookContent.push_back(content);
                content.clear();
                word.erase(word.length() - 1, 1);
            }
            wordDictionary[word.length()].insert(word);
            wordFrequencyMap[word] += 1;
        }
    }
}

string Book::getBookTitle() const {
    return bookTitle;
}

string Book::getAuthorName() {
    return authorName;
}

int Book::getBookLines() {
    return bookContent.size();
}

int Book::getBookWords() {
    return bookWords;
}

void Book::replaceWords(string oldWord, string newWord) {
    // Edit the contents of the book
    for (int i = 0; i < bookContent.size(); ++i) {
        int pos = bookContent[i].find(oldWord);
        if (pos != bookContent[i].npos)
            bookContent[i].replace(pos, oldWord.length(), newWord);
    }
    // Edit the dictionary
    wordDictionary[oldWord.length()].erase(oldWord);
    wordDictionary[newWord.length()].insert(newWord);
    // Edit the frequency Map
    wordFrequencyMap[newWord] = wordFrequencyMap[oldWord];
    wordFrequencyMap.erase(oldWord);
    // Update the frequency vector
    // TODO: FIXME Efficiency
    generateFrequencyTable();
}

bool Book::findWord(string word) {
    return wordDictionary[word.length()].find(word) != wordDictionary[word.length()].end();
}

void Book::generateFrequencyTable() {
    // Check if vector was previously generated
    if (wordFrequencyVector.size() > 0) wordFrequencyVector.clear();
    for (map<string, int>::iterator it = wordFrequencyMap.begin();
         it != wordFrequencyMap.end(); ++it) {
        wordFrequencyVector.push_back(make_pair(it->first, it->second));
    }
    sort(wordFrequencyVector.begin(), wordFrequencyVector.end(), frequencyComparator());
}

set<string> Book::getBookQuotes() {
    return bookQuotes;
}

vector<string> Book::getLines(int start, int end) {
    vector<string> vector(end - start + 1);
    for (int i = start; i <= end; ++i) {
        vector[i - start] = bookContent[i - 1];
    }
    return vector;
}

void Book::addQuote(string reference) {
    bookQuotes.insert(reference);
}

void Book::deleteQuote(string reference) {
    bookQuotes.erase(reference);
}

void Book::printInformation() {
    cout << authorName << " \"" <<  bookTitle << "\" " << endl;
}

void Book::printAllLines() {
    printSelectLines(1, bookContent.size());
}

void Book::printLines(string query) {
    // TODO: JORDI
    // TODO: Call the immersive recursive: bool found with items query and int[] with the lines where found
}

void Book::printWordsConsecutivesLines(string query){
    // TODO: JORDI
    // FIXME: Possible efficiency: Si las palabras no estan en el diccionario del currentBook -> error
    istringstream issQuery(query);
    string wordQuery;
    while (issQuery >> wordQuery) {
        if (!findWord(wordQuery)) {
            cout << "error" << endl;
            return;
        }
    }
    issQuery.seekg(0);
    // foreach line -> load line into iss -> Check if it's there?
    for (int i = 0; i < bookContent.size(); ++i) {
        istringstream issContent(bookContent[i]);
        string wordContent;
        issQuery >> wordQuery;
        // TODO: Add a bool to check if found
        while (issContent >> wordContent) {
            // TODO: If equals -> found = true and issQuery >> wordQuery
            // TODO: If found and not equals false positive break and move to next line!
        }
        // TODO: rewind issQuery: issQuery.seekg(0);
    }
}

void Book::printSelectLines(int start, int end) {
    for (int i = start; i <= end; ++i) {
        cout <<  i << " " << bookContent[i - 1] << endl;
    }
}

void Book::printFrequencyTable() {
    for (int i = 0; i < wordFrequencyVector.size(); ++i) {
        cout << wordFrequencyVector[i].first << " " << wordFrequencyVector[i].second << endl;
    }
}