#pragma once
#include "Employee.h"
#include "ProjectBudget.h"
#include "Heading.h"

class ProjectManager : public Employee, public ProjectBudget, public Heading {
private:
    double projectBudget;
    size_t numProjectMembers;
    double headingBonusFactor;

public:
    ProjectManager(size_t id, const string& name, size_t worktime, double projectBudget, size_t numProjectMembers, double headingBonusFactor);
    double calculateSalary() override;
    double calcBudgetPart(double projectBudget, double personalContribution) override;
    double calcProAdditions() override;
    double calcHeadingBonus(size_t numSubordinates) override;
    double getProjectBudget() const;
    void setProjectBudget(double projectBudget);
    size_t getNumProjectMembers() const;
    void setNumProjectMembers(size_t numProjectMembers);
    double getHeadingBonusFactor() const;
    void setHeadingBonusFactor(double headingBonusFactor);
    void print() const override;
};