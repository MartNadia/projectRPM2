#pragma once
#include <vector>
#include <string>
#include "Employee.h"
#include "Factory.h" // Correct include
//class Factory;
class Project {
public:
    std::string projectName;
    std::vector<Employee*> employees;

    Project(const std::string& name) : projectName(name) {}

    void addEmployee(Employee* employee) {
        employees.push_back(employee);
    }

    void removeEmployee(Employee* employee) {
        for (size_t i = 0; i < employees.size(); ++i) {
            if (employees[i]->getId() == employee->getId()) {
                employees.erase(employees.begin() + i);
                return;
            }
        }
    }

    bool hasEmployee(Employee* employee) const {
        for (Employee* emp : employees) {
            if (emp->getId() == employee->getId()) {
                return true;
            }
        }
        return false;
    }
};

class EmployeeManagementSystem {
public:
    std::vector<Employee*> employees;
    std::vector<Project> projects;

    ~EmployeeManagementSystem() {
        for (Employee* emp : employees) {
            delete emp; // Prevent memory leaks
        }
    }

    // --- Employee Management ---
    void addEmployee(EmployeeType type, size_t id, const std::string& name, size_t worktime,
        double arg1 = 0.0, double arg2 = 0.0, double arg3 = 0.0, size_t arg4 = 0);
    void removeEmployee(size_t id); // Remove by employee ID

    // --- Project Management ---
    void createProject(const std::string& projectName);
    void addEmployeeToProject(size_t employeeId, const std::string& projectName);
    void transferEmployeeToProject(size_t employeeId, const std::string& oldProjectName, const std::string& newProjectName);

    // --- Display and Search ---
    void displayAllEmployees() const;
    void displayEmployeesInProject(const std::string& projectName) const;
};

