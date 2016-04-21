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

void readActions(Library& library) {
    string input;
    while (getline(cin, input)) {
        if (input.substr(0, BOOK_INSERT.length()) == BOOK_INSERT) {
            string title, author;
            title = input.erase(input.length() - 1, 1).substr(input.find_first_of("\"") + 1);
            getline(cin, input);
            author = input.erase(input.length() - 1, 1).substr(input.find_first_of("\"") + 1);
            library.readBook(title, author);
        } else if (input.substr(0, BOOK_DELETE.length()) == BOOK_DELETE) {
            library.deleteBook();
        } else if (input.substr(0, BOOK_SELECT.length()) == BOOK_SELECT) {
            library.selectBook(input.erase(input.length() - 1, 1).substr(input.find_first_of("{") + 1));
        } else if (input.substr(0, BOOK_REPLACE_WORD.length()) == BOOK_REPLACE_WORD) {
            string oldWord, newWord;
            // TODO: Substring from input
            library.getBook().replaceWords(oldWord, newWord);
        } else if (input.substr(0, QUOTE_INSERT.length()) == QUOTE_INSERT) {
            // TODO
        } else if (input.substr(0, QUOTE_DELETE.length()) == QUOTE_DELETE) {
            string reference;
            // TODO: Substring refernce from input
            library.deleteQuote(reference);
        } else if (input.substr(0, QUERY_AUTHORS.length()) == QUERY_AUTHORS) {
            // TODO
        } else if (input.substr(0, QUERY_BOOKS_ALL.length()) == QUERY_BOOKS_ALL) {
            // TODO
        } else if (input.substr(0, QUERY_BOOKS_BY_AUTHOR.length()) == QUERY_BOOKS_BY_AUTHOR) {
            // TODO
        } else if (input.substr(0, QUERY_CURRENT_AUTHOR.length()) == QUERY_CURRENT_AUTHOR) {
            // TODO
        } else if (input.substr(0, QUERY_CURRENT_CONTENT.length()) == QUERY_CURRENT_CONTENT) {
            // TODO
        } else if (input.substr(0, QUERY_CURRENT_INFO.length()) == QUERY_CURRENT_INFO) {
            // TODO
        } else if (input.substr(0, QUERY_CURRENT_EXPRESION.length()) == QUERY_CURRENT_EXPRESION) {
            // TODO
        } else if (input.substr(0, QUERY_CURRENT_LINES.length()) == QUERY_CURRENT_LINES) {
            // TODO
        } else if (input.substr(0, QUERY_CURRENT_WORDS.length()) == QUERY_CURRENT_WORDS) {
            // TODO
        } else if (input.substr(0, QUERY_CURRENT_FREQUENCY.length()) == QUERY_CURRENT_FREQUENCY) {
            // TODO
        } else if (input.substr(0, QUERY_CURRENT_QUOTES.length()) == QUERY_CURRENT_QUOTES) {
            // TODO
        } else if (input.substr(0, QUERY_QUOTES_ALL.length()) == QUERY_QUOTES_ALL) {
            library.printQuotes();
        } else if (input.substr(0, QUERY_QUOTES_BY_AUTHOR.length()) == QUERY_QUOTES_BY_AUTHOR) {
            string author;
            // TODO: Substring author from input
            library.printQuotesByAuthor(author);
        } else if (input.substr(0, QUERY_QUOTE_INFO.length()) == QUERY_QUOTE_INFO) {
            string reference;
            // TODO: Substring reference from input
            library.getQuote(reference).printQuoteInformation();
        } else if (input.substr(0, QUIT.length()) == QUIT) {
            // TODO
        }
    }
}

/** @brief Main Procedure of main.cc */
int main() {
    Library mainLibrary;
    readActions(mainLibrary);
}