#include "menu.h"
#include "input.h"
#include "filework.h"
#include <iostream>
#include <iomanip>
#include <numeric>
#include <limits>
#include <string>

using namespace std;

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void displayMainMenu() {
    cout << "\nГлавное меню:" << endl;
    cout << "1. Добавить сотрудника" << endl;
    cout << "2. Показать всех сотрудников" << endl;
    cout << "3. Рассчитать общую зарплату" << endl;
    cout << "4. Сохранить в файл" << endl;
    cout << "5. Загрузить из файла" << endl;
    cout << "6. Выход" << endl;
    cout << "Ваш выбор: ";
}

void displayAddMenu() {
    cout << "\nДобавить сотрудника:" << endl;
    cout << "1. Почасовой сотрудник" << endl;
    cout << "2. Сотрудник с окладом" << endl;
    cout << "3. Назад в главное меню" << endl;
    cout << "Ваш выбор: ";
}

MainMenuOption getMainChoice() {
    int choice;
    while (true) {
        if (cin >> choice) {
            clearInputBuffer();
            if (choice >= static_cast<int>(MainMenuOption::ADD_EMPLOYEE) &&
                choice <= static_cast<int>(MainMenuOption::EXIT)) {
                return static_cast<MainMenuOption>(choice);
            }
        }
        else {
            clearInputBuffer();
        }
        cout << "Некорректный ввод. Введите число от "
            << static_cast<int>(MainMenuOption::ADD_EMPLOYEE) << " до "
            << static_cast<int>(MainMenuOption::EXIT) << ": ";
    }
}

AddMenuOption getAddChoice() {
    int choice;
    while (true) {
        if (cin >> choice) {
            clearInputBuffer();
            if (choice >= static_cast<int>(AddMenuOption::ADD_HOURLY) &&
                choice <= static_cast<int>(AddMenuOption::BACK)) {
                return static_cast<AddMenuOption>(choice);
            }
        }
        else {
            clearInputBuffer();
        }
        cout << "Некорректный ввод. Введите число от "
            << static_cast<int>(AddMenuOption::ADD_HOURLY) << " до "
            << static_cast<int>(AddMenuOption::BACK) << ": ";
    }
}

double calculateTotalSalary(const vector<shared_ptr<Employee>>& employees) {
    return accumulate(employees.begin(), employees.end(), 0.0,
        [](double sum, const shared_ptr<Employee>& emp) {
            return sum + emp->calculateSalary();
        });
}

void processMenuChoice(MainMenuOption mainChoice, AddMenuOption addChoice, vector<shared_ptr<Employee>>& employees) {
    string filename;

    switch (mainChoice) {
    case MainMenuOption::ADD_EMPLOYEE:
        displayAddMenu();
        addChoice = getAddChoice();

        switch (addChoice) {
        case AddMenuOption::ADD_HOURLY:
            employees.push_back(createHourlyEmployee());
            break;
        case AddMenuOption::ADD_SALARIED:
            employees.push_back(createSalariedEmployee());
            break;
        case AddMenuOption::BACK:
            break;
        case AddMenuOption::INVALID:
            cout << "Некорректный выбор." << endl;
            break;
        }
        break;

    case MainMenuOption::SHOW_EMPLOYEES:
        if (employees.empty()) {
            cout << "Список сотрудников пуст." << endl;
        }
        else {
            for (const auto& emp : employees) {
                emp->Show();
                cout << "-----------------------------" << endl;
            }
        }
        break;

    case MainMenuOption::CALCULATE_TOTAL_SALARY:
        if (employees.empty()) {
            cout << "Список сотрудников пуст." << endl;
        }
        else {
            double total = calculateTotalSalary(employees);
            cout << "Общая зарплата всех сотрудников: "
                << fixed << setprecision(2) << total << " руб." << endl;
        }
        break;

    case MainMenuOption::SAVE_TO_FILE:
        if (employees.empty()) {
            cout << "Список сотрудников пуст." << endl;
            break;
        }
        cout << "Введите имя файла для сохранения: ";
        getline(cin, filename);

        if (!saveEmployeesToFile(filename, employees)) {
            cout << "Ошибка при сохранении в файл." << endl;
        }
        break;

    case MainMenuOption::LOAD_FROM_FILE:
        cout << "Введите имя файла для загрузки: ";
        getline(cin, filename);
        if (!loadEmployeesFromFile(filename, employees)) {
            cout << "Не удалось загрузить данные из файла." << endl;
        }
        break;

    case MainMenuOption::EXIT:
        cout << "Выход из программы..." << endl;
        exit(0);

    case MainMenuOption::INVALID:
        cout << "Некорректный выбор." << endl;
        break;
    }
}
