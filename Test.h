#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Employee.h"

bool is_file_empty(const std::string& path);
bool test_employee_input(std::vector<std::shared_ptr<Employee>>& employees, const std::string& path);
void run_all_tests();
