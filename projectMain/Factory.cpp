#include "Factory.h"
#include "EmployeeManagementSystem.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm> // Для std::transform
#include <cctype>    // Для std::toupper
#include <sstream> // Для stringstream

using namespace std;

Employee* Factory::createEmployee(EmployeeType type, size_t id, const string& name, size_t worktime,
    double arg1, double arg2, double arg3, size_t arg4, size_t arg5) {

    std::vector<double> budgets;
    switch (type) {
    case EmployeeType::PERSONAL:
        return new Personal(id, name, worktime, arg1); // arg1 = hourlyRate
    case EmployeeType::ENGINEER:
        return new Engineer(id, name, worktime, arg1, arg2, arg3); // arg1 = hourlyRate, arg2 = projectContribution, arg3 = projectBudget
    case EmployeeType::CLEANER:
        return new Cleaner(id, name, worktime, arg1); // arg1 = hourlyRate
    case EmployeeType::DRIVER:
        return new Driver(id, name, worktime, arg1, arg2, static_cast<size_t>(arg3)); // arg1 = hourlyRate, arg2 = nightHourBonus, arg3 = nightHours
    case EmployeeType::PROGRAMMER:
        return new Programmer(id, name, worktime, arg1, arg2, arg3, arg4); // arg1 = hourlyRate, arg2 = projectContribution, arg3 = projectBudget, arg4 = earlyCompletionBonus
    case EmployeeType::TESTER:
        return new Tester(id, name, worktime, arg1, arg2, arg3, arg4, arg5); // arg1 = hourlyRate, arg2 = projectContribution, arg3 = projectBudget, arg4 = bugsFound, 0.0 = bugFixBonus (default)
    case EmployeeType::TEAMLEADER:
        return new TeamLeader(id, name, worktime, arg1, arg2, arg3, arg4, arg5); // arg1 = hourlyRate, arg2 = projectContribution, arg3 = projectBudget, arg4 = numSubordinates, 0.0 = headingBonusFactor (default)
    case EmployeeType::PROJECTMANAGER:
        return new ProjectManager(id, name, worktime, arg1, arg2, arg3); // arg1 = projectBudget, arg2 = numProjectMembers, arg3 = headingBonusFactor
    case EmployeeType::SENIORMANAGER:
        // Используем параметры как-то так:
        budgets = { arg3 }; //  Используем arg3 в качестве бюджета
        //  arg5 = totalEmployees (общее количество сотрудников)
        //  arg2 = headingBonusFactor (бонус за руководство)

        return new SeniorManager(id, name, worktime, budgets, arg4, arg2);
    default:
        cout << "Error: Unknown employee type." << endl;
        return nullptr;
    }
}

EmployeeType Factory::getEmployeeTypeFromString(const string& typeString) {
    if (typeString == "PERSONAL") return EmployeeType::PERSONAL;
    else if (typeString == "ENGINEER") return EmployeeType::ENGINEER;
    else if (typeString == "CLEANER") return EmployeeType::CLEANER;
    else if (typeString == "DRIVER") return EmployeeType::DRIVER;
    else if (typeString == "PROGRAMMER") return EmployeeType::PROGRAMMER;
    else if (typeString == "TESTER") return EmployeeType::TESTER;
    else if (typeString == "TEAMLEADER") return EmployeeType::TEAMLEADER;
    else if (typeString == "PROJECTMANAGER") return EmployeeType::PROJECTMANAGER;
    else if (typeString == "SENIORMANAGER") return EmployeeType::SENIORMANAGER;
    else return EmployeeType::UNKNOWN;
}

