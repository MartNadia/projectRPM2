#include "Tester.h"
using namespace std;

Tester::Tester(size_t id, const string& name, size_t worktime, double hourlyRate, double projectContribution, double projectBudget, size_t bugsFound, double bugFixBonus)
    : Employee(id, name, worktime), hourlyRate(hourlyRate), projectContribution(projectContribution), projectBudget(projectBudget), bugsFound(bugsFound), bugFixBonus(bugFixBonus) {
    salary = calculateSalary();
}

double Tester::calculateSalary() {
    return calcBase(hourlyRate, getWorktime()) + calcBonus() + calcBudgetPart(projectBudget, projectContribution) + calcProAdditions();
}

double Tester::calcBase(double hourlyRate, size_t worktime) {
    return hourlyRate * worktime;
}

double Tester::calcBonus() {
    return bugsFound * bugFixBonus;
}

double Tester::calcBudgetPart(double projectBudget, double personalContribution) {
    return projectBudget * personalContribution;
}

double Tester::calcProAdditions() {
    return 0.0;
}

double Tester::getHourlyRate() const {
    return hourlyRate;
}

void Tester::setHourlyRate(double hourlyRate) {
    this->hourlyRate = hourlyRate;
}

double Tester::getProjectContribution() const {
    return projectContribution;
}

void Tester::setProjectContribution(double projectContribution) {
    this->projectContribution = projectContribution;
}

double Tester::getProjectBudget() const {
    return projectBudget;
}

void Tester::setProjectBudget(double projectBudget) {
    this->projectBudget = projectBudget;
}

size_t Tester::getBugsFound() const {
    return bugsFound;
}

void Tester::setBugsFound(size_t bugsFound) {
    this->bugsFound = bugsFound;
}

double Tester::getBugFixBonus() const {
    return bugFixBonus;
}

void Tester::setBugFixBonus(double bugFixBonus) {
    this->bugFixBonus = bugFixBonus;
}

void Tester::print() const {
    Employee::print();
    cout << "Hourly Rate: " << hourlyRate << endl;
    cout << "Project Contribution: " << projectContribution << endl;
    cout << "Project Budget: " << projectBudget << endl;
    cout << "Bugs Found: " << bugsFound << endl;
    cout << "Bug Fix Bonus: " << bugFixBonus << endl;
    cout << "Salary: " << salary << endl;
}
