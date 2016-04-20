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

void executeAction(Library& library, string input) {
    // TODO
}

/** @brief Main Procedure of main.cc */
int main() {
    Library mainLibrary;
    string inputLine;
    while (getline(cin, inputLine)) {
        executeAction(mainLibrary, inputLine);
    }
}