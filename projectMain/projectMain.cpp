#include <iostream>
#include <string>
#include "Employee.h"
#include "Personal.h"
#include "Engineer.h"
#include "Cleaner.h"
#include "Driver.h"
#include "Programmer.h"
#include "Tester.h"
#include "TeamLeader.h"
#include "ProjectManager.h"
#include "SeniorManager.h"
#include "EmployeeManagementSystem.h"
#include "Factory.h"
#include <vector>
#include <cassert>
#include <limits>

using namespace std;

void clearInputBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main()
{
    EmployeeManagementSystem system;
    const string dataFileName = "company.txt";

    // 1. Load data from file
    if (Factory::loadEmployeesFromFile(system, dataFileName)) {
        cout << "Data loaded from " << dataFileName << endl;
    }
    else {
        cout << "No data file found or loading failed. Starting with an empty system." << endl;
    }

    // 2. Main menu loop
    int choice;
    do {
        cout << "\n--- Employee Management System ---" << endl;
        cout << "1. Add Employee" << endl;
        cout << "2. Remove Employee" << endl;
        cout << "3. Create Project" << endl;
        cout << "4. Add Employee to Project" << endl;
        cout << "5. Transfer Employee to Project" << endl;
        cout << "6. Display All Employees" << endl;
        cout << "7. Display Employees in Project" << endl;
        cout << "8. Search Employees by Name" << endl;
        cout << "9. Search Employees by Position" << endl;
        cout << "10. Search Employees by Project" << endl;
        cout << "11. Search Employees by Salary" << endl;
        cout << "0. Exit" << endl;//
        cout << "Enter your choice: ";
        cin >> choice;
        clearInputBuffer(); // Clear newline from the input buffer

        switch (choice) {
        case 1: {
            // Add Employee
            cout << "Enter employee type (PERSONAL, ENGINEER, CLEANER, DRIVER, PROGRAMMER, TESTER, TEAMLEADER, PROJECTMANAGER): ";
            string employeeTypeStr;
            cin >> employeeTypeStr;
            clearInputBuffer();
            EmployeeType employeeType = Factory::getEmployeeTypeFromString(employeeTypeStr);

            if (employeeType != EmployeeType::UNKNOWN) {
                size_t id;
                string name;
                size_t worktime;

                cout << "Enter employee ID: ";
                cin >> id;
                clearInputBuffer();

                cout << "Enter employee name: ";
                getline(cin, name);

                cout << "Enter worktime: ";
                cin >> worktime;
                clearInputBuffer();

                // Gather employee-specific arguments if needed
                double arg1 = 0.0, arg2 = 0.0, arg3 = 0.0;
                size_t arg4 = 0, arg5 = 0;

                if (employeeType == EmployeeType::ENGINEER) {
                    cout << "Enter hourly rate: ";
                    cin >> arg1;
                    clearInputBuffer();
                    cout << "Enter project contribution (0.0-1.0): ";
                    cin >> arg2;
                    clearInputBuffer();
                    cout << "Enter project budget: ";
                    cin >> arg3;
                    clearInputBuffer();
                }
                else if (employeeType == EmployeeType::DRIVER) {
                    cout << "Enter hourly rate: ";
                    cin >> arg1;
                    clearInputBuffer();
                    cout << "Enter night hour bonus: ";
                    cin >> arg2;
                    clearInputBuffer();
                    cout << "Enter night hours: ";
                    cin >> arg3;
                    clearInputBuffer();
                }
                else if (employeeType == EmployeeType::PROGRAMMER) {
                    cout << "Enter hourly rate: ";
                    cin >> arg1;
                    clearInputBuffer();
                    cout << "Enter project contribution (0.0-1.0): ";
                    cin >> arg2;
                    clearInputBuffer();
                    cout << "Enter project budget: ";
                    cin >> arg3;
                    clearInputBuffer();
                    cout << "Enter early completion bonus: ";
                    cin >> arg4;
                    clearInputBuffer();
                }
                else if (employeeType == EmployeeType::TESTER) {
                    cout << "Enter hourly rate: ";
                    cin >> arg1;
                    clearInputBuffer();
                    cout << "Enter project contribution (0.0-1.0): ";
                    cin >> arg2;
                    clearInputBuffer();
                    cout << "Enter project budget: ";
                    cin >> arg3;
                    clearInputBuffer();
                    cout << "Enter bugs found: ";
                    cin >> arg4;
                    clearInputBuffer();
                    cout << "Enter bug fix bonus: ";
                    cin >> arg5;
                    clearInputBuffer();
                }
                else if (employeeType == EmployeeType::TEAMLEADER) {
                    cout << "Enter hourly rate: ";
                    cin >> arg1;
                    clearInputBuffer();
                    cout << "Enter project contribution (0.0-1.0): ";
                    cin >> arg2;
                    clearInputBuffer();
                    cout << "Enter project budget: ";
                    cin >> arg3;
                    clearInputBuffer();
                    cout << "Enter numSubordinates: ";
                    cin >> arg4;
                    clearInputBuffer();
                }
                else if (employeeType == EmployeeType::PROJECTMANAGER) {
                    cout << "Enter project budget: ";
                    cin >> arg1;
                    clearInputBuffer();
                    cout << "Enter numProjectMembers: ";
                    cin >> arg2;
                    clearInputBuffer();
                    cout << "Enter headingBonusFactor: ";
                    cin >> arg3;
                    clearInputBuffer();
                }
                else if (employeeType == EmployeeType::SENIORMANAGER) {
                    cout << "Enter project budget: ";
                    cin >> arg3;
                    clearInputBuffer();
                    cout << "Enter totalEmployees: ";
                    cin >> arg4;
                    clearInputBuffer();
                    cout << "Enter headingBonusFactor: ";
                    cin >> arg2;
                    clearInputBuffer();
                }
                else if (employeeType == EmployeeType::PERSONAL || employeeType == EmployeeType::CLEANER) {
                    cout << "Enter hourly rate: ";
                    cin >> arg1;
                    clearInputBuffer();
                }


                system.addEmployee(employeeType, id, name, worktime, arg1, arg2, arg3, arg4);
            }
            else {
                cout << "Invalid employee type." << endl;
            }
            break;
        }
        case 2: {
            // Remove Employee
            size_t id;
            cout << "Enter employee ID to remove: ";
            cin >> id;
            clearInputBuffer();
            system.removeEmployee(id);
            break;
        }
        case 3: {
            // Create Project
            string projectName;
            cout << "Enter project name: ";
            getline(cin, projectName);
            system.createProject(projectName);
            break;
        }
        case 4: {
            // Add Employee to Project
            size_t employeeId;
            string projectName;
            cout << "Enter employee ID: ";
            cin >> employeeId;
            clearInputBuffer();
            cout << "Enter project name: ";
            getline(cin, projectName);
            system.addEmployeeToProject(employeeId, projectName);
            break;
        }
        case 5: {
            // Transfer Employee to Project
            size_t employeeId;
            string oldProjectName, newProjectName;
            cout << "Enter employee ID: ";
            cin >> employeeId;
            clearInputBuffer();
            cout << "Enter old project name: ";
            getline(cin, oldProjectName);
            cout << "Enter new project name: ";
            getline(cin, newProjectName);
            system.transferEmployeeToProject(employeeId, oldProjectName, newProjectName);
            break;
        }
        case 6: {
            // Display All Employees
            system.displayAllEmployees();
            break;
        }
        case 7: {
            // Display Employees in Project
            string projectName;
            cout << "Enter project name: ";
            getline(cin, projectName);
            system.displayEmployeesInProject(projectName);
            break;
        }
        case 8: {
            // Search Employees by Name
            string name;
            cout << "Enter employee name to search for: ";
            getline(cin, name);
            vector<Employee*> results = Factory::findEmployeesByName(system, name);
            if (!results.empty()) {
                cout << "Employees found:" << endl;
                for (Employee* emp : results) {
                    emp->print();
                }
            }
            else {
                cout << "No employees found with that name." << endl;
            }
            break;
        }

        case 9: { // Поиск по должности
            string positionStr;
            cout << "Enter employee position to search for: ";
            getline(cin, positionStr);

            EmployeeType position = Factory::getEmployeeTypeFromStringRegular(positionStr);

            if (position == EmployeeType::UNKNOWN) {
                cout << "Invalid employee position." << endl;
            }
            else {
                // Поиск сотрудников по должности
                vector<Employee*> results;
                for (Employee* emp : system.employees) { // Используем vector из EmployeeManagementSystem
                    if (position == EmployeeType::PERSONAL && dynamic_cast<Personal*>(emp) != nullptr) {
                        results.push_back(emp);
                    }
                    else if (position == EmployeeType::ENGINEER && dynamic_cast<Engineer*>(emp) != nullptr) {
                        results.push_back(emp);
                    }
                    else if (position == EmployeeType::CLEANER && dynamic_cast<Cleaner*>(emp) != nullptr) {
                        results.push_back(emp);
                    }
                    else if (position == EmployeeType::DRIVER && dynamic_cast<Driver*>(emp) != nullptr) {
                        results.push_back(emp);
                    }
                    else if (position == EmployeeType::PROGRAMMER && dynamic_cast<Programmer*>(emp) != nullptr) {
                        results.push_back(emp);
                    }
                    else if (position == EmployeeType::TESTER && dynamic_cast<Tester*>(emp) != nullptr) {
                        results.push_back(emp);
                    }
                    else if (position == EmployeeType::TEAMLEADER && dynamic_cast<TeamLeader*>(emp) != nullptr) {
                        results.push_back(emp);
                    }
                    else if (position == EmployeeType::PROJECTMANAGER && dynamic_cast<ProjectManager*>(emp) != nullptr) {
                        results.push_back(emp);
                    }
                    else if (position == EmployeeType::SENIORMANAGER && dynamic_cast<SeniorManager*>(emp) != nullptr) {
                        results.push_back(emp);
                    }
                }

                // Вывод результатов
                cout << "Employees with position " << positionStr << ":" << endl;
                for (Employee* emp : results) {
                    emp->print();
                    cout << endl;
                }
            }
            break;
        }

        case 10: {
            // Search Employees by Project
            string projectName;
            cout << "Enter project name: ";
            getline(cin, projectName);
            vector<Employee*> results = Factory::findEmployeesByProject(system, projectName);
            if (!results.empty()) {
                cout << "Employees in project " << projectName << ":" << endl;
                for (Employee* emp : results) {
                    emp->print();
                }
            }
            else {
                cout << "No employees found in that project." << endl;
            }
            break;
        }
        case 11: {
            // Search Employees by Salary
            double salary;
            cout << "Enter salary to search for: ";
            cin >> salary;
            clearInputBuffer();
            cout << "Search for employees earning more (1) or less (0) than " << salary << "? (1/0): ";
            int greaterThanChoice;
            cin >> greaterThanChoice;
            clearInputBuffer();
            bool greaterThan = (greaterThanChoice == 1);
            vector<Employee*> results = Factory::findEmployeesBySalary(system, salary, greaterThan);
            if (!results.empty()) {
                cout << "Employees found:" << endl;
                for (Employee* emp : results) {
                    emp->print();
                }
            }
            else {
                cout << "No employees found with that salary." << endl;
            }
            break;
        }
        case 0:
            std::cout << "Saving data to file..." << std::endl;
            Factory::saveEmployeesToFile(system, dataFileName);
            std::cout << "Exiting..." << std::endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);

    return 0;
}
