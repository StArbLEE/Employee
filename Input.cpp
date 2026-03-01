#include "input.h"
#include "Employee.h"
#include <limits>
#include <algorithm>

using namespace std;

bool isDigitsOnly(const string& str) {
    if (str.empty()) return false;
    return all_of(str.begin(), str.end(), ::isdigit);
}

bool isLettersOnly(const string& str) {
    if (str.empty()) return false;
    for (char ch : str) {
        if (!isalpha(ch)) {
            return false;
        }
    }
    return true;
}
shared_ptr<SalariedEmployee> createSalariedEmployee() {
    string Name, Position;
    int Age;
    double MonthlySalary;
    string input;

    cout << "Введите имя работника (только английские буквы): ";
    while (true) {
        getline(cin, Name);
        if (isLettersOnly(Name)) break;
        cout << "Введите только буквы: ";
    }

    cout << "Введите возраст работника (от 18 до 40 лет): ";
    while (true) {
        getline(cin, input);
        if (isDigitsOnly(input)) {
            Age = stoi(input);
            if (Age >= 18 && Age <= 40) break;
            cout << "Возраст вне допустимого диапазона. Попробуйте снова.\n";
        }
        else {
            cout << "Некорректный ввод. Попробуйте снова.\n";
        }
    }

    cout << "Введите специальность работника (только английские буквы): ";
    while (true) {
        getline(cin, Position);
        if (isLettersOnly(Position)) break;
        cout << "Введите только буквы: ";
    }

    cout << "Введите ежемесячную зарплату работника (от 30000 до 500000): ";
    while (true) {
        getline(cin, input);
        if (isDigitsOnly(input)) {
            MonthlySalary = stod(input);
            if (MonthlySalary >= 30000 && MonthlySalary <= 500000) break;
            cout << "Зарплата вне допустимого диапазона. Попробуйте снова.\n";
        }
        else {
            cout << "Некорректный ввод. Попробуйте снова.\n";
        }
    }

    return make_shared<SalariedEmployee>(Name, Age, Position, MonthlySalary);
}

shared_ptr<HourlyEmployee> createHourlyEmployee() {
    string Name, Position, input;
    int Age;
    double hoursWorked, hourlyRate;

    cout << "Введите имя работника (только английсикие буквы): ";
    while (true) {
        getline(cin, Name);
        if (isLettersOnly(Name)) break;
        cout << "Введите только английские буквы: ";
    }

    cout << "Введите возраст работника (от 18 до 40 лет): ";
    while (true) {
        getline(cin, input);
        if (isDigitsOnly(input)) {
            Age = stoi(input);
            if (Age >= 18 && Age <= 40) break;
            cout << "Возраст вне диапазона, попробуйте снова.\n";
        }
        else {
            cout << "Некорректный ввод, попробуйте снова.\n";
        }
    }

    cout << "Введите специальность работника (только буквы): ";
    while (true) {
        getline(cin, Position);
        if (isLettersOnly(Position)) break;
        cout << "Введите только буквы: ";
    }

    cout << "Введите отработанные часы работника (от 4 до 12): ";
    while (true) {
        getline(cin, input);
        try {
            hoursWorked = stod(input);
            if (hoursWorked >= 4 && hoursWorked <= 12) break;
            cout << "Часы вне диапазона, попробуйте снова.\n";
        }
        catch (...) {
            cout << "Некорректный ввод, попробуйте снова.\n";
        }
    }

    cout << "Введите часовую ставку работника (от 110 до 500): ";
    while (true) {
        getline(cin, input);
        try {
            hourlyRate = stod(input);
            if (hourlyRate >= 110 && hourlyRate <= 500) break;
            cout << "Ставка вне диапазона, попробуйте снова.\n";
        }
        catch (...) {
            cout << "Некорректный ввод, попробуйте снова.\n";
        }
    }

    return make_shared<HourlyEmployee>(Name, Age, Position, hoursWorked, hourlyRate);
}
