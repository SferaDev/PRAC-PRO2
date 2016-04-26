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
const string BOOK_INSERT = "afegir text";
const string BOOK_DELETE = "eliminar text";
const string BOOK_SELECT = "triar text";
const string BOOK_REPLACE_WORD = "substitueix";

const string QUOTE_INSERT = "afegir cita";
const string QUOTE_DELETE = "eliminar cita";

const string QUERY_AUTHORS = "tots autors ?";
const string QUERY_BOOKS_ALL = "tots textos ?";
const string QUERY_BOOKS_BY_AUTHOR = "textos autor";

const string QUERY_CURRENT_AUTHOR = "autor ?";
const string QUERY_CURRENT_CONTENT = "contingut ?";
const string QUERY_CURRENT_INFO = "info ?";
const string QUERY_CURRENT_EXPRESION = "frases"; // TODO: Logical or numeric!
const string QUERY_CURRENT_LINES = "nombre de frases ?";
const string QUERY_CURRENT_WORDS = "nombre de paraules ?";
const string QUERY_CURRENT_FREQUENCY = "taula de frequencies ?";
const string QUERY_CURRENT_QUOTES = "cites ?";

const string QUERY_QUOTES_ALL = "totes cites ?";
const string QUERY_QUOTES_BY_AUTHOR = "cites autor";
const string QUERY_QUOTE_INFO = "info cita";

const string QUIT = "sortir";

bool startsWith(string input, string compare) {
    return input.substr(0, compare.length()) == compare;
}

void readActions(Library& library) {
    string input;
    while (getline(cin, input)) {
        if (startsWith(input, BOOK_INSERT)) {
            string title, author;
            title = input.erase(input.length() - 1, 1).substr(input.find_first_of("\"") + 1);
            getline(cin, input);
            author = input.erase(input.length() - 1, 1).substr(input.find_first_of("\"") + 1);
            library.readBook(title, author);
        } else if (startsWith(input, BOOK_DELETE)) {
            library.deleteBook();
        } else if (startsWith(input, BOOK_SELECT)) {
            library.selectBook(input.erase(input.length() - 1, 1).substr(input.find_first_of("{") + 1));
        } else if (startsWith(input, BOOK_REPLACE_WORD)) {
            library.replaceWordsOnBook(input);
        } else if (startsWith(input, QUOTE_INSERT)) {
            // TODO
        } else if (startsWith(input, QUOTE_DELETE)) {
            string reference;
            // TODO: Substring reference from input
            library.deleteQuote(reference);
        } else if (startsWith(input, QUERY_AUTHORS)) {
            // TODO
        } else if (startsWith(input, QUERY_BOOKS_ALL)) {
            // TODO
        } else if (startsWith(input, QUERY_BOOKS_BY_AUTHOR)) {
            // TODO
        } else if (startsWith(input, QUERY_CURRENT_AUTHOR)) {
            // TODO
        } else if (startsWith(input, QUERY_CURRENT_CONTENT)) {
            if (library.isBookSelected())
                library.getBook().printAllLines();
            else cout << "error" << endl;
        } else if (startsWith(input, QUERY_CURRENT_INFO)) {
            // TODO
        } else if (startsWith(input, QUERY_CURRENT_EXPRESION)) {
            // TODO
        } else if (startsWith(input, QUERY_CURRENT_LINES)) {
            if (library.isBookSelected())
                cout << library.getBook().getBookLines() << endl;
            else cout << "error" << endl;
        } else if (startsWith(input, QUERY_CURRENT_WORDS)) {
            if (library.isBookSelected())
                cout << library.getBook().getBookWords() << endl;
            else cout << "error" << endl;
        } else if (startsWith(input, QUERY_CURRENT_FREQUENCY)) {
            if (library.isBookSelected())
                library.getBook().printFrequencyTable();
            else cout << "error" << endl;
        } else if (startsWith(input, QUERY_CURRENT_QUOTES)) {
            // TODO
        } else if (startsWith(input, QUERY_QUOTES_ALL)) {
            library.printQuotes();
        } else if (startsWith(input, QUERY_QUOTES_BY_AUTHOR)) {
            string author;
            // TODO: Substring author from input
            library.printQuotesByAuthor(author);
        } else if (startsWith(input, QUERY_QUOTE_INFO)) {
            string reference;
            // TODO: Substring reference from input
            library.getQuote(reference).printQuoteInformation();
        } else if (startsWith(input, QUIT)) {
            return;
        }
    }
}

/** @brief Main Procedure of main.cc */
int main() {
    Library mainLibrary;
    readActions(mainLibrary);
}
