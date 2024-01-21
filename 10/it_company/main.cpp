/* IT company
 *
 * Desc:
 *   This program implements a system for managing employees and projects
 *   inside an IT company.
 *   At first, when the execution starts, a new company is created. At this
 *   point, the user is shown a simple interface through which can execute
 *   different types of commands. In particular, several aspects of the
 *   company can be managed like: the hiring and firing process, adding skills
 *   to employees, managing projects (create and close them), assign new
 *   requirements/employees to a specific project and print all kind of
 *   information such as: the list of projects, the list of the current staff
 *   and all the employees actively working on a project.
 *   The program terminates when the user gives a quitting command (several
 *   options are available). In this case the program does not print anything.
 * 
 * Program author
 * Name: Andrea Tomasoni
 * Student number: 151920631
 * UserID: ksanto
 * E-Mail: andrea.tomasoni@tuni.fi
 * */

#include "cli.hh"
#include "company.hh"

const std::string PROMPT = "IT> ";

int main()
{
    Company* company = new Company();
    Cli cli(company, PROMPT);
    while( cli.exec() ){}

    delete company;
    return EXIT_SUCCESS;
}
