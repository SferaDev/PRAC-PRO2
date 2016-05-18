/**
  @file Utils.hh
  @brief Host for the utils namespace declaration
*/

#ifndef PRO2_PRAC_UTILS_HH
#define PRO2_PRAC_UTILS_HH

#ifndef NO_DIAGRAM
#include <string>
#include <sstream>
#endif
using namespace std;

/**
    @brief Utility namespace for generic functions.
*/
namespace utils {

    /** @brief Returns if a sentence contains a word
        \param input: The sentence (can contain one delimiter per word)
        \param query: The word to find in the sentence (without any delimiter)
        \pre The sentence and the word to find
        \post Returns true if the single word is on the sentence
    */
    bool contains(string input, string query);

    /** @brief Converts a string from lowercase to uppercase
        \param input: A string with or without lowercase chars
        \pre True
        \post The forwarded param string has all chars uppercase
    */
    void stringUppercase(string& input);

    /** @brief Returns if a sentence starts with another one
        \param a: String to analyze
        \param b: String to find on first positions of param a
        \pre True
        \post Returns true if the first b.size() chars are the same on a
    */
    bool startsWith(string a, string b);

    /** @brief Returns if a sentence ends with another one
        \param a: String to analyze
        \param b: String to find on first positions of param a
        \pre True
        \post Returns true if the last b.size() chars are the same on a
    */
    bool endsWith(string a, string b);

    /** @brief Finds if a string is between parentheses
       \param a: The string to check
       \param position: End position to check
       \pre True
       \post Returns true if the string is between a parentheses on the specified position
   */
    bool betweenPar(string query, int position);


    /** @brief Removes spaces (start/end) in the sentence
       \param query: A param string
       \pre True
       \post The referenced string doesn't have any spaces at start and/or end
   */
    void trimString(string& query);

    /** @brief Removes spaces and quotation marks in the sentence
        \param query: A param string
        \pre True
        \post The referenced string doesn't have any spaces or quotation marks at start and/or end
    */
    void trimStringComplex(string& query);

    /** @brief Formats a string following a specified criteria
        \param query: A param string
        \pre True
        \post The referenced string has all the punctuation marks correctly placed without extra spaces
    */
    void formatString(string& query);
}

#endif //PRO2_PRAC_UTILS_HH
