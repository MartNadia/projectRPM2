#include "pch.h"
#include "CppUnitTest.h"
#include "Personal.h"
#include "Engineer.h"
#include "Cleaner.h"
#include "Driver.h"
#include "Programmer.h"
#include "Tester.h"
#include "TeamLeader.h"
#include "ProjectManager.h"
#include "SeniorManager.h"
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1 
{
    TEST_CLASS(PersonalTests)
    {
    public:

        TEST_METHOD(CalculateSalary)
        {
            Personal personal(1, "John Doe", 40, 200.0);
            Assert::AreEqual(8000.0, personal.calculateSalary(), 0.001);// 40 hours * 200 per/hour
        }

        TEST_METHOD(SetWorktime)
        {
            Personal personal(1, "John Doe", 40, 200.0);
            personal.setWorktime(50);
            Assert::AreEqual(10000.0, personal.calculateSalary(), 0.001);
        }
    };

    TEST_CLASS(EngineerTests)
    {
    public:
        TEST_METHOD(CalculateSalary)
        {
            Engineer engineer(2, "Jane Smith", 210, 450.0, 0.1, 100000.0);// Contribution = 10%, Budget = 100,000
            Assert::AreEqual(109500.0, engineer.calculateSalary(), 0.001); // Salary = (200 hours * 450 per/hour + (10 hours * 450+500 per/hour)) + (10% * 100,000) = 109500
        }
    };

    TEST_CLASS(CleanerTests)
    {
    public:
        TEST_METHOD(CalculateSalary)
        {
            Cleaner cleaner(3, "Alice Clean", 170, 250.0);
            Assert::AreEqual(44500.0, cleaner.calculateSalary(), 0.001);// Salary = (160 hours * 250 per/hour + (10 hours * 250+200 per/hour))
        }

        TEST_METHOD(SetWorktime)
        {
            Cleaner cleaner(3, "Alice Clean", 170, 250.0);
            cleaner.setWorktime(10);
            Assert::AreEqual(2500.0, cleaner.calculateSalary(), 0.001);
        }
    };

    TEST_CLASS(DriverTests)
    {
    public:
        TEST_METHOD(CalculateSalary)
        {
            Driver driver(4, "Bob Drive", 40, 280.0, 150.0, 20);
            Assert::AreEqual(19800.0, driver.calculateSalary(), 0.001);// (40 * 280) + (20 * 430) = 19,800
        }
    };

    TEST_CLASS(ProgrammerTests)
    {
    public:
        TEST_METHOD(CalculateSalary)
        {
            Programmer programmer(5, "Charlie Code", 240, 350.0, 0.2, 500000.0, 10000.0);
            Assert::AreEqual(194000.0, programmer.calculateSalary(), 0.001);
            // Salary = (240 * 350) + (20% * 500,000) + 10000 = 194,000
        }
    };

    TEST_CLASS(TesterTests)
    {
    public:
        TEST_METHOD(CalculateSalary)
        {
            Tester tester(6, "David Test", 200, 320.0, 0.15, 600000.0, 10, 1000.0);
            Assert::AreEqual(164000.0, tester.calculateSalary(), 0.001);
            // Salary = (200 * 320) + (15% * 600,000) + (10 * 1000) = 164,000
        }
    };

    TEST_CLASS(TeamLeaderTests)
    {
    public:
        TEST_METHOD(CalculateSalary)
        {
            TeamLeader teamLeader(7, "Eve Lead", 290, 300.0, 0.25, 800000.0, 15, 2000.0);
            Assert::AreEqual(322000.0, teamLeader.calculateSalary(), 0.001);

            // Salary = (290 * 300) + (25% * 800,000) + (10 * 2000) + (5,000 * 3,000) = 322,000
        }
    };

    TEST_CLASS(ProjectManagerTests)
    {
    public:
        TEST_METHOD(CalculateSalary)
        {
            ProjectManager projectManager(8, "Frank Manage", 230, 1000000.0, 10, 2000.0);
            Assert::AreEqual(240000.0, projectManager.calculateSalary(), 0.001);
            // Salary = 22% * 1000000 + (10 * 2000) = 240,000
        }
    };

    TEST_CLASS(SeniorManagerTests)
    {
    public:
        TEST_METHOD(CalculateSalary)
        {
            std::vector<double> budgets = { 500000.0, 750000.0, 1000000.0 }; // 500,000 + 750,000 + 1,000,000
            SeniorManager seniorManager(9, "Grace Senior", 300, budgets, 25, 3000.0);
            Assert::AreEqual(412500.0, seniorManager.calculateSalary(), 0.001);
            // Salary = (15% * (500,000 + 750,000 + 1,000,000)) + (25 * 3000) = 412,500
        }
    };
}
