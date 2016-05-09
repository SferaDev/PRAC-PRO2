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

void analyzeExpression(string input, Library& library)  {
    // Delete '?' from query
    input = input.erase(input.length() - 1 , 1);
    // Erase 'frases ' from input channel
    input = input.substr(QUERY_CURRENT_EXPRESION.length() + 1);
    // If it's a digit call {frases x y ?} otherwise call the recursive
    if (isdigit(input[0])) {
        int x, y;
        istringstream iss(input);
        iss >> x >> y;
        library.getBook().printSelectLines(x,y);
    } else if (input[0] == '\"') {
        input = input.substr(0, input.length() - 1);
        input = input.erase(0, 1);
        input = input.substr(0, input.length() - 1);
        library.getBook().printWordsConsecutiveLines(input);
    } else {
        library.getBook().printLines(input);
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
            int start, end;
            input = input.substr(QUOTE_INSERT.length());
            istringstream iss(input);
            iss >> start >> end;
            library.insertQuote(start, end);
        } else if (startsWith(input, QUOTE_DELETE)) {
            string reference = input.erase(input.length() - 1, 1);
            reference = reference.substr(input.find_first_of("\"") + 1);
            library.deleteQuote(reference);
        } else if (startsWith(input, QUERY_AUTHORS)) {
            library.printAuthors();
        } else if (startsWith(input, QUERY_BOOKS_ALL)) {
            library.printBooks();
        } else if (startsWith(input, QUERY_BOOKS_BY_AUTHOR)) {
	        string authorName = input.erase(input.length() - 3, 3);
            authorName = authorName.substr(input.find_first_of("\"") + 1);
	        library.printBooksByAuthor(authorName);
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
        } else if (startsWith(input, QUERY_CURRENT_EXPRESION)) {
            if (library.isBookSelected()) {
                analyzeExpression(input, library);
            } else cout << "error" << endl;
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
        } else if (startsWith(input, QUERY_QUOTES_BY_AUTHOR)) {
            string authorName = input.erase(input.length() - 3, 3);
            authorName = authorName.substr(input.find_first_of("\"") + 1);
            library.printQuotesByAuthor(authorName);
        } else if (startsWith(input, QUERY_QUOTE_INFO)) {
            string reference = input.erase(input.length() - 3, 3);
            reference = reference.substr(input.find_first_of("\"") + 1);
            if (library.quoteExists(reference)) {
                Quote quote = library.getQuote(reference);
                cout << quote.getAuthor() << " \"" << quote.getBookTitle() << "\"" << endl;
                quote.printInformation(false, true);
            } else cout << "error" << endl;
        }
    }
}

/** @brief Main Procedure of main.cc */
int main() {
    Library mainLibrary;
    readActions(mainLibrary);
}
