#include "Employee.h"
#include <iostream>
#include <iomanip>

using namespace std;

Employee::Employee(const string& n, int a, const string& p)
    : Name(n), Age(a), Position(p) {
}

HourlyEmployee::HourlyEmployee(const string& n, int a, const string& p, double Worked, double Rate)
    : Employee(n, a, p), hourlyRate(Rate), hoursWorked(Worked) {
}

Employee::Type HourlyEmployee::getType() const {
    return Employee::Type::HourlyEmployee;
}

void HourlyEmployee::Show() const {
    cout << "Тип: Почасовой сотрудник" << endl;
    cout << "Имя: " << Name << endl;
    cout << "Возраст: " << Age << endl;
    cout << "Должность: " << Position << endl;
    cout << "Отработанные часы: " << hoursWorked << endl;
    cout << "Почасовая ставка: " << hourlyRate << endl;
    cout << "Зарплата: " << fixed << setprecision(2) << calculateSalary() << " руб." << endl;
}

double HourlyEmployee::calculateSalary() const {
    return hoursWorked * hourlyRate * 30;
}

SalariedEmployee::SalariedEmployee(const string& n, int a, const string& p, double Salary)
    : Employee(n, a, p), MonthlySalary(Salary) {
}

Employee::Type SalariedEmployee::getType() const {
    return Employee::Type::SalariedEmployee;
}

void SalariedEmployee::Show() const {
    cout << "Тип: Штатный сотрудник" << endl;
    cout << "Имя: " << Name << endl;
    cout << "Возраст: " << Age << endl;
    cout << "Должность: " << Position << endl;
    cout << "Оклад: " << MonthlySalary << endl;
    cout << "Зарплата: " << fixed << setprecision(2) << calculateSalary() << " руб." << endl;
}

double SalariedEmployee::calculateSalary() const {
    return MonthlySalary;
}
