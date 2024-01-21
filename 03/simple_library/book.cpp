#include "date.hh"
#include "book.hh"
#include <iostream>

Book::Book(const std::string& author, const std::string& title): author_(author), title_(title)
{
    is_loaned_ = false;
    is_returned_ = true;
    loan_date_ = Date();
    return_date_ = Date();
}

void Book::print() const
{
    std::cout << author_ << " : " << title_ << std::endl;

    if(!is_loaned_)
    {
        std::cout << "- available" << std::endl;
    } else
    {
        std::cout << "- loaned: ";
        loan_date_.print();

        std::cout << "- to be returned: ";
        return_date_.print();
    }
}

void Book::loan(Date date)
{
    if(is_loaned_) {
        std::cout << "Already loaned: cannot be loaned" << std::endl;
    } else 
    {
        loan_date_ = date;
        date.advance(28);
        return_date_ = date;

        is_loaned_ = true;
    }
}

void Book::renew()
{
    if(is_loaned_ && is_returned_)
    {
        return_date_.advance(28);
    } else 
    {
        std::cout << "Not loaned: cannot be renewed" << std::endl;
    }
}

void Book::give_back()
{
    is_loaned_ = false;
    is_returned_ = true;
}