#include "EmployeeManagementSystem.h"
#include <iostream>

using namespace std;

// --- Employee Management ---
void EmployeeManagementSystem::addEmployee(EmployeeType type, size_t id, const string& name, size_t worktime,
    double arg1, double arg2, double arg3, size_t arg4) {
    Employee* newEmployee = Factory::createEmployee(type, id, name, worktime, arg1, arg2, arg3, arg4);
    if (newEmployee) {
        employees.push_back(newEmployee);
    }
}

void EmployeeManagementSystem::removeEmployee(size_t id) {
    for (size_t i = 0; i < employees.size(); ++i) {
        if (employees[i]->getId() == id) {
            delete employees[i];
            employees.erase(employees.begin() + i);
            return;
        }
    }
    cout << "Employee with ID " << id << " not found." << endl;
}

// --- Project Management ---
void EmployeeManagementSystem::createProject(const string& projectName) {
    projects.emplace_back(projectName);
}

void EmployeeManagementSystem::addEmployeeToProject(size_t employeeId, const string& projectName) {
    Employee* employeeToAdd = nullptr;
    for (Employee* emp : employees) {
        if (emp->getId() == employeeId) {
            employeeToAdd = emp;
            break;
        }
    }

    if (!employeeToAdd) {
        cout << "Employee with ID " << employeeId << " not found." << endl;
        return;
    }

    for (Project& proj : projects) {
        if (proj.projectName == projectName) {
            if (!proj.hasEmployee(employeeToAdd)) {
                proj.addEmployee(employeeToAdd);
                cout << "Employee " << employeeId << " added to project " << projectName << endl;
            }
            else {
                cout << "Employee " << employeeId << " is already on project " << projectName << endl;
            }
            return;
        }
    }

    cout << "Project " << projectName << " not found." << endl;
}

void EmployeeManagementSystem::transferEmployeeToProject(size_t employeeId, const string& oldProjectName, const string& newProjectName) {
    Employee* employeeToTransfer = nullptr;
    for (Employee* emp : employees) {
        if (emp->getId() == employeeId) {
            employeeToTransfer = emp;
            break;
        }
    }

    if (!employeeToTransfer) {
        cout << "Employee with ID " << employeeId << " not found." << endl;
        return;
    }

    Project* oldProject = nullptr;
    Project* newProject = nullptr;

    for (Project& proj : projects) {
        if (proj.projectName == oldProjectName) {
            oldProject = &proj;
        }
        if (proj.projectName == newProjectName) {
            newProject = &proj;
        }
    }

    if (!oldProject) {
        cout << "Old project " << oldProjectName << " not found." << endl;
        return;
    }

    if (!newProject) {
        cout << "New project " << newProjectName << " not found." << endl;
        return;
    }

    if (oldProject->hasEmployee(employeeToTransfer)) {
        oldProject->removeEmployee(employeeToTransfer);
        newProject->addEmployee(employeeToTransfer);
        cout << "Employee " << employeeId << " transferred from " << oldProjectName << " to " << newProjectName << endl;
    }
    else {
        cout << "Employee " << employeeId << " is not on project " << oldProjectName << endl;
    }
}

// --- Display and Search ---
void EmployeeManagementSystem::displayAllEmployees() const {
    cout << "--- All Employees ---" << endl;
    for (const Employee* emp : employees) {
        emp->print();
        cout << endl;
    }
}

void EmployeeManagementSystem::displayEmployeesInProject(const string& projectName) const {
    cout << "--- Employees in Project: " << projectName << " ---" << endl;
    for (const Project& proj : projects) {
        if (proj.projectName == projectName) {
            for (const Employee* emp : proj.employees) {
                emp->print();
                cout << endl;
            }
            return;
        }
    }
    cout << "Project " << projectName << " not found." << endl;
}