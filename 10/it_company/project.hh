/* Class Project
 * ----------
 * COMP.CS.110 FALL 2023
 * ----------
 * Desc:
 *    Class for describing a project in an IT company. The class is responsible for defining
 *    the interface methods that are responsible for managing a project. In particular,
 *    the most relevant are the ones for closing a project, assign a new employee, add a
 *    requirement and print all the information.
 *
 * Program author
 * Name: Andrea Tomasoni
 * Student number: 151920631
 * UserID: ksanto
 * E-Mail: andrea.tomasoni@tuni.fi
 * */

#ifndef PROJECT_HH
#define PROJECT_HH

#include "employee.hh"
#include "date.hh"
#include "utils.hh"
#include <string>
#include <map>
#include <set>

/**
 * @brief error and information outputs
 */
const std::string NOT_QUALIFIED = "Not qualified any more: ";
const std::string REQUIREMENT = "** Requirements: ";
const std::string STAFF = "** Staff: ";

class Project
{
public:
    /**
     * @brief Project constructor
     * @param : id
     * @param : start (given as string ddmmyyyy)
     */
    Project(const std::string& id, const std::string& start);

    /**
     * @brief Project constructor
     * @param : id
     * @param : start (given as Date object)
     */
    Project(const std::string& id, const Date& start);

    /**
     * @brief Project destructor
     */
    ~Project();

    // More public methods
    /**
     * @brief close
     * @param : close_date (given as Date object)
     * Closes the project by setting its end date with the one given as paramter
     */
    void close(Date& close_date);

    /**
     * @brief print_date
     * Prints the name of the project along with its start and end (if closed) dates
     */
    void print_date() const;

    /**
     * @brief is_active
     * @return true
     * @return false 
     * Checks whether the project is open or closed. Returns true in the former case 
     * and false in the latter
     */
    bool is_active() const;

    /**
     * @brief is_employee_assignable
     * @param : employee (given as Employee* pointer)
     * @return true 
     * @return false 
     * Verifies whether the given employee can be assigned to the project 
     * by meeting the selected criteria. Returns true if the employee is assignable
     * and false otherwise
     */
    bool is_employee_assignable(const Employee* employee) const;

    /**
     * @brief assign
     * @param : employee_id (given as string)
     * @param : employee (given as an Employee* pointer)
     * Assigns the employee to the project
     */
    void assign(const std::string& employee_id, Employee* employee);

    /**
     * @brief add_requirement
     * @param : req (given as string)
     * First adds the given requirement and then checks if the employee must be removed or not
     * from the project
     */
    void add_requirement(const std::string& req);

    /**
     * @brief print_info
     * Prints all the information about the project (start and end dates, requirements and the staff)
     */
    void print_info() const;

private:
    /**
     * @brief obvious attributes
     */
    std::string id_; // Can be a name or any other identifier
    Date start_;
    Date end_;

    /**
     * @brief additional attributes
     * is_active_ is used to verify if the project is ongoing or not,
     * requirements_ is a set containing all the skills required by the project,
     * employees_ contains all the assigned employees
     */
    bool is_active_;
    std::set<std::string> requirements_;
    std::map<std::string, Employee*> employees_;

    /**
     * @brief is_employee_in_project
     * @param : employee_id (given as string)
     * @return true 
     * @return false
     * Checks if the given employee is working on the project. Returns true if so,
     * otherwise false
     */
    bool is_employee_in_project(const std::string& employee_id) const;

    /**
     * @brief has_employee_required_skills
     * @param : employee (given as Employee* pointer)
     * @return true 
     * @return false 
     * Checks whether the given employee has at least one of the skills required for the project.
     * Returns true in the first case and false otherwise
     */
    bool has_employee_required_skills(const Employee* employee) const;

    /**
     * @brief print_requirements
     * Prints all the project requirements in alphabetical order
     */
    void print_requirements() const;

    /**
     * @brief print_staff
     * Prints all the employees assigned to the project in alphabetical order
     */
    void print_staff() const;
};

#endif // PROJECT_HH
