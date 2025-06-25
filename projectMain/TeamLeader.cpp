#include "TeamLeader.h"
using namespace std;

TeamLeader::TeamLeader(size_t id, const string& name, size_t worktime, double hourlyRate, double projectContribution, double projectBudget, size_t numSubordinates, double headingBonusFactor)
    : Employee(id, name, worktime), hourlyRate(hourlyRate), projectContribution(projectContribution), projectBudget(projectBudget), numSubordinates(numSubordinates), headingBonusFactor(headingBonusFactor) {}

double TeamLeader::calculateSalary() {
    return calcBase(hourlyRate, getWorktime()) + calcBonus() + calcBudgetPart(projectBudget, projectContribution) + calcProAdditions() + calcHeadingBonus(numSubordinates);
}

double TeamLeader::calcBase(double hourlyRate, size_t worktime) {
    return hourlyRate * worktime;
}

double TeamLeader::calcBonus() {
    if (numSubordinates > 10) {
        return (numSubordinates-10)*1000;
    }
    return 0.0;
    
}

double TeamLeader::calcBudgetPart(double projectBudget, double personalContribution) {
    return projectBudget * personalContribution;
}

double TeamLeader::calcProAdditions() {
    return 0.0;
}

double TeamLeader::calcHeadingBonus(size_t numSubordinates) {
    return numSubordinates * headingBonusFactor;
}

double TeamLeader::getHourlyRate() const {
    return hourlyRate;
}

void TeamLeader::setHourlyRate(double hourlyRate) {
    this->hourlyRate = hourlyRate;
}

double TeamLeader::getProjectContribution() const {
    return projectContribution;
}

void TeamLeader::setProjectContribution(double projectContribution) {
    this->projectContribution = projectContribution;
}

double TeamLeader::getProjectBudget() const {
    return projectBudget;
}

void TeamLeader::setProjectBudget(double projectBudget) {
    this->projectBudget = projectBudget;
}

size_t TeamLeader::getNumSubordinates() const {
    return numSubordinates;
}

void TeamLeader::setNumSubordinates(size_t numSubordinates) {
    this->numSubordinates = numSubordinates;
}

double TeamLeader::getHeadingBonusFactor() const {
    return headingBonusFactor;
}

void TeamLeader::setHeadingBonusFactor(double headingBonusFactor) {
    this->headingBonusFactor = headingBonusFactor;
}

void TeamLeader::print() const {
    Employee::print();
    cout << "Hourly Rate: " << hourlyRate << endl;
    cout << "Project Contribution: " << projectContribution << endl;
    cout << "Project Budget: " << projectBudget << endl;
    cout << "Number of Subordinates: " << numSubordinates << endl;
    cout << "Heading Bonus Factor: " << headingBonusFactor << endl;
}