#include <cstdio>
#include <iostream>
#include "class.h"

namespace classes{

void importStudent(){
    using namespace Csv;
    csv_handler student("19APCS1-Student.csv");
    if (student.init_read()==false){
        std::cout<<"Error!";
        return;
    }
    student.read_and_terminate();
}

void addStudent(){
    using namespace Csv;
    csv_handler student("19APCS1-Student.csv");
    if (student.init_read()==false){
        std::cout<<"Error!";
        return;
    }
    student.get_table().add_row();
}

void deleteStudent(){
    using namespace Csv;
    csv_handler student("19APCS1-Student.csv");
    if (student.init_read()==false){
        std::cout<<"Error!";
        return;
    }
    std::cout<<"Input id: ";
    multitype id;
    student.get_table().get_row_where("Student ID",id);
    student.get_table().del_row_where("Student ID",id);
}
}
