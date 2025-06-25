#pragma once
class ProjectBudget {
public:
    virtual double calcBudgetPart(double projectBudget, double personalContribution) = 0;
    virtual double calcProAdditions() = 0;
    virtual ~ProjectBudget() {};
};