EmployeeType Factory::getEmployeeTypeFromStringRegular(const string& typeString) {
    if (typeString == "Personal") return EmployeeType::PERSONAL;
    else if (typeString == "Engineer") return EmployeeType::ENGINEER;
    else if (typeString == "Cleaner") return EmployeeType::CLEANER;
    else if (typeString == "Driver") return EmployeeType::DRIVER;
    else if (typeString == "Programmer") return EmployeeType::PROGRAMMER;
    else if (typeString == "Tester") return EmployeeType::TESTER;
    else if (typeString == "Team Leader") return EmployeeType::TEAMLEADER;
    else if (typeString == "Project Manager") return EmployeeType::PROJECTMANAGER;
    else if (typeString == "Senior Manager") return EmployeeType::SENIORMANAGER;
    else return EmployeeType::UNKNOWN;
}
// --- File I/O ---
bool Factory::loadEmployeesFromFile(EmployeeManagementSystem& system, const std::string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        return false; // Indicate failure
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        std::vector<std::string> tokens;

        while (std::getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() < 4) {
            std::cerr << "Skipping invalid line: " << line << std::endl;
            continue; // Skip this line and go to the next one
        }

        try {
            EmployeeType type = stringToEmployeeType(tokens[0]);
            size_t id = std::stoul(tokens[1]);
            std::string name = tokens[2];
            size_t worktime = std::stoul(tokens[3]);
            double arg1 = (tokens.size() > 4) ? std::stod(tokens[4]) : 0.0;
            double arg2 = (tokens.size() > 5) ? std::stod(tokens[5]) : 0.0;
            double arg3 = (tokens.size() > 6) ? std::stod(tokens[6]) : 0.0;
            size_t arg4 = (tokens.size() > 7) ? std::stoul(tokens[7]) : 0;
            size_t arg5 = (tokens.size() > 8) ? std::stoul(tokens[8]) : 0;

            Employee* employee = createEmployee(type, id, name, worktime, arg1, arg2, arg3, arg4, arg5);

            if (employee) {
                system.employees.push_back(employee);
            }
            else {
                std::cerr << "Failed to create employee from line: " << line << std::endl;
            }
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "Error converting " << line << std::endl;
        }
        catch (const std::out_of_range& e) {
            std::cerr << "Value out of range: " << line << std::endl;
        }
    }
    file.close();
    return true;
}

bool Factory::saveEmployeesToFile(const EmployeeManagementSystem& system, const std::string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Could not open file for saving." << std::endl;
        return false;
    }

    for (const Employee* emp : system.employees) {
        EmployeeType employeeType;

        if (dynamic_cast<const Personal*>(emp)) {
            employeeType = EmployeeType::PERSONAL;
        }
        else if (dynamic_cast<const Engineer*>(emp)) {
            employeeType = EmployeeType::ENGINEER;
        }
        else if (dynamic_cast<const Cleaner*>(emp)) {
            employeeType = EmployeeType::CLEANER;
        }
        else if (dynamic_cast<const Driver*>(emp)) {
            employeeType = EmployeeType::DRIVER;
        }
        else if (dynamic_cast<const Programmer*>(emp)) {
            employeeType = EmployeeType::PROGRAMMER;
        }
        else if (dynamic_cast<const Tester*>(emp)) {
            employeeType = EmployeeType::TESTER;
        }
        else if (dynamic_cast<const TeamLeader*>(emp)) {
            employeeType = EmployeeType::TEAMLEADER;
        }
        else if (dynamic_cast<const ProjectManager*>(emp)) {
            employeeType = EmployeeType::PROJECTMANAGER;
        }
        else if (dynamic_cast<const SeniorManager*>(emp)) {
            employeeType = EmployeeType::SENIORMANAGER;
        }
        else {
            employeeType = EmployeeType::UNKNOWN;
        }

        file << employeeTypeToString(employeeType) << ","
            << emp->getId() << ","
            << emp->getName() << ","
            << emp->getWorktime() << ",";

        // Depending on the employee type, save additional data to the file
        if (dynamic_cast<const Personal*>(emp)) {
            const Personal* p = dynamic_cast<const Personal*>(emp);
            file << p->getHourlyRate();
        }
        else if (dynamic_cast<const Engineer*>(emp)) {
            const Engineer* e = dynamic_cast<const Engineer*>(emp);
            file << e->getHourlyRate() << "," << e->getProjectContribution() << "," << e->getProjectBudget();
        }
        else if (dynamic_cast<const Cleaner*>(emp)) {
            const Cleaner* c = dynamic_cast<const Cleaner*>(emp);
            file << c->getHourlyRate();
        }
        else if (dynamic_cast<const Driver*>(emp)) {
            const Driver* d = dynamic_cast<const Driver*>(emp);
            file << d->getHourlyRate() << "," << d->getNightHourBonus() << "," << d->getNightHours();
        }
        else if (dynamic_cast<const Programmer*>(emp)) {
            const Programmer* p = dynamic_cast<const Programmer*>(emp);
            file << p->getHourlyRate() << "," << p->getProjectContribution() << "," << p->getProjectBudget() << "," << p->getEarlyCompletionBonus();
        }
        else if (dynamic_cast<const Tester*>(emp)) {
            const Tester* t = dynamic_cast<const Tester*>(emp);
            file << t->getHourlyRate() << "," << t->getProjectContribution() << "," << t->getProjectBudget() << "," << t->getBugsFound() << "," << t->getBugFixBonus();
        }
        else if (dynamic_cast<const TeamLeader*>(emp)) {
            const TeamLeader* tl = dynamic_cast<const TeamLeader*>(emp);
            file << tl->getHourlyRate() << "," << tl->getProjectContribution() << "," << tl->getProjectBudget() << "," << tl->getNumSubordinates() << "," << tl->getHeadingBonusFactor();
        }
        else if (dynamic_cast<const ProjectManager*>(emp)) {
            const ProjectManager* pm = dynamic_cast<const ProjectManager*>(emp);
            file << pm->getProjectBudget() << "," << pm->getNumProjectMembers() << "," << pm->getHeadingBonusFactor();
        }
        else if (dynamic_cast<const SeniorManager*>(emp)) {
            const SeniorManager* sm = dynamic_cast<const SeniorManager*>(emp);
            file << sm->getTotalBudget() << "," << sm->getTotalEmployees() << "," << sm->getHeadingBonusFactor();
        }
        file << endl; // End of employee line
    }
    file.close();
    return true;
}

