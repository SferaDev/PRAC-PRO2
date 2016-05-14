#ifndef PRO2_PRAC_UTILS_HH
#define PRO2_PRAC_UTILS_HH

#ifndef NO_DIAGRAM
#include <string>
#include <sstream>
#endif
using namespace std;

namespace utils {
    bool contains(string input, string query);

    void stringUppercase(string& input);

    bool startsWith(string a, string b);

    bool endsWith(string a, string b);

    bool betweenPar(string query, int position);

    void trimString(string& query);

    void trimStringComplex(string& query);

    void formatString(string& query);
}

#endif //PRO2_PRAC_UTILS_HH
