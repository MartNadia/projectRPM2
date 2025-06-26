#pragma once
#include "Employee.h"
#include "WorkBaseTime.h"
#include "ProjectBudget.h"

class Engineer : public Employee, public WorkBaseTime, public ProjectBudget {
private:
    double hourlyRate;
    double projectContribution;
    double projectBudget;
    double salary;

public:
    Engineer(size_t id, const string& name, size_t worktime, double hourlyRate, double projectContribution, double projectBudget);
    double calculateSalary() override;
    double calcBase(double hourlyRate, size_t worktime) override;
    double calcBonus() override;
    double calcBudgetPart(double projectBudget, double personalContribution) override;
    double calcProAdditions() override;
    double getHourlyRate() const;
    void setHourlyRate(double hourlyRate);
    double getProjectContribution() const;
    void setProjectContribution(double projectContribution);
    double getProjectBudget() const;
    void setProjectBudget(double projectBudget);
    EmployeeType getEmployeeType() const override {
        return EmployeeType::ENGINEER;
    }
    void print() const override;
};
