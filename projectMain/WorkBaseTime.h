#pragma once
class WorkBaseTime {
public:
    virtual double calcBase(double hourlyRate, size_t worktime) = 0;
    virtual double calcBonus() = 0;
    virtual ~WorkBaseTime() {};
};
