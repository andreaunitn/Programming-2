#ifndef BOOK_HH
#define BOOK_HH

#include "date.hh"
#include <string>

class Book
{
public:
    Book(const std::string& author, const std::string& title);

    void print() const;
    void loan(Date date);
    void renew();
    void give_back();

private:
    std::string author_;
    std::string title_;
    bool is_loaned_;
    bool is_returned_;
    Date loan_date_;
    Date return_date_;
};

#endif
