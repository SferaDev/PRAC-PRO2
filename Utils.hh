/**
  @file Utils.hh
  @brief Host for the utils namespace declaration
*/

#ifndef PRO2_PRAC_UTILS_HH
#define PRO2_PRAC_UTILS_HH

#ifndef NO_DIAGRAM
#include <iostream>
#include <string>
#include <sstream>
#endif
using namespace std;

/**
    @brief Utility namespace for generic functions.
*/
namespace utils {
    struct stringNaturalComparator {
        bool operator() (const string& a, const string& b) {
            int posA = a.find_first_of("0123456789");
            int posB = b.find_first_of("0123456789");
            if (a.substr(0, posA) != b.substr(0, posB)) {
                return a.substr(0, posA) < b.substr(0, posB);
            } else if (posA != string::npos and posB != string::npos) {
                int valA, valB;
                istringstream issA(a.substr(posA));
                istringstream issB(b.substr(posB));
                issA >> valA;
                issB >> valB;
                return valA < valB;
            } else {
                return a < b;
            }
        }
    };

    struct frequencyComparator {
        bool operator() (const pair<string, int>& a, const pair<string, int>& b) {
            // Special case: Same frequency
            if (a.second == b.second) {
                // Special case: Same length
                if (a.first.length() == b.first.length()) {
                    return a.first < b.first;
                }
                // Base case: Order by length in asc order
                return a.first.length() < b.first.length();
            }
            // Base case: Order by frequency in desc order
            return a.second > b.second;
        }
    };

    /** @brief Returns if a sentence contains a word
        \param input: The sentence (can contain one delimiter per word)
        \param query: The word to find in the sentence (without any delimiter)
        \pre The sentence and the word to find
        \post Returns true if the single word is on the sentence
    */
    bool contains(string input, string query);

    /** @brief Returns if a sentence contains a consecutive sequence of words
        \param input: The sentence (can contain one delimiter per word)
        \param query: The word to find in the sentence (without any delimiter)
        \pre The sentence and the word to find
        \post Returns true if the single word is on the sentence
    */
    bool containsConsecutive(string a, string b);

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

    /** @brief Returns if a sentence starts and equals the start of another one
        \param a: String to analyze
        \param b: String to find on first positions of param a
        \pre True
        \post Returns true if the first b.size() chars are the same on a
    */
    bool startsWithEquals(string a, string b);

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

    void formatString(string& query);

        /** @brief Prints an error using the correct formatting */
    void printError();
}

#endif //PRO2_PRAC_UTILS_HH
