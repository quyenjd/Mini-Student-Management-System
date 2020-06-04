#include <cstdio>
#ifndef FUNCTION_H
#define FUNCTION_H
#include "csv.h"
#include "interface.h"
#include "csv_import.h"

namespace SMS{
    void addStudent();//add a student
    void removeStudent();//remove a student
    void editStudent();//edit a student
    void viewStudentInClass();//view all students in a specific class
    void updateusers();//update users.csv based on the data in students.csv; use only when users.csv is empty
    void viewClass();//view all classes
    bool filterClass();
    bool filterStudent();
    void newClass();//import student data to students.csv, users.csv
}


#endif // FUNCTION_H
