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

class EmployeeManagementSystem;


class Factory {
public:
    static Employee* createEmployee(EmployeeType type, size_t id, const string& name, size_t worktime,
        double arg1 = 0.0, double arg2 = 0.0, double arg3 = 0.0, size_t arg4 = 0, size_t arg5 = 0);

    static EmployeeType getEmployeeTypeFromStringRegular(const string& typeString);

    static bool loadEmployeesFromFile(EmployeeManagementSystem& system, const string& filename);
    static bool loadProjectsFromFile(EmployeeManagementSystem& system, const string& filename);
    static bool saveProjectsToFile(const EmployeeManagementSystem& system, const string& filename);
    static bool saveEmployeesToFile(const EmployeeManagementSystem& system, const string& filename);

    static vector<Employee*> findEmployeesByName(const EmployeeManagementSystem& system, const string& name);
    static vector<Employee*> findEmployeesByPosition(const EmployeeManagementSystem& system, EmployeeType position);
    static vector<Employee*> findEmployeesByProject(const EmployeeManagementSystem& system, const string& projectName);
    static vector<Employee*> findEmployeesBySalary(const EmployeeManagementSystem& system, double salary, bool greaterThan);

private:
    Factory() {}
    static string employeeTypeToString(EmployeeType type);
    static EmployeeType stringToEmployeeType(const string& typeString);
};

ostream& operator<<(ostream& os, EmployeeType type);
