#include "Employee.h"

Employee::Employee() : id(0), name(""), worktime(0), hourlyRate(0.0), employeeType(EmployeeType::UNKNOWN) {}

Employee::Employee(size_t id, const string& name, size_t worktime, EmployeeType type)
	: id(id), name(name), worktime(worktime), hourlyRate(0.0), employeeType(type) {}

string employeeTypeToString(EmployeeType type) {
    switch (type) {
    case EmployeeType::PERSONAL:      return "Personal";
    case EmployeeType::ENGINEER:      return "Engineer";
    case EmployeeType::CLEANER:       return "Cleaner";
    case EmployeeType::DRIVER:        return "Driver";
    case EmployeeType::PROGRAMMER:    return "Programmer";
    case EmployeeType::TESTER:        return "Tester";
    case EmployeeType::TEAMLEADER:    return "Team Leader";
    case EmployeeType::PROJECTMANAGER: return "Project Manager";
    case EmployeeType::SENIORMANAGER: return "Senior Manager";
    default:                          return "UNKNOWN";
    }
}
size_t Employee::getId() const { return id; }

string Employee::getName() const { return name; }

size_t Employee::getWorktime() const { return worktime; }

double Employee::getHourlyRate() const { return hourlyRate; }

void Employee::setId(size_t id) { this->id = id; }

void Employee::setName(const string& name) { this->name = name; }

void Employee::setWorktime(size_t worktime) { this->worktime = worktime; }

void Employee::setHourlyRate(double hourlyRate) { this->hourlyRate = hourlyRate; }

EmployeeType Employee::getEmployeeType() const {
	return employeeType;
}

void Employee::setEmployeeType(EmployeeType type) {
	employeeType = type;
}

void Employee::print() const {
	cout << "ID: " << id << endl;
	cout << "Employee Type: " << employeeTypeToString(getEmployeeType()) << endl;
	cout << "Name: " << name << endl;
	cout << "Worktime: " << worktime << endl;
}
