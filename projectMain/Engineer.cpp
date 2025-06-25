#include "Engineer.h"
using namespace std;

Engineer::Engineer(size_t id, const string& name, size_t worktime, double hourlyRate, double projectContribution, double projectBudget)
    : Employee(id, name, worktime), hourlyRate(hourlyRate), projectContribution(projectContribution), projectBudget(projectBudget) {}

double Engineer::calculateSalary() {
    return calcBase(hourlyRate, getWorktime()) + calcBonus() + calcBudgetPart(projectBudget, projectContribution) + calcProAdditions();
}


double Engineer::calcBase(double hourlyRate, size_t worktime) {
    if (worktime <= 200) {
        return hourlyRate * worktime;
    }
    else {
        return hourlyRate * 200;
    }
}

double Engineer::calcBonus() {
    if (getWorktime() > 200) {
        return (hourlyRate + 500) * (getWorktime() - 200);
    }
    return 0.0;
}

double Engineer::calcBudgetPart(double projectBudget, double personalContribution) {
    return projectBudget * personalContribution;
}

double Engineer::calcProAdditions() {
    return 0.0;
}

double Engineer::getHourlyRate() const {
    return hourlyRate;
}

void Engineer::setHourlyRate(double hourlyRate) {
    this->hourlyRate = hourlyRate;
}

double Engineer::getProjectContribution() const {
    return projectContribution;
}

void Engineer::setProjectContribution(double projectContribution) {
    this->projectContribution = projectContribution;
}

double Engineer::getProjectBudget() const {
    return projectBudget;
}

void Engineer::setProjectBudget(double projectBudget) {
    this->projectBudget = projectBudget;
}

void Engineer::print() const {
    Employee::print();
    cout << "Hourly Rate: " << hourlyRate << endl;
    cout << "Project Contribution: " << projectContribution << endl;
    cout << "Project Budget: " << projectBudget << endl;
}