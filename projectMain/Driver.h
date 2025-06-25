#pragma once
#include "Employee.h"
#include "WorkBaseTime.h"

class Driver : public Employee, public WorkBaseTime {
private:
    double hourlyRate;
    double nightHourBonus;
    size_t nightHours;

public:
    Driver(size_t id, const string& name, size_t worktime, double hourlyRate, double nightHourBonus, size_t nightHours);
    double calculateSalary() override;
    double calcBase(double hourlyRate, size_t worktime) override;
    double calcBonus() override;
    double getHourlyRate() const;
    void setHourlyRate(double hourlyRate);
    double getNightHourBonus() const;
    void setNightHourBonus(double nightHourBonus);
    size_t getNightHours() const;
    void setNightHours(size_t nightHours);
    void print() const override;
};