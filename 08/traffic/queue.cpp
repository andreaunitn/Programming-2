#include "queue.hh"
#include <iostream>

using namespace std;

Queue::Queue(unsigned int cycle): cycle_(cycle) {}

Queue::~Queue()
{
    while(first_ != nullptr)
    {
        Vehicle* item_to_deallocate = first_;
        first_ = first_->next;

        delete item_to_deallocate;
    }
}

void Queue::enqueue(string const& reg) {
    if (is_green_) {
        cout << "GREEN: The vehicle " << reg << " need not stop to wait" << endl;
        return;
    }
    Vehicle* new_vehicle = new Vehicle{reg, nullptr};
    if (!first_) {
        first_ = last_ = new_vehicle;
    } else {
        last_->next = new_vehicle;
        last_ = new_vehicle;
    }
}

void Queue::switch_light() {
    if (is_green_) {
        cout << "RED: ";
        if (!first_) {
            cout << "No vehicles waiting in traffic lights" << endl;
        } else {
            cout << "Vehicle(s) ";
            Vehicle* current = first_;
            while (current) {
                cout << current->reg_num << " ";
                current = current->next;
            }
            cout << "waiting in traffic lights" << endl;
        }
        is_green_ = false;
    } else {
        is_green_ = true;
        if (!first_) {
            cout << "GREEN: No vehicles waiting in traffic lights" << endl;
        } else {
            cout << "GREEN: Vehicle(s) ";
            for (unsigned int i = 0; i < cycle_ && first_; ++i) {
                cout << first_->reg_num << " ";
                Vehicle* temp = first_;
                first_ = first_->next;
                delete temp;
            }
            cout << "can go on" << endl;
            is_green_ = false;
        }
    }
}

void Queue::reset_cycle(unsigned int cycle) {
    cycle_ = cycle;
}

void Queue::print() const {
    cout << (is_green_ ? "GREEN: " : "RED: ");

    if (!first_) {
        cout << "No vehicles waiting in traffic lights" << endl;
        return;
    }

    cout << "Vehicle(s) ";
    Vehicle* current = first_;
    while (current) {
        cout << current->reg_num << " ";
        current = current->next;
    }
    cout << "waiting in traffic lights" << endl;
}
