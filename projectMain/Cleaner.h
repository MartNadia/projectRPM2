#pragma once
#include "Employee.h"
#include "WorkBaseTime.h"

class Cleaner : public Employee, public WorkBaseTime {
private:
    double hourlyRate;
public:
    Cleaner(size_t id, const string& name, size_t worktime, double hourlyRate);
    double calculateSalary() override;
    double calcBase(double hourlyRate, size_t worktime) override;
    double calcBonus() override;
    double getHourlyRate() const;
    void setHourlyRate(double hourlyRate);
    void print() const override;
};