#include "ProjectManager.h"
using namespace std;

ProjectManager::ProjectManager(size_t id, const string& name, size_t worktime, double projectBudget, size_t numProjectMembers, double headingBonusFactor)
    : Employee(id, name, worktime), projectBudget(projectBudget), numProjectMembers(numProjectMembers), headingBonusFactor(headingBonusFactor) {
    salary = calculateSalary();
}

double ProjectManager::calculateSalary() {
    return calcBudgetPart(projectBudget, 0.22) + calcProAdditions() + calcHeadingBonus(numProjectMembers);
}

double ProjectManager::calcBudgetPart(double projectBudget, double personalContribution) {
    return projectBudget * personalContribution;
}

double ProjectManager::calcProAdditions() {
    return 0.0;
}

double ProjectManager::calcHeadingBonus(size_t numSubordinates) {
    return numSubordinates * headingBonusFactor;
}

double ProjectManager::getProjectBudget() const {
    return projectBudget;
}

void ProjectManager::setProjectBudget(double projectBudget) {
    this->projectBudget = projectBudget;
}

size_t ProjectManager::getNumProjectMembers() const {
    return numProjectMembers;
}

void ProjectManager::setNumProjectMembers(size_t numProjectMembers) {
    this->numProjectMembers = numProjectMembers;
}

double ProjectManager::getHeadingBonusFactor() const {
    return headingBonusFactor;
}

void ProjectManager::setHeadingBonusFactor(double headingBonusFactor) {
    this->headingBonusFactor = headingBonusFactor;
}

void ProjectManager::print() const {
    Employee::print();
    cout << "Project Budget: " << projectBudget << endl;
    cout << "Number of Project Members: " << numProjectMembers << endl;
    cout << "Heading Bonus Factor: " << headingBonusFactor << endl;
    cout << "Salary: " << salary << endl;
}
