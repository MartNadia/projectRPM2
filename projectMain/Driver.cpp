#include "Driver.h"
#include <iostream> // Нужно для std::cout
using namespace std;

Driver::Driver(unsigned __int64 id, const string& name, unsigned __int64 worktime, double hourlyRate, double nightHourBonus, unsigned __int64 nightHours)
    : Employee(id, name, worktime), hourlyRate(hourlyRate), nightHourBonus(nightHourBonus), nightHours(nightHours){
}

double Driver::calculateSalary() {
    return calcBase(hourlyRate, getWorktime()) + calcBonus();
}

double Driver::calcBase(double hourlyRate, unsigned __int64 worktime) {
    return hourlyRate * worktime;
}

double Driver::calcBonus() {
    return nightHours * (hourlyRate + nightHourBonus);
}

double Driver::getHourlyRate() const {
    return hourlyRate;
}

void Driver::setHourlyRate(double hourlyRate) {
    this->hourlyRate = hourlyRate;
}

double Driver::getNightHourBonus() const {
    return nightHourBonus;
}

void Driver::setNightHourBonus(double nightHourBonus) {
    this->nightHourBonus = nightHourBonus;
}

unsigned __int64 Driver::getNightHours() const {
    return nightHours;
}

void Driver::setNightHours(unsigned __int64 nightHours) {
    this->nightHours = nightHours;
}

void Driver::print() const {
    Employee::print();
    cout << "Hourly Rate: " << hourlyRate << endl;
    cout << "Night Hour Bonus: " << nightHourBonus << endl;
    cout << "Night Hours: " << nightHours << endl;
}