#include "Test.h"
#include "Filework.h"
#include "Employee.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>

using namespace std;

bool is_file_empty(const string& path) {
    ifstream file(path);
    return file.peek() == ifstream::traits_type::eof();
}

int convertToInt(const string& s) {
    return stoi(s);
}
double convertToDouble(const string& s) {
    return stod(s);
}

bool readDoubleField(ifstream& file, double& var, int& line_num) {
    string line;
    if (!getline(file, line)) {
        return false;
    }
    line_num++;
    try {
        var = convertToDouble(line);
        return true;
    }
    catch (...) {
        return false;
    }
}


string convertToString(const string& s) {
    return s;
}
bool readStringField(ifstream& file, string& var, int& line_num) {
    string line;
    if (!getline(file, line)) {
        return false;
    }
    line_num++;
    try {
        var = convertToString(line);
        return true;
    }
    catch (...) {
        return false;
    }
}

bool readIntField(ifstream& file, int& var, int& line_num) {
    string line;
    if (!getline(file, line)) {
        return false;
    }
    line_num++;
    try {
        var = convertToInt(line);
        return true;
    }
    catch (...) {
        return false;
    }
}
bool test_employee_input(vector<shared_ptr<Employee>>& employees, const string& path) {
    ifstream file(path);
    if (!file.is_open()) {
        cout << "Не удалось открыть файл " << path << endl;
        return false;
    }

    if (is_file_empty(path)) {
        file.close();
        return false;
    }

    string line;
    int line_num = 0;

    while (getline(file, line)) {
        line_num++;
        if (line.empty()) continue;

        string type = line;
        string name, position;
        int age;

        if (!readStringField(file, name, line_num)) {
            file.close();
            return false;
        }

        if (!readIntField(file, age, line_num)) {
            file.close();
            return false;
        }

        if (!readStringField(file, position, line_num)) {
            file.close();
            return false;
        }

        if (type == "HourlyEmployee") {
            double hoursWorked, hourlyRate;

            if (!readDoubleField(file, hoursWorked, line_num)) {
                file.close();
                return false;
            }

            if (!readDoubleField(file, hourlyRate, line_num)) {
                file.close();
                return false;
            }

            employees.push_back(make_shared<HourlyEmployee>(name, age, position, hoursWorked, hourlyRate));
        }
        else if (type == "SalariedEmployee") {
            double monthlySalary;

            if (!readDoubleField(file, monthlySalary, line_num)) {
                file.close();
                return false;
            }

            employees.push_back(make_shared<SalariedEmployee>(name, age, position, monthlySalary));
        }
        else {
            cout << "Неизвестный тип сотрудника на строке " << line_num << ": " << type << endl;
            file.close();
            return false;
        }

        if (!file.eof()) {
            getline(file, line);
            line_num++;
        }
    }

    file.close();
    return true;
}
void run_all_tests() {
    bool all_ok = true;
    vector<shared_ptr<Employee>> test_employees;
    bool loaded;

    // Тест 1: Корректные данные (HourlyEmployee)
    test_employees.clear();
    if (!test_employee_input(test_employees, "test1.txt") || test_employees.size() != 1) {
        all_ok = false;
        cout << "Тест 1: Ожидался 1 HourlyEmployee, но данные некорректны или количество не совпадает.\n";
    }

    // Тест 2: Некорректные данные
    test_employees.clear();
    loaded = test_employee_input(test_employees, "test2.txt");
    if (loaded) {
        all_ok = false;
        cout << "Тест 2: Ожидались ошибки при загрузке, но данные загружены успешно.\n";
    }

    // Тест 3: Пустой файл
    test_employees.clear();
    if (!is_file_empty("test3.txt")) {
        all_ok = false;
        cout << "Тест 3: Ожидался пустой файл, но файл содержит данные.\n";
    }

    // Тест 4: Проверка количества SalariedEmployee
    test_employees.clear();
    if (test_employee_input(test_employees, "test4.txt")) {
        int salary_count = 0;
        for (const auto& emp : test_employees) {
            if (dynamic_pointer_cast<SalariedEmployee>(emp)) {
                salary_count++;
            }
        }
        if (salary_count != 2) { // ожидание: 2 salaried сотрудника в test4.txt
            all_ok = false;
            cout << "Тест 4: Ожидалось 2 SalariedEmployee, получено: " << salary_count << endl;
        }
    }
    else {
        all_ok = false;
        cout << "Тест 4: Не удалось загрузить сотрудников из файла test4.txt\n";
    }

    // Тест 5: Проверка параметров HourlyEmployee
    test_employees.clear();
    if (test_employee_input(test_employees, "test5.txt")) {
        for (const auto& emp : test_employees) {
            if (auto hourly = dynamic_pointer_cast<HourlyEmployee>(emp)) {
                if (hourly->getHoursWorked() < 0 || hourly->getHourlyRate() <= 0) {
                    all_ok = false;
                    cout << "Тест 5: HourlyEmployee с некорректными данными.\n";
                    break;
                }
            }
        }
    }
    else {
        all_ok = false;
        cout << "Тест 5: Не удалось загрузить сотрудников из файла test5.txt\n";
    }

    // Вывод финального результата
    if (all_ok) {
        cout << "ТЕСТЫ УСПЕШНО ПРОЙДЕНЫ!\n";
    }
    else {
        cout << "ЕСТЬ ОШИБКИ В ТЕСТАХ!\n";
    }
}
