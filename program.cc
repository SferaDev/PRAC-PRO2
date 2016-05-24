/**
 @mainpage Gestor de textos i cites | Alexis Rico and Jordi Romero
*/

/**
  @file main.cc
  @brief Main program that handles the I/O operations with the end user.
*/

#include "Library.hh"
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

const string ACTION_EXPRESSION = "frases";

const string QUERY_AUTHORS = "tots autors";
const string QUERY_BOOKS_ALL = "tots textos";
const string QUERY_CURRENT_AUTHOR = "autor";
const string QUERY_CURRENT_CONTENT = "contingut";
const string QUERY_CURRENT_INFO = "info";
const string QUERY_CURRENT_LINES = "nombre de frases";
const string QUERY_CURRENT_WORDS = "nombre de paraules";
const string QUERY_CURRENT_FREQUENCY = "taula de frequencies";
const string QUERY_CURRENT_QUOTES = "cites";
const string QUERY_QUOTES_ALL = "totes cites";

const string QUIT = "sortir";

void actionExpression(Library& library, string input)  {
    // Erase 'frases ' from input channel
    input = input.substr(ACTION_EXPRESSION.length() + 1);
    // Delete '?' from query
    utils::trimString(input);
    int posQuery = input.find_last_of("?");
    if (posQuery != string::npos) input.erase(posQuery, 1);
    // If it's a digit call {frases x y ?} otherwise call the recursive
    int x, y;
    istringstream iss(input);
    iss >> x >> y;
    if (!iss.fail()) library.getBook().printSelectLines(x,y);
    else if (input[0] == '\"' and input[input.length() - 1]) {
        utils::trimStringComplex(input);
        library.getBook().printLinesConsecutiveWords(input);
    } else if (input.find_first_of("({})&|") != string::npos){
        library.getBook().printLines(input);
    } //else utils::printError();
}

void readActions(Library& library) {
    string input;
    bool lastOutputSpace = true;
    while (getline(cin, input)) {
        string original = input;
        if (!lastOutputSpace) cout << endl;
        // Remove spaces from input
        utils::trimString(input);
        lastOutputSpace = input.empty();
        // Quit command returns void
        if (utils::startsWithEquals(input, QUIT)) {
            return;
        } else if (!input.empty()) cout << original << endl;
        // Handle the rest of commands
        if (utils::startsWith(input, BOOK_INSERT)) {
            string title, author;
            title = original.erase(original.length() - 1, 1).substr(BOOK_INSERT.length());
            getline(cin, input);
            if (utils::startsWith(input, BOOK_INSERT_AUTHOR)) {
                author = input.erase(input.length() - 1, 1).substr(BOOK_INSERT_AUTHOR.length());
                library.readBook(title, author);
            } else {
                while (input != "****") getline(cin, input);
            }
        } else if (utils::startsWithEquals(input, BOOK_DELETE)) {
            library.deleteBook();
        } else if (utils::startsWithEquals(input, BOOK_SELECT)) {
            string query = input.erase(input.length() - 1, 1);
            query = input.substr(input.find_first_of("{") + 1);
            library.selectBook(query);
        } else if (utils::startsWithEquals(input, BOOK_REPLACE_WORD)) {
            istringstream iss(input);
            string oldWord, newWord;
            iss >> oldWord >> oldWord >> newWord >> newWord;
            if (oldWord[0] == '\"' and newWord[0] == '\"' and
                    oldWord[oldWord.length() - 1] == '\"' and newWord[newWord.length() - 1] == '\"') {
                utils::trimStringComplex(oldWord);
                utils::trimStringComplex(newWord);
                library.replaceWordsOnBook(oldWord, newWord);
            }
        } else if (utils::startsWith(input, QUOTE_INSERT)) {
            int start, end;
            input = input.substr(QUOTE_INSERT.length());
            istringstream iss(input);
            iss >> start >> end;
            if (!iss.fail()) library.insertQuote(start, end);
            else utils::printError();
        } else if (utils::startsWith(input, QUOTE_DELETE)) {
            string reference = input.erase(input.length() - 1, 1);
            reference = reference.substr(input.find_first_of("\"") + 1);
            library.deleteQuote(reference);
        } else if (utils::startsWithEquals(input, ACTION_EXPRESSION)) {
            if (library.isBookSelected()) {
                actionExpression(library, input);
            } else utils::printError();
        } else if (utils::startsWithEquals(input, QUOTE_INFO)) {
            string reference = input.substr(QUOTE_INFO.length());
            reference.erase(reference.length() - 1, 1);
            utils::trimStringComplex(reference);
            if (!reference.empty() and library.quoteExists(reference)) {
                Quote quote = library.getQuote(reference);
                cout << quote.getAuthor() << " \"" << quote.getBookTitle() << "\"" << endl;
                quote.printInformation(false, true);
            } else utils::printError();
        } else if (utils::startsWithEquals(input, AUTHOR_QUOTES)) {
            string reference = input.substr(AUTHOR_QUOTES.length());
            reference.erase(reference.length() - 1, 1);
            utils::trimStringComplex(reference);
            if (!reference.empty()) library.printQuotesByAuthor(reference);
        } else if (utils::startsWithEquals(input, AUTHOR_BOOKS)) {
            string reference = input.substr(AUTHOR_BOOKS.length());
            reference.erase(reference.length() - 1, 1);
            utils::trimStringComplex(reference);
            if (!reference.empty()) library.printBooksByAuthor(reference);
        } else if (utils::startsWith(input, QUERY_AUTHORS)) {
            library.printAuthors();
        } else if (utils::startsWithEquals(input, QUERY_BOOKS_ALL)) {
            library.printBooks();
        } else if (utils::startsWithEquals(input, QUERY_CURRENT_AUTHOR)) {
            if (library.isBookSelected())
                cout << library.getBook().getAuthor() << endl;
            else utils::printError();
        } else if (utils::startsWithEquals(input, QUERY_CURRENT_CONTENT)) {
            if (library.isBookSelected())
                library.getBook().printAllLines();
            else utils::printError();
        } else if (utils::startsWithEquals(input, QUERY_CURRENT_INFO)) {
            if (library.isBookSelected())
                library.printCurrentInformation();
            else utils::printError();
        } else if (utils::startsWithEquals(input, QUERY_CURRENT_LINES)) {
            if (library.isBookSelected())
                cout << library.getBook().getLineCount() << endl;
            else utils::printError();
        } else if (utils::startsWithEquals(input, QUERY_CURRENT_WORDS)) {
            if (library.isBookSelected())
                cout << library.getBook().getWordCount() << endl;
            else utils::printError();
        } else if (utils::startsWithEquals(input, QUERY_CURRENT_FREQUENCY)) {
            if (library.isBookSelected())
                library.getBook().printFrequencyTable();
            else utils::printError();
        } else if (utils::startsWithEquals(input, QUERY_CURRENT_QUOTES)) {
            if (library.isBookSelected())
                library.printCurrentQuotes();
            else utils::printError();
        } else if (utils::startsWithEquals(input, QUERY_QUOTES_ALL)) {
            library.printQuotes();
        }
    }
}

/** @brief Main Procedure of main.cc */
int main() {
    Library mainLibrary;
    readActions(mainLibrary);
}
