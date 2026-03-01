#include <vector>
#include <memory>
#include <locale>
#include <iostream>
#include "menu.h"
#include "Test.h"


using namespace std;

void displayAssignment() {
 cout << "Разработать поля и методы, наследуемые из базового класса," << endl;
 cout << "а также собственные компоненты производных классов" << endl;
 cout << "Базовый класс может быть абстрактным" << endl;
 cout << "Реализовать заполнение контейнера указателями на базовый класс" << endl;
 cout << "с возможностью получения списка внесенных объектов" << endl;
 cout << "Предусмотреть необходимые проверки исходных данных" << endl;
 cout << "Создать базовый класс работник, производные классы: " << endl;
 cout << "- служащий с почасовой оплатой."  << endl;
 cout << "- служащий в штате." << endl;
 cout << "Определить функцию начисления зарплаты. " << endl;
 cout << endl;
}
int main() {
 setlocale(LC_ALL, "Russian");
 run_all_tests();
 displayAssignment();

 vector<shared_ptr<Employee>> employees;

 while (true) {
  displayMainMenu();
  MainMenuOption mainChoice = getMainChoice();
  AddMenuOption addChoice = AddMenuOption::INVALID;
  processMenuChoice(mainChoice, addChoice, employees);
 }
}
