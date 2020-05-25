#include <cstdio>
#include <iostream>
#include "class.h"
#include <string>

namespace classes{

void removeStudent(){
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
    std::cin.ignore();
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
    std::cin.ignore();
    student.get_table().get(student.get_table().num_rows()-1,"Class").assign(Class);
    if (student.init_write()==false){
        std::cout<<"Error!";
        return;
    }
    student.write_and_terminate(); //paste the table to the csv file
    csv_handler idpass("idpass.csv");
    if (idpass.init_read()==false){
        std::cout<<"Error!";
        return;
    }
    idpass.read_and_terminate();
    idpass.get_table().add_row();
    idpass.get_table().get(idpass.get_table().num_rows()-1,"No").assign(idpass.get_table().num_rows());
    idpass.get_table().get(idpass.get_table().num_rows()-1,"ID").assign(student.get_table().get(student.get_table().num_rows()-1,"Student ID").to_str());
    char* dobb=new char[20];
    char* temp=new char[20];
    temp=student.get_table().get(student.get_table().num_rows()-1,"DoB").to_str();
    int j=0;
    for (int i=0;i<strlen(temp);i++){
        if (temp[i]!='/'){
            dobb[j]=temp[i];
            j++;
        }
    }
    idpass.get_table().get(idpass.get_table().num_rows()-1,"Pass").assign(dobb);
    if (idpass.init_write()==false){
        std::cout<<"Error!";
        return;
    }
    idpass.write_and_terminate();
}

void editStudent(){
    using namespace Csv;
    csv_handler student("19APCS1-Student.csv");
    if (student.init_read()==false){
        std::cout<<"Error!";
        return;
    }
    student.read_and_terminate(); //read the csv file and copy to table
    std::cout<<"Select the student's no you want to edit: ";
    int no;
    std::cin>>no;
    std::cout<<"Select what you want to edit: "<<std::endl;
    std::cout<<"1 for Student ID"<<std::endl;
    std::cout<<"2 for Fullname"<<std::endl;
    std::cout<<"3 for date of birth"<<std::endl;
    std::cout<<"4 for class"<<std::endl;
    int num;
    std::cin>>num;
    if (num==1){
        int id;
        std::cout<<"Insert Student ID: ";
        std::cin>>id;
        student.get_table().get(no-1,"Student ID").assign(id);
        std::cin.ignore();
    }
    if (num==2){
        char* fullname=new char[30];
        std::cout<<"Insert fullname: ";
        std::cin.ignore();
        std::cin.get(fullname,'/n');
        student.get_table().get(no-1,"Fullname").assign(fullname);
        std::cin.ignore();
    }
    if (num==3){
        char* dob=new char[30];
        std::cout<<"Insert date of birth: ";
        std::cin.ignore();
        std::cin.get(dob,'/n');
        student.get_table().get(no-1,"DoB").assign(dob);
        std::cin.ignore();
    }
    if (num==4){
        char* Class=new char[30];
        std::cout<<"Insert class: ";
        std::cin.ignore();
        std::cin.get(Class,'/n');
        student.get_table().get(no-1,"Class").assign(Class);
        std::cin.ignore();
    }
    if (student.init_write()==false){
        std::cout<<"Error!";
        return;
    }
    student.write_and_terminate(); //paste the table to the csv file
}

void viewStudentInClass(){
    using namespace Csv;
    csv_handler student("19APCS1-Student.csv");
    if (student.init_read()==false){
        std::cout<<"Error!";
        return;
    }
    student.read_and_terminate();
    std::cout<<"Select the class: ";
    char* s=new char[30];
    std::cin.get(s,'\n');
    for (int i=0;i<student.get_table().num_rows();i++){
        if (strcmp(student.get_table().get(i,"Class").to_str(),s)==0){
             std::cout<<student.get_table().get(i,"Fullname").to_str()<<std::endl;
        }
    }
}

void updateIDPass(){
    using namespace Csv;
    csv_handler student("19APCS1-Student.csv");
    if (student.init_read()==false){
        std::cout<<"Error!";
        return;
    }
    student.read_and_terminate();
    for (int i=0;i<student.get_table().num_rows();i++){
        csv_handler idpass("idpass.csv");
        if (idpass.init_read()==false){
            std::cout<<"Error!";
            return;
        }
        idpass.read_and_terminate();
        idpass.get_table().add_row();
        idpass.get_table().get(idpass.get_table().num_rows()-1,"No").assign(idpass.get_table().num_rows());
        idpass.get_table().get(idpass.get_table().num_rows()-1,"ID").assign(student.get_table().get(i,"Student ID").to_str());
        char* dob=new char[20];
        char* temp=new char[20];
        temp=student.get_table().get(i,"DoB").to_str();
        int j=0;
        for (int i=0;i<strlen(temp);i++){
            if (temp[i]!='/'){
                dob[j]=temp[i];
                j++;
            }
        }
        idpass.get_table().get(idpass.get_table().num_rows()-1,"Pass").assign(dob);
        if (idpass.init_write()==false){
            std::cout<<"Error!";
            return;
        }
        idpass.write_and_terminate();
    }
}
}


