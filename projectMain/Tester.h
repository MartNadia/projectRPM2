#pragma once
#include "Employee.h"
#include "WorkBaseTime.h"
#include "ProjectBudget.h"

class Tester : public Employee, public WorkBaseTime, public ProjectBudget {
private:
    double hourlyRate;
    double projectContribution;
    double projectBudget;
    size_t bugsFound;
    double bugFixBonus;

public:
    Tester(size_t id, const string& name, size_t worktime, double hourlyRate, double projectContribution, double projectBudget, size_t bugsFound, double bugFixBonus);
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
    size_t getBugsFound() const;
    void setBugsFound(size_t bugsFound);
    double getBugFixBonus() const;
    void setBugFixBonus(double bugFixBonus);
    void print() const override;
};