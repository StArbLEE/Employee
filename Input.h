#pragma once
#include <string>
#include <iostream>
#include <cctype>
#include <algorithm> 
#include <memory>
#include "Employee.h"

using namespace std;

bool isDigitsOnly(const string& str);
bool isLettersOnly(const string& str);

shared_ptr<SalariedEmployee> createSalariedEmployee();
shared_ptr<HourlyEmployee> createHourlyEmployee();