// --- Search Functions ---
std::vector<Employee*> Factory::findEmployeesByName(const EmployeeManagementSystem& system, const std::string& name) {
    std::vector<Employee*> results;
    for (Employee* emp : system.employees) {
        if (emp->getName() == name) {
            results.push_back(emp);
        }
    }
    return results;
}

std::vector<Employee*> Factory::findEmployeesByPosition(const EmployeeManagementSystem& system, EmployeeType position) {
    std::vector<Employee*> results;
    for (Employee* emp : system.employees) {
        // Используем параметр функции 'position'
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
    return results;
}

std::vector<Employee*> Factory::findEmployeesByProject(const EmployeeManagementSystem& system, const std::string& projectName) {
    std::vector<Employee*> results;
    for (const Project& project : system.projects) {
        if (project.projectName == projectName) {
            for (Employee* emp : project.employees) {
                results.push_back(emp);
            }
            break; // Assuming project names are unique
        }
    }
    return results;
}

std::vector<Employee*> Factory::findEmployeesBySalary(const EmployeeManagementSystem& system, double salary, bool greaterThan) {
    std::vector<Employee*> results;
    for (Employee* emp : system.employees) {
        if (greaterThan && emp->calculateSalary() > salary) {
            results.push_back(emp);
        }
        else if (!greaterThan && emp->calculateSalary() < salary) {
            results.push_back(emp);
        }
    }
    return results;
}

std::string Factory::employeeTypeToString(EmployeeType type) {
    switch (type) {
    case EmployeeType::PERSONAL: return "PERSONAL";
    case EmployeeType::ENGINEER: return "ENGINEER";
    case EmployeeType::CLEANER: return "CLEANER";
    case EmployeeType::DRIVER: return "DRIVER";
    case EmployeeType::PROGRAMMER: return "PROGRAMMER";
    case EmployeeType::TESTER: return "TESTER";
    case EmployeeType::TEAMLEADER: return "TEAMLEADER";
    case EmployeeType::PROJECTMANAGER: return "PROJECTMANAGER";
    case EmployeeType::SENIORMANAGER: return "SENIORMANAGER";
    default: return "UNKNOWN";
    }
}

EmployeeType Factory::stringToEmployeeType(const std::string& typeString) {
    if (typeString == "PERSONAL") return EmployeeType::PERSONAL;
    else if (typeString == "ENGINEER") return EmployeeType::ENGINEER;
    else if (typeString == "CLEANER") return EmployeeType::CLEANER;
    else if (typeString == "DRIVER") return EmployeeType::DRIVER;
    else if (typeString == "PROGRAMMER") return EmployeeType::PROGRAMMER;
    else if (typeString == "TESTER") return EmployeeType::TESTER;
    else if (typeString == "TEAMLEADER") return EmployeeType::TEAMLEADER;
    else if (typeString == "PROJECTMANAGER") return EmployeeType::PROJECTMANAGER;
    else if (typeString == "SENIORMANAGER") return EmployeeType::SENIORMANAGER;
    else return EmployeeType::UNKNOWN;
}

std::ostream& operator<<(std::ostream& os, EmployeeType type) {
    switch (type) {
    case EmployeeType::PERSONAL:      os << "PERSONAL";      break;
    case EmployeeType::ENGINEER:      os << "ENGINEER";      break;
    case EmployeeType::CLEANER:       os << "CLEANER";       break;
    case EmployeeType::DRIVER:        os << "DRIVER";        break;
    case EmployeeType::PROGRAMMER:    os << "PROGRAMMER";    break;
    case EmployeeType::TESTER:        os << "TESTER";        break;
    case EmployeeType::TEAMLEADER:    os << "TEAMLEADER";    break;
    case EmployeeType::PROJECTMANAGER: os << "PROJECTMANAGER"; break;
    case EmployeeType::SENIORMANAGER: os << "SENIORMANAGER"; break;
    default:                          os << "UNKNOWN";       break;
    }
    return os;
}