#pragma once
#include "Employee.h"
#include "WorkBaseTime.h"
#include "ProjectBudget.h"
#include "Heading.h"

class TeamLeader : public Employee, public WorkBaseTime, public ProjectBudget, public Heading {
private:
    double hourlyRate;
    double projectContribution;
    double projectBudget;
    size_t numSubordinates;
    double headingBonusFactor;
    double salary;

public:
    TeamLeader(size_t id, const string& name, size_t worktime, double hourlyRate, double projectContribution, double projectBudget, size_t numSubordinates, double headingBonusFactor);
    double calculateSalary() override;
    double calcBase(double hourlyRate, size_t worktime) override;
    double calcBonus() override;
    double calcBudgetPart(double projectBudget, double personalContribution) override;
    double calcProAdditions() override;
    double calcHeadingBonus(size_t numSubordinates) override;
    double getHourlyRate() const;
    void setHourlyRate(double hourlyRate);
    double getProjectContribution() const;
    void setProjectContribution(double projectContribution);
    double getProjectBudget() const;
    void setProjectBudget(double projectBudget);
    size_t getNumSubordinates() const;
    void setNumSubordinates(size_t numSubordinates);
    double getHeadingBonusFactor() const;
    void setHeadingBonusFactor(double headingBonusFactor);
    EmployeeType getEmployeeType() const override {
        return EmployeeType::TEAMLEADER;
    }
    void print() const override;
};
