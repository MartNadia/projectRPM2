#include "Factory.h"
#include "EmployeeManagementSystem.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <sstream>

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
        return new Tester(id, name, worktime, arg1, arg2, arg3, arg4, arg5); // arg1 = hourlyRate, arg2 = projectContribution, arg3 = projectBudget, arg4 = bugsFound, arg5 = bugFixBonus
    case EmployeeType::TEAMLEADER:
        return new TeamLeader(id, name, worktime, arg1, arg2, arg3, arg4, arg5); // arg1 = hourlyRate, arg2 = projectContribution, arg3 = projectBudget, arg4 = numSubordinates, arg5 = headingBonusFactor
    case EmployeeType::PROJECTMANAGER:
        return new ProjectManager(id, name, worktime, arg1, arg2, arg3); // arg1 = projectBudget, arg2 = numProjectMembers, arg3 = headingBonusFactor
    case EmployeeType::SENIORMANAGER:
        budgets = { arg1 }; 
        return new SeniorManager(id, name, worktime, budgets, arg2, arg3);
    default:
        cout << "Error: Unknown employee type." << endl;
        return nullptr;
    }
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

bool Factory::loadProjectsFromFile(EmployeeManagementSystem& system, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    string line;
    string projectName;
    vector<string> employeeNames;

    while (getline(file, line)) {
        if (line.find("Project:") != string::npos) {
            size_t pos = line.find("Project:");
            projectName = line.substr(pos + string("Project:").length());

            size_t start = projectName.find_first_not_of(" ");
            size_t end = projectName.find_last_not_of(" ");
            if (start != string::npos && end != string::npos) {
                projectName = projectName.substr(start, end - start + 1);
            }
            else {
                projectName = "";
            }
            employeeNames.clear();
        }
        else if (line.find("Employees in project:") != string::npos) {
            size_t pos = line.find("Employees in project:");
            string employeeList = line.substr(pos + string("Employees in project:").length());

            stringstream ss(employeeList);
            string employeeName;

            while (getline(ss, employeeName, ',')) {
                size_t start = employeeName.find_first_not_of(" ");
                size_t end = employeeName.find_last_not_of(" ");

                if (start != string::npos && end != string::npos) {
                    employeeName = employeeName.substr(start, end - start + 1);
                    employeeNames.push_back(employeeName);
                }
            }
            if (!projectName.empty()) {
                Project newProject(projectName); 
                for (const auto& employeeName : employeeNames) {
                    auto it = find_if(system.employees.begin(), system.employees.end(),
                        [&](Employee* emp) { return emp->getName() == employeeName; });
                    if (it != system.employees.end()) {
                        newProject.employees.push_back(*it); 
                    }
                    else {
                        cout << "Employee " << employeeName << " not found." << endl;
                    }
                }
                system.projects.push_back(newProject);
            }
        }
    }

    file.close();
    return true;
}

bool Factory::saveProjectsToFile(const EmployeeManagementSystem& system, const string& filename){
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file for writing projects: " << filename << endl;
        return false;
    }

    for (const Project& project : system.projects) {
        file << "Project: " << project.projectName << endl;
        file << "Employees in project: ";

        for (size_t i = 0; i < project.employees.size(); ++i) {
            file << project.employees[i]->getName();
            if (i < project.employees.size() - 1) {
                file << ", ";
            }
        }
        file << endl;
    }

    file.close();
    return true;
}

bool Factory::loadEmployeesFromFile(EmployeeManagementSystem& system, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        return false; 
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        vector<string> tokens;

        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() < 4) {
            cerr << "Skipping invalid line: " << line << endl;
            continue; 
        }

        try {
            EmployeeType type = stringToEmployeeType(tokens[0]);
            size_t id = stoul(tokens[1]);
            string name = tokens[2];
            size_t worktime = stoul(tokens[3]);
            double arg1 = (tokens.size() > 4) ? stod(tokens[4]) : 0.0;
            double arg2 = (tokens.size() > 5) ? stod(tokens[5]) : 0.0;
            double arg3 = (tokens.size() > 6) ? stod(tokens[6]) : 0.0;
            size_t arg4 = (tokens.size() > 7) ? stoul(tokens[7]) : 0;
            size_t arg5 = (tokens.size() > 8) ? stoul(tokens[8]) : 0;

            Employee* employee = createEmployee(type, id, name, worktime, arg1, arg2, arg3, arg4, arg5);

            if (employee) {
                system.employees.push_back(employee);
            }
            else {
                cerr << "Failed to create employee from line: " << line << endl;
            }
        }
        catch (const std::invalid_argument& e) {
            cerr << "Error converting " << line << endl;
        }
        catch (const std::out_of_range& e) {
            cerr << "Value out of range: " << line << endl;
        }
    }
    file.close();
    return true;
}


bool Factory::saveEmployeesToFile(const EmployeeManagementSystem& system, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Could not open file for saving." << endl;
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
        file << endl;
    }
    file.close();
    return true;
}

vector<Employee*> Factory::findEmployeesByName(const EmployeeManagementSystem& system, const string& name) {
    vector<Employee*> results;
    for (Employee* emp : system.employees) {
        if (emp->getName() == name) {
            results.push_back(emp);
        }
    }
    return results;
}

vector<Employee*> Factory::findEmployeesByPosition(const EmployeeManagementSystem& system, EmployeeType position) {
    vector<Employee*> results;
    for (Employee* emp : system.employees) {
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

vector<Employee*> Factory::findEmployeesByProject(const EmployeeManagementSystem& system, const string& projectName) {
    vector<Employee*> results;
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

vector<Employee*> Factory::findEmployeesBySalary(const EmployeeManagementSystem& system, double salary, bool greaterThan) {
    vector<Employee*> results;
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

string Factory::employeeTypeToString(EmployeeType type) {
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

EmployeeType Factory::stringToEmployeeType(const string& typeString) {
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
