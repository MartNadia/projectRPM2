#pragma once
#include "Employee.h"

#pragma once
#include "Employee.h"
#include "WorkBaseTime.h"

class Personal : public Employee, public WorkBaseTime {
private:
    double hourlyRate;
    double salary;
public:
    Personal(size_t id, const std::string& name, size_t worktime, double hourlyRate);
    double calculateSalary() override;
    double calcBase(double hourlyRate, size_t worktime) override;
    double calcBonus() override;
    double getHourlyRate() const;
    void setHourlyRate(double hourlyRate);
    EmployeeType getEmployeeType() const override {
        return EmployeeType::PERSONAL;
    }
    void print() const override;
};
