#include <cstdio>
#include <iostream>
#include "class.h"

namespace classes{

void deleteStudent(){
    using namespace Csv;
    csv_handler student("19APCS1-Student.csv");
    if (student.init_read()==false){
        std::cout<<"Error!";
        return;
    }
    student.read_and_terminate(); //read the csv file and copy to table
    int id;
    std::cout<<"Input id: ";
    std::cin>>id;
    //std::cout<<student.get_table().del_row_where("Student ID",id); DEBUG
    //std::cout<<student.get_table().get_key("Student ID"); DEBUG
    student.write_and_terminate(); //paste the table to the csv file
}

void addStudent(){
    using namespace Csv;
    csv_handler student("19APCS1-Student.csv");
    if (student.init_read()==false){
        std::cout<<"Error!";
        return;
    }
    student.read_and_terminate(); //read the csv file and copy to table
    student.get_table().add_row(); //add row to the table
    //add data to the row
    student.write_and_terminate(); //paste the table to the csv file
}
}


