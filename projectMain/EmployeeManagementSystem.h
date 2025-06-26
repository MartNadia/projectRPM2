#pragma once
#include <vector>
#include <string>
#include "Employee.h"
#include "Factory.h" 

class Project {
public:
    string projectName;
    vector<Employee*> employees;

    Project(const string& name) : projectName(name) {}

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
    vector<Employee*> employees;
    vector<Project> projects;

    ~EmployeeManagementSystem() {
        for (Employee* emp : employees) {
            delete emp;
        }
    }

    void addEmployee(EmployeeType type, size_t id, const string& name, size_t worktime,
        double arg1 = 0.0, double arg2 = 0.0, double arg3 = 0.0, size_t arg4 = 0);
    void removeEmployee(size_t id);

    void createProject(const string& projectName);
    void addEmployeeToProject(size_t employeeId, const string& projectName);
    void transferEmployeeToProject(size_t employeeId, const string& oldProjectName, const string& newProjectName);

    void displayAllEmployees() const;
    void displayEmployeesInProject(const string& projectName) const;
};

