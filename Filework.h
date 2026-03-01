#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Employee.h"
using namespace std;

enum class FileOperationOption {
    OVERWRITE = 1,
    NEW_NAME,
    CANCEL
};

bool isValidFileName(const string& filename);
bool canWriteToFile(const string& filename);
bool fileExists(const string& filename);
bool saveEmployeesToFile(const string& filename, const vector<shared_ptr<Employee>>& employees);
bool loadEmployeesFromFile(const string& filename, vector<shared_ptr<Employee>>& employees);
