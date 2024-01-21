#include "account.hh"
#include <iostream>

Account::Account(const std::string& owner, bool has_credit): owner_(owner), has_credit_(has_credit)
{
    balance_ = 0;
    generate_iban();
}

// Setting initial value for the static attribute running_number_
int Account::running_number_ = 0;

void Account::generate_iban()
{
    ++running_number_;
    std::string suffix = "";
    if(running_number_ < 10)
    {
        suffix.append("0");
    }
    else if(running_number_ > 99)
    {
        std::cout << "Too many accounts" << std::endl;
    }
    suffix.append(std::to_string(running_number_));

    iban_ = "FI00 1234 ";
    iban_.append(suffix);
}

void Account::print() const
{
    std::cout << owner_ << " : " << iban_ << " : " << balance_ << " euros" << std::endl;
}

void Account::set_credit_limit(int limit)
{
    if(has_credit_ == true) 
    {
        credit_limit_ = limit;
    } else 
    {
        std::cout << "Cannot set credit limit: the account has no credit card" << std::endl;
    }
}

void Account::save_money(int amount)
{
    balance_ += amount;
}

void Account::take_money(int amount)
{
    if(!has_credit_)
    {
        if(balance_ >= amount)
        {
            balance_ -= amount;
            std::cout << amount << " euros taken: new balance of " << iban_ << " is " << balance_ << " euros" << std::endl;

        } else 
        {
            std::cout << "Cannot take money: balance underflow" << std::endl;
        }
    } else 
    {
        if(balance_ >= 0)
        {
            balance_ -= amount;
            std::cout << amount << " euros taken: new balance of " << iban_ << " is " << balance_ << " euros" << std::endl;
        } else 
        {
            std::cout << "Cannot take money: credit limit overflow" << std::endl;
        }
    }
}

void Account::transfer_to(Account& account, int amount)
{
    if(!has_credit_)
    {
        if(balance_ >= amount)
        {
            balance_ -= amount;
            account.balance_ += amount;
            std::cout << amount << " euros taken: new balance of " << iban_ << " is " << balance_ << " euros" << std::endl;
        } else 
        {
            std::cout << "Cannot take money: balance underflow" << std::endl;
            std::cout << "Transfer from " << iban_ << " failed" << std::endl;
        }
    } else 
    {
        if(balance_ >= 0)
        {
            balance_ -= amount;
            account.balance_ += amount;
            std::cout << amount << " euros taken: new balance of " << iban_ << " is " << balance_ << " euros" << std::endl;
        } else 
        {
            std::cout << "Cannot take money: credit limit overflow" << std::endl;
            std::cout << "Transfer from " << iban_ << " failed" << std::endl;
        }
    }
}
