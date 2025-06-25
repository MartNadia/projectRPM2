#pragma once
#include <iostream>
#include <string> 
using namespace std;


enum class EmployeeType {
	PERSONAL,
	ENGINEER,
	CLEANER,
	DRIVER,
	PROGRAMMER,
	TESTER,
	TEAMLEADER,
	PROJECTMANAGER,
	SENIORMANAGER,
	UNKNOWN // Default Value
};

class Employee
{
protected:
	size_t id;
	string name;
	size_t worktime;
	double hourlyRate;

public:
	Employee();
	Employee(size_t id, const string& name, size_t worktime);

	virtual ~Employee() {};

	size_t getId() const;
	string getName() const;
	size_t getWorktime() const;
	double getHourlyRate() const;


	void setId(size_t id);
	void setName(const string& name);
	void setWorktime(size_t worktime);
	void setHourlyRate(double payment);

	virtual double calculateSalary() = 0;

	virtual void print() const;
};

