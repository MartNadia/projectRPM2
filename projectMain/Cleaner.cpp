#include "Cleaner.h"
using namespace std;

Cleaner::Cleaner(size_t id, const string& name, size_t worktime, double hourlyRate)
    : Employee(id, name, worktime), hourlyRate(hourlyRate) {
    salary = calculateSalary();
}

double Cleaner::calculateSalary() {
    return calcBase(hourlyRate, getWorktime()) + calcBonus();
}

double Cleaner::calcBase(double hourlyRate, size_t worktime) {
    if (worktime <= 160) {
        return hourlyRate * worktime;
    }
    else {
        return hourlyRate * 160;
    }
}

double Cleaner::calcBonus() {
    if (getWorktime() > 160) {
        return (hourlyRate+200) * (getWorktime() - 160);
    }
    return 0.0;
}

double Cleaner::getHourlyRate() const {
    return hourlyRate;
}

void Cleaner::setHourlyRate(double hourlyRate) {
    this->hourlyRate = hourlyRate;
}

void Cleaner::print() const {
    Employee::print();
    cout << "Hourly Rate: " << hourlyRate << endl;
    cout << "Salary: " << salary << endl;
}
