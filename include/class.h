#include <cstdio>
#ifndef FUNCTION_H
#define FUNCTION_H
#include "csv.h"
#include "interface.h"
#include "csv_import.h"

namespace SMS{
    void addStudent();
    void removeStudent();
    void editStudent();
    void viewStudentInClass();
    void updateusers();
    void viewClass();
    bool filterClass();
    bool filterStudent();
    void newClass();
}


#endif // FUNCTION_H
