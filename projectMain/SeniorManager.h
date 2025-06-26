#pragma once
#include "Employee.h"
#include "Heading.h"

#include <vector>

class SeniorManager : public Employee, public Heading {
private:
    vector<double> projectBudgets;
    size_t totalEmployees;
    double headingBonusFactor;
    double salary;


public:
    SeniorManager(size_t id, const string& name, size_t worktime, const vector<double>& projectBudgets, size_t totalEmployees, double headingBonusFactor);
    double calculateSalary() override;
    double calcHeadingBonus(size_t numSubordinates) override;
    void addProjectBudget(double budget);
    double getTotalBudget() const;
    size_t getTotalEmployees() const;
    void setTotalEmployees(size_t totalEmployees);
    double getHeadingBonusFactor() const;
    void setHeadingBonusFactor(double headingBonusFactor);
    EmployeeType getEmployeeType() const override{
        return EmployeeType::SENIORMANAGER;
    };
    void print() const override;

};
