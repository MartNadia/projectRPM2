#include "Personal.h"
using namespace std;

Personal::Personal(size_t id, const string& name, size_t worktime, double hourlyRate)
    : Employee(id, name, worktime), hourlyRate(hourlyRate) {
}

double Personal::calculateSalary(){
    return calcBase(hourlyRate, getWorktime()) + calcBonus();
}

double Personal::calcBase(double hourlyRate, size_t worktime){
    return hourlyRate * worktime;
}

double Personal::calcBonus() {
    return 0.0;
}

double Personal::getHourlyRate() const {
    return hourlyRate;
}

void Personal::setHourlyRate(double hourlyRate) {
    this->hourlyRate = hourlyRate;
}

void Personal::print() const {
    Employee::print();
    cout << "Hourly Rate: " << hourlyRate << endl;
}