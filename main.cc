/**
 @mainpage Gestor de textos i cites | Alexis Rico and Jordi Romero
*/

/**
  @file main.cc
  @brief Main program that handles the I/O operations with the end user.
*/

#include "Library.hh"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

/* Constants */
const string BOOK_INSERT = "afegir text \"";
const string BOOK_INSERT_AUTHOR = "autor \"";
const string BOOK_DELETE = "eliminar text";
const string BOOK_SELECT = "triar text";
const string BOOK_REPLACE_WORD = "substitueix";

const string QUOTE_INSERT = "afegir cita";
const string QUOTE_DELETE = "eliminar cita";
const string QUOTE_INFO = "info cita";

const string AUTHOR_BOOKS = "textos autor";
const string AUTHOR_QUOTES = "cites autor";

const string ACTION_QUERY = "?";
const string ACTION_EXPRESSION = "frases";

const string QUERY_AUTHORS = "tots autors ?";
const string QUERY_BOOKS_ALL = "tots textos ?";
const string QUERY_CURRENT_AUTHOR = "autor ?";
const string QUERY_CURRENT_CONTENT = "contingut ?";
const string QUERY_CURRENT_INFO = "info ?";
const string QUERY_CURRENT_LINES = "nombre de frases ?";
const string QUERY_CURRENT_WORDS = "nombre de paraules ?";
const string QUERY_CURRENT_FREQUENCY = "taula de frequencies ?";
const string QUERY_CURRENT_QUOTES = "cites ?";
const string QUERY_QUOTES_ALL = "totes cites ?";

const string QUIT = "sortir";

bool startsWith(string a, string b) {
    if (b.size() > a.size()) return false;
    return std::equal(a.begin(), a.begin() + b.size(), b.begin());
}

bool endsWith(string a, string b) {
    if (b.size() > a.size()) return false;
    return std::equal(a.begin() + a.size() - b.size(), a.end(), b.begin());
}

// TODO: We need a Utils class
void trimStringComplex(string& query) {
    while (query[0] == ' ' or query[0] == '\"') query.erase(0, 1);
    while (query[query.length() - 1] == ' '  or query[query.length() - 1] == '\"')
        query.erase(query.length() - 1, 1);
}

void actionExpression(Library& library, string input)  {
    // Delete '?' from query
    trimStringComplex(input);
    if (input[input.size() - 1] != '?') return;
    input = input.erase(input.length() - 1 , 1);
    // Erase 'frases ' from input channel
    input = input.substr(ACTION_EXPRESSION.length() + 1);
    // If it's a digit call {frases x y ?} otherwise call the recursive
    int x, y;
    istringstream iss(input);
    iss >> x >> y;
    if (!iss.fail()) library.getBook().printSelectLines(x,y);
    else if (input[0] == '\"' and input[input.length() - 1]) {
        trimStringComplex(input);
        library.getBook().printLinesConsecutiveWords(input);
    } else {
        library.getBook().printLines(input);
    }
}

void actionQuery(Library& library, string input) {
    if (startsWith(input, QUERY_AUTHORS)) {
        library.printAuthors();
    } else if (startsWith(input, QUERY_BOOKS_ALL)) {
        library.printBooks();
    } else if (startsWith(input, QUERY_CURRENT_AUTHOR)) {
        if (library.isBookSelected())
            cout << library.getBook().getAuthor() << endl;
        else cout << "error" << endl;
    } else if (startsWith(input, QUERY_CURRENT_CONTENT)) {
        if (library.isBookSelected())
            library.getBook().printAllLines();
        else cout << "error" << endl;
    } else if (startsWith(input, QUERY_CURRENT_INFO)) {
        if (library.isBookSelected())
            library.printCurrentInformation();
        else cout << "error" << endl;
    } else if (startsWith(input, QUERY_CURRENT_LINES)) {
        if (library.isBookSelected())
            cout << library.getBook().getLineCount() << endl;
        else cout << "error" << endl;
    } else if (startsWith(input, QUERY_CURRENT_WORDS)) {
        if (library.isBookSelected())
            cout << library.getBook().getWordCount() << endl;
        else cout << "error" << endl;
    } else if (startsWith(input, QUERY_CURRENT_FREQUENCY)) {
        if (library.isBookSelected())
            library.getBook().printFrequencyTable();
        else cout << "error" << endl;
    } else if (startsWith(input, QUERY_CURRENT_QUOTES)) {
        if (library.isBookSelected())
            library.printCurrentQuotes();
        else cout << "error" << endl;
    } else if (startsWith(input, QUERY_QUOTES_ALL)) {
        library.printQuotes();
    }
}

