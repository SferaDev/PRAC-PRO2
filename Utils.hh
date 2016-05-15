/**
  @file Utils.hh
  TODO :: @brief Data model for generic functions.
*/


#ifndef PRO2_PRAC_UTILS_HH
#define PRO2_PRAC_UTILS_HH

#ifndef NO_DIAGRAM
#include <string>
#include <sstream>
#endif
using namespace std;

/**
    TODO @namespace utils
    TODO: @brief Data model for generic functions.
*/

namespace utils {

    /** @brief Finds if a sentence contains a word
        \param input: The sentence
        \param query: The word to find in the sentence
        \pre The sentence and the word to find in the sentence
        \post Returns true if the word is on the sentence
    */
    bool contains(string input, string query);

    /** @brief Converts lowercase to uppercase
        \param input: The sentence that can have some letters are in lowercase
        \pre The sentence that can have some letters in lowercase
        \post The sentence with all letters in uppercase
    */
    void stringUppercase(string& input);

    /** @brief Finds if a sentence are equal to another sentence
        \param a: A sentence
        \param b: A sentence
        \pre Doesn't know if the sentence a and the sentence b are equals
        \post Returns true if the two sentences are the same sentence
    */
    bool startsWith(string a, string b);

    /** @brief Finds if a sentence ends with another sentence
        \param a: A sentence
        \param b: A sentence
        \pre Doesn't know if the sentence a ends with the sentence b
        \post Returns true if the sentence a ends with the sentence b
    */
    bool endsWith(string a, string b);

    /** @brief Finds if a sentence is between parenthesis
       \param a: A sentence that is an operand
       \param position: The position where is the sentence
       \pre Doesn't know if the sentence is between parenthesis
       \post Returns true if the sentence is between parenthesis
   */
    bool betweenPar(string query, int position);


    /** @brief Removes spaces in the sentence
       \param query: A sentence or word with spaces
       \pre The sentences with spaces
       \post The sentences without spaces
   */
    void trimString(string& query);

    /** @brief Removes spaces and quotation marks in the sentence
        \param query: A word with spaces and quotation marks
        \pre The sentences with spaces and quotation marks
        \post The sentences without spaces and quotation marks
    */
    void trimStringComplex(string& query);

    /** @brief Removes spaces that remains in the sentence
        \param query: A sentence with spaces and/or punctuation marks
        \pre The sentences with a lot of spaces
        \post The sentences without spaces that remains in the sentence
    */
    void formatString(string& query);
}

#endif //PRO2_PRAC_UTILS_HH
