 /*
 * Program author
 * Name: Andrea Tomasoni
 * Student number: 151920631
 * UserID: ksanto
 * E-Mail: andrea.tomasoni@tuni.fi
 * */

#include "project.hh"
#include <iostream>

Project::Project(const std::string& id, const std::string& start):
    id_(id), start_(start), is_active_(true)
{
}

Project::Project(const std::string& id, const Date &start):
    id_(id), start_(start), is_active_(true)
{
}

Project::~Project() {}

void Project::close(Date& close_date)
{
    end_ = close_date;
    is_active_ = false;
}

void Project::print_date() const
{
    if(end_.is_default())
    {
        std::cout << id_ << " : ";
        start_.print();
        std::cout << " - " << std::endl;
    } else
    {
        std::cout << id_ << " : ";
        start_.print();
        std::cout << " - ";
        end_.print();
        std::cout << std::endl;
    }
}

bool Project::is_active() const
{
    return is_active_;
}

bool Project::is_employee_assignable(const Employee* employee) const
{
    return !is_employee_in_project(employee->get_id()) && has_employee_required_skills(employee);
}

void Project::assign(const std::string& employee_id, Employee* employee)
{
    employees_.insert({employee_id, employee});
}

void Project::add_requirement(const std::string& req)
{
    requirements_.insert(req);

    // Checks if one/more employee/s must be removed from the project
    if(employees_.size() != 0)
    {
        std::set<std::string> employees_to_remove;
        std::map<std::string, Employee*> new_employee_set; // New set of employees after the checking process

        for(auto& employee: employees_)
        {
            if(!has_employee_required_skills(employee.second))
            {
                employees_to_remove.insert(employee.first);
            } else
            {
                new_employee_set.insert({employee.first, employee.second});
            }
        }

        // At least one employee must be removed. Updates set of employees working on the project
        if(employees_to_remove.size() != 0)
        {
            employees_.clear();
            employees_ = new_employee_set;

            std::cout << NOT_QUALIFIED;
            for(auto it = employees_to_remove.begin(); it != employees_to_remove.end(); it++)
            {
                if(std::next(it) == employees_to_remove.end())
                {
                    std::cout << *it << std::endl;
                } else
                {
                    std::cout << *it << ", ";
                }
            }
        }
    }
}

void Project::print_info() const
{
    print_date();
    print_requirements();
    print_staff();
}

bool Project::is_employee_in_project(const std::string& employee_id) const
{
    return employees_.find(employee_id) != employees_.end();
}


bool Project::has_employee_required_skills(const Employee* employee) const
{
    // No requirements needed
    if(requirements_.size() == 0)
    {
        return true;
    }

    for(auto& req: requirements_)
    {
        if(employee->has_skill(req))
        {
            return true;
        }
    }

    return false;
}

void Project::print_requirements() const
{
    std::cout << REQUIREMENT;

    if(requirements_.size() == 0)
    {
        std::cout << "None" << std::endl;
        return;
    }

    for(auto it = requirements_.begin(); it != requirements_.end(); it++)
    {
        if(std::next(it) == requirements_.end())
        {
            std::cout << *it << std::endl;
        } else
        {
            std::cout << *it << ", ";
        }
    }
}

void Project::print_staff() const
{
    std::cout << STAFF;

    if(employees_.size() == 0)
    {
        std::cout << "None" << std::endl;
        return;
    }

    // Getting names of employees in alphabetical order
    std::set<std::string> staff_names;
    for(auto& pair: employees_)
    {
        staff_names.insert(pair.first);
    }

    for(auto it = staff_names.begin(); it != staff_names.end(); it++)
    {
        if(std::next(it) == staff_names.end())
        {
            std::cout << *it << std::endl;
        } else
        {
            std::cout << *it << ", ";
        }
    }
}
