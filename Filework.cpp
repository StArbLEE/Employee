#include "Filework.h"
#include "Input.h"
#include "Employee.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>
#include <memory>

using namespace std;

bool isValidFileName(const string& filename) {
    if (filename.empty()) return false;
    string badChars = "<>\"|?*";

    if (filename[0] == ' ' || filename[0] == '.') {
        return false;
    }

    for (size_t i = 0; i < filename.size(); ++i) {
        char ch = filename[i];
        if (badChars.find(ch) != string::npos) return false;
        if (ch == ':' && i != 1) return false;
    }

    const vector<string> reservedNames = {
        "CON", "PRN", "AUX", "NUL",
        "COM1", "COM2", "COM3", "COM4", "COM5", "COM6", "COM7", "COM8", "COM9",
        "LPT1", "LPT2", "LPT3", "LPT4", "LPT5", "LPT6", "LPT7", "LPT8", "LPT9"
    };

    size_t lastSlash = filename.find_last_of("\\/");
    string fileNameWithoutPath = (lastSlash == string::npos) ? filename : filename.substr(lastSlash + 1);
    size_t dotPosition = fileNameWithoutPath.find_last_of('.');
    if (dotPosition != string::npos) {
        fileNameWithoutPath = fileNameWithoutPath.substr(0, dotPosition);
    }

    string upperFileName;
    for (char c : fileNameWithoutPath) {
        upperFileName += static_cast<char>(toupper(c));
    }

    for (const string& reservedName : reservedNames) {
        if (upperFileName == reservedName) return false;
    }

    return true;
}

bool canWriteToFile(const string& filename) {
    ofstream file(filename, ios::app);
    if (file.is_open()) {
        file.close();
        return true;
    }
    return false;
}

bool fileExists(const string& filename) {
    ifstream file(filename);
    return file.good();
}

bool saveEmployeesToFile(const string& filename, const vector<shared_ptr<Employee>>& employees) {
    if (!isValidFileName(filename)) {
        cout << "Недопустимое имя файла: " << filename << endl;
        return false;
    }

    if (employees.empty()) {
        cout << "Список сотрудников пуст." << endl;
        return false;
    }

    bool exists = fileExists(filename);
    if (exists && !canWriteToFile(filename)) {
        cout << "Нет прав на запись в файл: " << filename << endl;
        return false;
    }

    if (exists) {
        cout << "\nФайл " << filename << " уже существует." << endl;
        cout << static_cast<int>(FileOperationOption::OVERWRITE) << ". Перезаписать файл" << endl;
        cout << static_cast<int>(FileOperationOption::NEW_NAME) << ". Ввести новое имя" << endl;
        cout << static_cast<int>(FileOperationOption::CANCEL) << ". Отменить сохранение" << endl;
        cout << "Ваш выбор: ";

        int choice;
        if (!(cin >> choice)) {
            cout << "Ошибка ввода" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return false;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == static_cast<int>(FileOperationOption::NEW_NAME)) {
            string newFilename;
            cout << "Введите новое имя файла: ";
            getline(cin, newFilename);
            return saveEmployeesToFile(newFilename, employees);
        }
        else if (choice == static_cast<int>(FileOperationOption::CANCEL)) {
            cout << "Сохранение отменено." << endl;
            return false;
        }
    }

    ofstream file(filename, ios::out | ios::trunc);
    if (!file) {
        cout << "Не удалось открыть файл для записи: " << filename << endl;
        return false;
    }

    try {
        for (const auto& employee : employees) {
            switch (employee->getType()) {
            case Employee::Type::HourlyEmployee:
                file << "HourlyEmployee" << endl;
                break;
            case Employee::Type::SalariedEmployee:
                file << "SalariedEmployee" << endl;
                break;
            }

            file << employee->getName() << endl
                << employee->getAge() << endl
                << employee->getPosition() << endl;

            if (auto hourly = dynamic_pointer_cast<HourlyEmployee>(employee)) {
                file << hourly->getHoursWorked() << endl
                    << hourly->getHourlyRate() << endl;
            }
            else if (auto salaried = dynamic_pointer_cast<SalariedEmployee>(employee)) {
                file << salaried->getMonthlySalary() << endl;
            }

            file << endl;

            if (!file) {
                cout << "Ошибка записи в файл" << endl;
                file.close();
                remove(filename.c_str());
                return false;
            }
        }
    }
    catch (const exception&) {
        cout << "Ошибка при сохранении данных" << endl;
        file.close();
        remove(filename.c_str());
        return false;
    }

    file.close();
    cout << "Сотрудники успешно сохранены в файл: " << filename << endl;
    return true;
}

bool loadEmployeesFromFile(const string& filename, vector<shared_ptr<Employee>>& employees) {
    if (!fileExists(filename)) {
        cout << "Файл не найден: " << filename << endl;
        return false;
    }

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Не удалось открыть файл: " << filename << endl;
        return false;
    }

    if (file.peek() == ifstream::traits_type::eof()) {
        cout << "Файл пуст." << endl;
        file.close();
        return false;
    }

    vector<shared_ptr<Employee>> tempEmployees;
    string type;

    while (getline(file, type)) {
        string name, position;
        int age = 0;

        if (!getline(file, name) || !(file >> age) || file.get() != '\n' || !getline(file, position)) {
            cout << "Ошибка чтения данных сотрудника." << endl;
            file.close();
            return false;
        }

        if (type == "HourlyEmployee") {
            double hoursWorked = 0.0, hourlyRate = 0.0;
            if (!(file >> hoursWorked) || !(file >> hourlyRate)) {
                cout << "Ошибка чтения HourlyEmployee." << endl;
                file.close();
                return false;
            }
            file.ignore(numeric_limits<streamsize>::max(), '\n');
            tempEmployees.push_back(make_shared<HourlyEmployee>(name, age, position, hoursWorked, hourlyRate));
        }
        else if (type == "SalariedEmployee") {
            double monthlySalary = 0.0;
            if (!(file >> monthlySalary)) {
                cout << "Ошибка чтения SalariedEmployee." << endl;
                file.close();
                return false;
            }
            file.ignore(numeric_limits<streamsize>::max(), '\n');
            tempEmployees.push_back(make_shared<SalariedEmployee>(name, age, position, monthlySalary));
        }
        else {
            cout << "Неизвестный тип сотрудника: " << type << endl;
            file.close();
            return false;
        }

        while (file.peek() == '\n') {
            file.get();
        }
    }

    employees = move(tempEmployees);
    cout << "Сотрудники успешно загружены из файла: " << filename << endl;
    return true;
}
