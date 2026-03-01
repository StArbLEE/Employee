#pragma once
#include <vector>
#include <memory>
#include "Employee.h"

using namespace std;

enum class MainMenuOption {
    ADD_EMPLOYEE = 1,
    SHOW_EMPLOYEES,
    CALCULATE_TOTAL_SALARY,  // Новая опция
    SAVE_TO_FILE,
    LOAD_FROM_FILE,
    EXIT,
    INVALID
};

enum class AddMenuOption {
    ADD_HOURLY = 1,
    ADD_SALARIED,
    BACK,
    INVALID
};

void displayMainMenu();
void displayAddMenu();
MainMenuOption getMainChoice();
AddMenuOption getAddChoice();
void processMenuChoice(MainMenuOption mainChoice, AddMenuOption addChoice, vector<shared_ptr<Employee>>& employees);
double calculateTotalSalary(const vector<shared_ptr<Employee>>& employees); 
