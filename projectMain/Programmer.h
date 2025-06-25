#pragma once
#include "Employee.h"
#include "WorkBaseTime.h"
#include "ProjectBudget.h"

class Programmer : public Employee, public WorkBaseTime, public ProjectBudget {
private:
    double hourlyRate;
    double projectContribution;
    double projectBudget;
    double earlyCompletionBonus;

public:
    Programmer(size_t id, const std::string& name, size_t worktime, double hourlyRate, double projectContribution, double projectBudget, double earlyCompletionBonus);
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
    double getEarlyCompletionBonus() const;
    void setEarlyCompletionBonus(double earlyCompletionBonus);
    void print() const override;
};