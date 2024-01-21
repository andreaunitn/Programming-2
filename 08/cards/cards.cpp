#include "cards.hh"
#include <iostream>

using namespace std;

Cards::Cards(): top_(nullptr), last_(nullptr) {}

Cards::~Cards() {
    while(top_ != nullptr)
    {
        Card_data* item_to_deallocate = top_;
        top_ = top_->next;

        delete item_to_deallocate;
    }
}

Card_data* Cards::get_topmost()
{
    return top_;
}

bool Cards::is_empty()
{
    if(top_ == nullptr && last_ == nullptr)
    {
        return true;
    }

    return false;
}

void Cards::add(int id)
{
    Card_data* new_item = new Card_data{id, nullptr};

    if(is_empty())
    {
        top_ = new_item;
        last_ = new_item;
    } else 
    {
        Card_data* old_top = top_;
        top_ = new_item;
        new_item->next = old_top;
    }
}

void Cards::print_from_top_to_bottom(std::ostream& s)
{
    if(!is_empty())
    {
        Card_data* item_to_be_printed = top_;
        int elem_number = 1;

        while(item_to_be_printed != nullptr)
        {
            s << elem_number << ": " << item_to_be_printed->data << endl;
            elem_number++;
            item_to_be_printed = item_to_be_printed->next;
        }
    }
}

bool Cards::remove(int& id)
{
    if (is_empty()) {
        return false;
    }

    id = top_->data;

    Card_data* temp = top_;
    top_ = top_->next;

    if (!top_) {
        last_ = nullptr;
    }

    delete temp;
    return true;
}

bool Cards::bottom_to_top()
{
    if(is_empty())
    {
        return false;
    }

    if(top_ == last_)
    {
        return true;
    }

    Card_data* prev_to_last = top_;
    while(prev_to_last->next != last_)
    {
        prev_to_last = prev_to_last->next;
    }

    prev_to_last->next = nullptr;

    last_->next = top_;
    top_ = last_;
    last_ = prev_to_last;

    return true;
}

bool Cards::top_to_bottom()
{
    if(is_empty())
    {
        return false;
    }

    if(top_ == last_)
    {
        return true;
    }

    Card_data* item_to_move = top_;
    top_ = top_->next;
    last_->next = item_to_move;
    item_to_move->next = nullptr;
    last_ = item_to_move;

    return true;
}

void Cards::print_from_bottom_to_top(std::ostream& s)
{
    recursive_print(top_, s);
}

int Cards::recursive_print(Card_data* top, std::ostream& s) {
    if (!top) {
        return 0;
    }

    int ordinal = recursive_print(top->next, s) + 1;
    s << ordinal << ": " << top->data << std::endl;
    return ordinal;
}
