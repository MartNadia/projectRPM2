#include "Employee.h"

Employee::Employee() : id(0), name(""), worktime(0), hourlyRate(0.0) {}

Employee::Employee(size_t id, const string& name, size_t worktime)
	: id(id), name(name), worktime(worktime), hourlyRate(0.0) {}

size_t Employee::getId() const { return id; }

string Employee::getName() const { return name; }

size_t Employee::getWorktime() const { return worktime; }

double Employee::getHourlyRate() const { return hourlyRate; }

void Employee::setId(size_t id) { this->id = id; }

void Employee::setName(const string& name) { this->name = name; }

void Employee::setWorktime(size_t worktime) { this->worktime = worktime; }

void Employee::setHourlyRate(double hourlyRate) { this->hourlyRate = hourlyRate; }

void Employee::print() const {
	cout << "ID: " << id << endl;
	cout << "Name: " << name << endl;
	cout << "Worktime: " << worktime << endl;
}