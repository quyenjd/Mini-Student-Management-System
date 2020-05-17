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
    student.get_table().rm_row_where("Student ID",id);
    //Update "No" column
    for (int i=0;i<=student.get_table().num_rows();i++)
        student.get_table().get(i,"No").assign(i+1);
    if (student.init_write()==false){
        std::cout<<"Error!";
        return;
    }
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
    student.get_table().get(student.get_table().num_rows()-1,"No").assign(student.get_table().num_rows());
    int id;
    std::cout<<"Insert Student ID: ";
    std::cin>>id;
    student.get_table().get(student.get_table().num_rows()-1,"Student ID").assign(id);
    char* fullname=new char[30];
    std::cout<<"Insert fullname: ";
    std::cin.ignore();
    std::cin.get(fullname,'/n');
    student.get_table().get(student.get_table().num_rows()-1,"Fullname").assign(fullname);
    char* dob=new char[30];
    std::cout<<"Insert date of birth: ";
    std::cin.ignore();
    std::cin.get(dob,'/n');
    student.get_table().get(student.get_table().num_rows()-1,"DoB").assign(dob);
    char* Class=new char[30];
    std::cout<<"Insert class: ";
    std::cin.ignore();
    std::cin.get(Class,'/n');
    student.get_table().get(student.get_table().num_rows()-1,"Class").assign(Class);
    if (student.init_write()==false){
        std::cout<<"Error!";
        return;
    }
    student.write_and_terminate(); //paste the table to the csv file
}
}


