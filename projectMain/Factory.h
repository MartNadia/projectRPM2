#pragma once
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
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

// Forward declaration for EmployeeManagementSystem
class EmployeeManagementSystem;


class Factory {
public:
    static Employee* createEmployee(EmployeeType type, size_t id, const std::string& name, size_t worktime,
        double arg1 = 0.0, double arg2 = 0.0, double arg3 = 0.0, size_t arg4 = 0, size_t arg5 = 0);

    static EmployeeType getEmployeeTypeFromString(const std::string& typeString);
    static EmployeeType getEmployeeTypeFromStringRegular(const std::string& typeString);

    // --- File I/O ---
    static bool loadEmployeesFromFile(EmployeeManagementSystem& system, const std::string& filename);
    static bool saveEmployeesToFile(const EmployeeManagementSystem& system, const std::string& filename);

    // --- Search Functions ---
    static std::vector<Employee*> findEmployeesByName(const EmployeeManagementSystem& system, const std::string& name);
    static std::vector<Employee*> findEmployeesByPosition(const EmployeeManagementSystem& system, EmployeeType position);
    static std::vector<Employee*> findEmployeesByProject(const EmployeeManagementSystem& system, const std::string& projectName);
    static std::vector<Employee*> findEmployeesBySalary(const EmployeeManagementSystem& system, double salary, bool greaterThan);

private:
    Factory() {} // Private constructor to prevent instantiation
    // Helper function to convert EmployeeType to string (for saving)
    static std::string employeeTypeToString(EmployeeType type);
    // Helper function to convert string to EmployeeType (for loading)
    static EmployeeType stringToEmployeeType(const std::string& typeString);
};

// Overload the << operator for EmployeeType
std::ostream& operator<<(std::ostream& os, EmployeeType type);
