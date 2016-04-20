#ifndef PRO2_PRAC_AUTHOR_HH
#define PRO2_PRAC_AUTHOR_HH

class Author {

private:
    // Name of the author
    string authorName;

    // Size of Author's collection
    int totalBooks;
    int totalLines;
    int totalWords;

    // Ordered collection of books
    // The value of the item is the ID of the parent bookCollection
    set<string> books;

public:
    // Constructor
    Author();

    // Destructor
    ~Author();


};

#endif //PRO2_PRAC_AUTHOR_HH