void readActions(Library& library) {
    string input;
    while (getline(cin, input)) {
        // Quit command returns void
        if (startsWith(input, QUIT)) {
            return;
        } else cout << input << endl;
        // Handle the rest of commands
        if (startsWith(input, BOOK_INSERT)) {
            string title, author;
            title = input.erase(input.length() - 1, 1).substr(BOOK_INSERT.length());
            getline(cin, input);
            if (startsWith(input, BOOK_INSERT_AUTHOR)) {
                string author;
                author = input.erase(input.length() - 1, 1).substr(BOOK_INSERT_AUTHOR.length());
                library.readBook(title, author);
            }
        } else if (startsWith(input, BOOK_DELETE)) {
            library.deleteBook();
        } else if (startsWith(input, BOOK_SELECT)) {
            string query = input.erase(input.length() - 1, 1);
            query = input.substr(input.find_first_of("{") + 1);
            library.selectBook(query);
        } else if (startsWith(input, BOOK_REPLACE_WORD)) {
            istringstream iss(input);
            string oldWord, newWord;
            iss >> oldWord >> oldWord >> newWord >> newWord;
            if (oldWord[0] == '\"' and newWord[0] == '\"' and
                    oldWord[oldWord.length() - 1] == '\"' and newWord[newWord.length() - 1] == '\"') {
                trimStringComplex(oldWord);
                trimStringComplex(newWord);
                library.replaceWordsOnBook(oldWord, newWord);
            }
        } else if (startsWith(input, QUOTE_INSERT)) {
            int start, end;
            input = input.substr(QUOTE_INSERT.length());
            istringstream iss(input);
            iss >> start >> end;
            if (!iss.fail()) library.insertQuote(start, end);
        } else if (startsWith(input, QUOTE_DELETE)) {
            string reference = input.erase(input.length() - 1, 1);
            reference = reference.substr(input.find_first_of("\"") + 1);
            library.deleteQuote(reference);
        } else if (startsWith(input, AUTHOR_BOOKS)) {
            string authorName = input.erase(input.length() - 3, 3);
            authorName = authorName.substr(input.find_first_of("\"") + 1);
            library.printBooksByAuthor(authorName);
        } else if (startsWith(input, AUTHOR_QUOTES)) {
            string authorName = input.erase(input.length() - 3, 3);
            authorName = authorName.substr(input.find_first_of("\"") + 1);
            library.printQuotesByAuthor(authorName);
        } else if (startsWith(input, QUOTE_INFO)) {
            string reference = input.erase(input.length() - 3, 3);
            reference = reference.substr(input.find_first_of("\"") + 1);
            if (library.quoteExists(reference)) {
                Quote quote = library.getQuote(reference);
                cout << quote.getAuthor() << " \"" << quote.getBookTitle() << "\"" << endl;
                quote.printInformation(false, true);
            } else cout << "error" << endl;
        } else if (startsWith(input, ACTION_EXPRESSION)) {
            if (library.isBookSelected()) {
                actionExpression(library, input);
            } else cout << "error" << endl;
        } else if (endsWith(input, ACTION_QUERY)) {
            actionQuery(library, input);
        }
    }
}

/** @brief Main Procedure of main.cc */
int main() {
    Library mainLibrary;
    readActions(mainLibrary);
}
