#pragma once
#include <string>
#include <memory>

using namespace std;

class Employee {
protected:
    string Name;
    int Age;
    string Position;
public:
    enum class Type { HourlyEmployee, SalariedEmployee };
    Employee(const string& n, int a, const string& p);  // конструктор принимает const ссылки
    virtual ~Employee() = default;
    virtual Type getType() const = 0;
    virtual double calculateSalary() const = 0;
    virtual void Show() const = 0;

    const string& getName() const { return Name; }    // возвращаем const ссылку
    int getAge() const { return Age; }
    const string& getPosition() const { return Position; }
};

class SalariedEmployee : public Employee {
    double MonthlySalary;

public:
    SalariedEmployee(const string& n, int a, const string& p, double Salary);
    Type getType() const override;
    void Show() const override;
    double calculateSalary() const override;

    double getMonthlySalary() const { return MonthlySalary; }
};

class HourlyEmployee : public Employee {
    double hoursWorked;
    double hourlyRate;
public:
    HourlyEmployee(const string& n, int a, const string& p, double Worked, double Rate);
    Type getType() const override;
    void Show() const override;
    double calculateSalary() const override;

    double getHoursWorked() const { return hoursWorked; }    // методы const не обязательны, но лучше добавить
    double getHourlyRate() const { return hourlyRate; }
};
