 /*
 * Program author
 * Name: Andrea Tomasoni
 * Student number: 151920631
 * UserID: ksanto
 * E-Mail: andrea.tomasoni@tuni.fi
 * */

#include "company.hh"
#include "utils.hh"
#include <iostream>
#include <set>

Company::Company() {}

Company::~Company()
{
    // Deallocate staff
    for(auto& pair: all_staff_)
    {
        delete pair.second;
        pair.second = nullptr;
    }

    all_staff_.clear();
    current_staff_.clear();
}

void Company::set_date(Params params)
{
    std::string day = params.at(0);
    std::string month = params.at(1);
    std::string year = params.at(2);
    if( not Utils::is_numeric(day, false) or
        not Utils::is_numeric(month, false) or
        not Utils::is_numeric(year, false) )
    {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    Utils::today.set(stoi(day), stoi(month), stoi(year));
    std::cout << "Date has been set to ";
    Utils::today.print();
    std::cout << std::endl;
}

void Company::advance_date(Params params)
{
    std::string amount = params.at(0);
    if( not Utils::is_numeric(amount, true) )
    {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    Utils::today.advance(stoi(amount));
    std::cout << "New date is ";
    Utils::today.print();
    std::cout << std::endl;
}

void Company::recruit(Params params)
{
    std::string employee_id = params.at(0);
    std::map<std::string, Employee*>::const_iterator
            iter = current_staff_.find(employee_id);

    if( iter != current_staff_.end() )
    {
        std::cout << ALREADY_EXISTS << employee_id << std::endl;
        return;
    }

    iter = all_staff_.find(employee_id);
    if( iter != all_staff_.end() )
    {
        current_staff_.insert(*iter);
        std::cout << EMPLOYEE_RECRUITED << std::endl;
        return;
    }

    Employee* new_employee = new Employee(employee_id);
    all_staff_.insert({employee_id, new_employee});
    current_staff_.insert({employee_id, new_employee});
    std::cout << EMPLOYEE_RECRUITED << std::endl;
}

void Company::leave(Params params)
{
    std::string employee_id = params.at(0);
    std::map<std::string, Employee*>::const_iterator
            iter = current_staff_.find(employee_id);
    if( iter == current_staff_.end() )
    {
        std::cout << CANT_FIND << employee_id << std::endl;
        return;
    }

    current_staff_.erase(iter); // Employee still stays in all_staff_
    std::cout << EMPLOYEE_LEFT << std::endl;
}

void Company::add_skill(Params params)
{
    std::string employee_id = params.at(0);
    std::string skill_name = params.at(1);

    std::map<std::string, Employee*>::const_iterator
            staff_iter = current_staff_.find(employee_id);
    if( staff_iter == current_staff_.end() )
    {
        std::cout << CANT_FIND << employee_id << std::endl;
        return;
    }

    staff_iter->second->add_skill(skill_name);
    std::cout << SKILL_ADDED << employee_id << std::endl;
}

void Company::print_current_staff(Params)
{
    if( current_staff_.empty() )
    {
        std::cout << "None" << std::endl;
        return;
    }

    for( auto employee : current_staff_ )
    {
        employee.second->print_id("");
        std::cout << std::endl;
    }
}

void Company::create_project(Params params)
{
    std::string project_id = params.at(0);

    // Checks if project already exists
    if(is_project_in_company(project_id))
    {
        std::cout << ALREADY_EXISTS << project_id << std::endl;
        return;
    }

    // Creates a new project and add it to the company
    Project_ptr project(std::make_shared<Project>(project_id, Utils::today));
    projects_.insert({project_id, project});
    projects_list_.push_back(project);

    std::cout << PROJECT_CREATED << std::endl;
}

void Company::close_project(Params params)
{
    std::string project_id = params.at(0);

    // Checks if project exists
    if(!is_project_in_company(project_id))
    {
        std::cout << CANT_FIND << project_id << std::endl;
        return;
    }

    // Closes project
    Project_ptr project = get_project(project_id);
    project->close(Utils::today);

    std::cout << PROJECT_CLOSED << std::endl;
}

void Company::print_projects(Params)
{
    // No projects inside the company
    if(projects_.size() == 0)
    {
        std::cout << "None" << std::endl;
        return;
    }

    for(auto project: projects_list_)
    {
        project->print_date();
    }
}

void Company::add_requirement(Params params)
{
    std::string project_id = params.at(0);
    std::string requirement = params.at(1);

    if(!is_project_in_company(project_id))
    {
        std::cout << CANT_FIND << project_id << std::endl;
        return;
    }

    Project_ptr project = get_project(project_id);

    if(!project->is_active())
    {
        std::cout << CANT_FIND << project_id << std::endl;
        return;
    }

    project->add_requirement(requirement);

    std::cout << REQUIREMENT_ADDED << project_id << std::endl;
}

void Company::assign(Params params)
{
    std::string employee_id = params.at(0);
    std::string project_id = params.at(1);

    if(!is_employee_in_company(employee_id))
    {
        std::cout << CANT_FIND << employee_id << std::endl;
        return;
    }

    if(!is_project_in_company(project_id))
    {
        std::cout << CANT_FIND << project_id << std::endl;
        return;
    }

    Project_ptr project = get_project(project_id);
    Employee* employee = get_employee(employee_id);

    // Checks basic eligible criteria
    if(!project->is_active() || !project->is_employee_assignable(employee))
    {
        std::cout << CANT_ASSIGN << employee_id << std::endl;
        return;
    }

    project->assign(employee_id, employee);
    save_employee_project_info(employee_id, project);

    std::cout << STAFF_ASSIGNED << project_id << std::endl;
}

void Company::print_project_info(Params params)
{
    std::string project_id = params.at(0);

    if(!is_project_in_company(project_id))
    {
        std::cout << CANT_FIND << project_id << std::endl;
        return;
    }

    Project_ptr project = get_project(project_id);
    project->print_info();
}

void Company::print_employee_info(Params params)
{
    std::string employee_id = params.at(0);

    if(!is_employee_in_company(employee_id))
    {
        std::cout << CANT_FIND << employee_id << std::endl;
        return;
    }

    Employee* employee = get_employee(employee_id);
    employee->print_skills();

    std::cout << PROJECTS;

    // No employee has been assigned to any project
    if(assigned_employee_projects_.size() == 0)
    {
        std::cout << "None" << std::endl;
        return;
    }

    for(auto& pair: assigned_employee_projects_)
    {
        if(pair.first == employee_id)
        {
            std::cout << std::endl;
            for(auto project: pair.second)
            {
                std::cout << "** ";
                project->print_date();
            }
        }
    }
}

void Company::print_active_staff(Params)
{
    if(assigned_employee_projects_.size() == 0)
    {
        std::cout << "None" << std::endl;
        return;
    }

    // Getting ordered names for the active staff
    std::set<std::string> employee_names;
    for(auto& pair: assigned_employee_projects_)
    {
        employee_names.insert(pair.first);
    }

    for(auto& name: employee_names)
    {
        std::cout << name << std::endl;
    }
}

bool Company::is_project_in_company(const std::string& project_id) const
{
    return projects_.find(project_id) != projects_.end();
}

Project_ptr Company::get_project(const std::string& project_id) const
{
    if(projects_.find(project_id) != projects_.end())
    {
        return projects_.at(project_id);
    }

    return nullptr;
}

bool Company::is_employee_in_company(const std::string& employee_id) const
{
    return current_staff_.find(employee_id) != current_staff_.end();
}

Employee* Company::get_employee(const std::string& employee_id) const
{
    if(current_staff_.find(employee_id) != current_staff_.end())
    {
        return current_staff_.at(employee_id);
    }

    return nullptr;
}

void Company::save_employee_project_info(const std::string& employee_id, Project_ptr project)
{
    for(auto& pair: assigned_employee_projects_)
    {
        // Employee with at least one assigned project exists
        if(pair.first == employee_id)
        {
            pair.second.push_back(project);
            return;
        }
    }

    // No projects have been assigned to the given employee. Create appropriate data structure and save info
    std::vector<Project_ptr> tmp;
    pair_employee_projects p;

    tmp.push_back(project);
    p.first = employee_id;
    p.second = tmp;

    assigned_employee_projects_.push_back(p);
}
