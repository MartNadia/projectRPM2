#include "SeniorManager.h"
using namespace std;

SeniorManager::SeniorManager(size_t id, const string& name, size_t worktime, const vector<double>& projectBudgets, size_t totalEmployees, double headingBonusFactor)
    : Employee(id, name, worktime), projectBudgets(projectBudgets), totalEmployees(totalEmployees), headingBonusFactor(headingBonusFactor) {

    salary = calculateSalary();
}

double SeniorManager::calculateSalary() {
    return (0.15*getTotalBudget()) + calcHeadingBonus(totalEmployees);
}

double SeniorManager::calcHeadingBonus(size_t numSubordinates) {
    return numSubordinates * headingBonusFactor;
}

void SeniorManager::addProjectBudget(double budget) {
    projectBudgets.push_back(budget);
}

double SeniorManager::getTotalBudget() const {
    double totalBudget = 0.0;
    for (double budget : projectBudgets) {
        totalBudget += budget;
    }
    return totalBudget;
}

size_t SeniorManager::getTotalEmployees() const {
    return totalEmployees;
}

void SeniorManager::setTotalEmployees(size_t totalEmployees) {
    this->totalEmployees = totalEmployees;
}

double SeniorManager::getHeadingBonusFactor() const {
    return headingBonusFactor;
}

void SeniorManager::setHeadingBonusFactor(double headingBonusFactor) {
    this->headingBonusFactor = headingBonusFactor;
}

void SeniorManager::print() const {
    Employee::print();
    cout << "Total Budget: " << getTotalBudget() << endl;
    cout << "Total Employees: " << totalEmployees << endl;
    cout << "Heading Bonus Factor: " << headingBonusFactor << endl;
    cout << "Salary: " << salary << endl;

}
