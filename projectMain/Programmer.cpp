#include "Programmer.h"
using namespace std;

Programmer::Programmer(size_t id, const string& name, size_t worktime, double hourlyRate, double projectContribution, double projectBudget, double earlyCompletionBonus)
    : Employee(id, name, worktime), hourlyRate(hourlyRate), projectContribution(projectContribution), projectBudget(projectBudget), earlyCompletionBonus(earlyCompletionBonus) {
    salary = calculateSalary();
}

double Programmer::calculateSalary() {
    return calcBase(hourlyRate, getWorktime()) + calcBonus() + calcBudgetPart(projectBudget, projectContribution) + calcProAdditions();
}

double Programmer::calcBase(double hourlyRate, size_t worktime) {
    return hourlyRate * worktime;
}

double Programmer::calcBonus() {
    return earlyCompletionBonus;
}

double Programmer::calcBudgetPart(double projectBudget, double personalContribution) {
    return projectBudget * personalContribution;
}

double Programmer::calcProAdditions() {
    return 0.0;
}

double Programmer::getHourlyRate() const {
    return hourlyRate;
}

void Programmer::setHourlyRate(double hourlyRate) {
    this->hourlyRate = hourlyRate;
}

double Programmer::getProjectContribution() const {
    return projectContribution;
}

void Programmer::setProjectContribution(double projectContribution) {
    this->projectContribution = projectContribution;
}

double Programmer::getProjectBudget() const {
    return projectBudget;
}

void Programmer::setProjectBudget(double projectBudget) {
    this->projectBudget = projectBudget;
}

double Programmer::getEarlyCompletionBonus() const {
    return earlyCompletionBonus;
}

void Programmer::setEarlyCompletionBonus(double earlyCompletionBonus) {
    this->earlyCompletionBonus = earlyCompletionBonus;
}

void Programmer::print() const {
    Employee::print();
    cout << "Hourly Rate: " << hourlyRate << endl;
    cout << "Project Contribution: " << projectContribution << endl;
    cout << "Project Budget: " << projectBudget << endl;
    cout << "Early Completion Bonus: " << earlyCompletionBonus << endl;
    cout << "Salary: " << salary << endl;
}
