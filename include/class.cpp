#include <cstdio>
#include <iostream>
#include "class.h"
#include <string>

namespace SMS{

using namespace Csv;
bool checkExist(multitype s){
    for (int i=0;i<students.get_table().num_rows();i++){
        if (students.get_table().get(i,"Student ID").equal(s)){
            return true;
        }
    }
    return false;
}

void removeStudent(){
    using namespace Csv;
    Interface::input_menu menu;
    menu.set_title("Delete Student");
    menu.add_item("Student ID: ",false);
    list<multitype> res=menu.print_menu_and_wait(false);
    students.get_table().rm_row_where("Student ID",res.at(0));
    if (students.init_write()==false){
        return;
    }
    students.write_and_terminate();
    users.get_table().rm_row_where("ID",res.at(0));
    if (users.init_write()==false){
        return;
    }
    users.write_and_terminate();
    coursestudent.get_table().rm_row_where("Student ID",res.at(0));
    if (coursestudent.init_write()==false){
        return;
    }
    coursestudent.write_and_terminate();
}

void addStudent(){
    using namespace Csv;
    Interface::input_menu menu;
    menu.set_title("Add Student");
    menu.add_item("Student ID: ",false);
    menu.add_item("Fullname: ",true);
    menu.add_item("Date of birth: ",true);
    menu.add_item("Class: ",false);
    list<multitype> res=menu.print_menu_and_wait(false);
    if (checkExist(res.at(0))==true){
        Interface::print_note("The student is exist","Error");
        return;
    }
    students.get_table().add_row();
    students.get_table().get(students.get_table().num_rows()-1,"Student ID").assign(res.at(0));
    students.get_table().get(students.get_table().num_rows()-1,"Fullname").assign(res.at(1));
    students.get_table().get(students.get_table().num_rows()-1,"DoB").assign(res.at(2));
    students.get_table().get(students.get_table().num_rows()-1,"Class").assign(res.at(3));
    if (students.init_write()==false){
        return;
    }
    students.write_and_terminate();
    users.get_table().add_row();
    users.get_table().get(users.get_table().num_rows()-1,"ID").assign(res.at(0));
    users.get_table().get(users.get_table().num_rows()-1,"Role").assign("Student");
    char* dobb=new char[20];
    char* temp=new char[20];
    temp=res.at(2).to_str();
    int j=0;
    for (int i=0;i<strlen(temp);i++){
        if (temp[i]!='/'){
            dobb[j]=temp[i];
            j++;
        }
    }
    users.get_table().get(users.get_table().num_rows()-1,"Pass").assign(dobb);
    if (users.init_write()==false){
        return;
    }
    users.write_and_terminate();
}

void editStudent(){
    using namespace Csv;
    Interface::input_menu menu;
    menu.set_title("Edit Student");
    menu.add_item("Student ID: ",false);
    list<multitype> res=menu.print_menu_and_wait(true);
    Interface::select_menu menu2;
    menu2.set_title(multitype("Editing student ").append(res.at(0)));
    menu2.add_item(1,"Student ID");
    menu2.add_item(2,"Fullname");
    menu2.add_item(3,"Date of birth");
    menu2.add_item(4,"Class");
    if (checkExist(res.at(0))==false){
        Interface::print_note("The student is not exist","Error");
        return;
    }
    int num=menu2.print_menu_and_wait().to_int();
    if (num==1){
        int id;
        std::cout<<"Insert Student ID: ";
        std::cin>>id;
        students.get_table().get_row_where("Student ID",res.at(0)).at(0).assign(id);
        users.get_table().get_row_where("Student ID",res.at(0)).at(0).assign(id);
        coursestudent.get_table().get_row_where("Student ID",res.at(0)).at(1).assign(id);
        std::cin.ignore();
    }
    if (num==2){
        char* fullname=new char[30];
        std::cout<<"Insert fullname: ";
        std::cin.ignore();
        std::cin.get(fullname,'/n');
        students.get_table().get_row_where("Student ID",res.at(0)).at(1).assign(fullname);
        std::cin.ignore();
    }
    if (num==3){
        char* dob=new char[30];
        std::cout<<"Insert date of birth: ";
        std::cin.ignore();
        std::cin.get(dob,'/n');
        students.get_table().get_row_where("Student ID",res.at(0)).at(2).assign(dob);
        std::cin.ignore();
    }
    if (num==4){
        char* Class=new char[30];
        std::cout<<"Insert class: ";
        std::cin.ignore();
        std::cin.get(Class,'/n');
        students.get_table().get_row_where("Student ID",res.at(0)).at(3).assign(Class);
        std::cin.ignore();
    }
    if (students.init_write()==false){
        std::cout<<"Error!";
        return;
    }
    students.write_and_terminate(); //paste the table to the csv file
}

void updateusers(){
    for (int i=0;i<students.get_table().num_rows();i++){
        users.get_table().add_row();
        users.get_table().get(users.get_table().num_rows()-1,"ID").assign(students.get_table().get(i,"Student ID").to_str());
        users.get_table().get(users.get_table().num_rows()-1,"Role").assign("Student");
        char* dob=new char[20];
        char* temp=new char[20];
        temp=students.get_table().get(i,"DoB").to_str();
        int j=0;
        for (int i=0;i<strlen(temp);i++){
            if (temp[i]!='/'){
                dob[j]=temp[i];
                j++;
            }
        }
        users.get_table().get(users.get_table().num_rows()-1,"Pass").assign(dob);
        if (users.init_write()==false){
            return;
        }
        users.write_and_terminate();
    }
}

using namespace Csv;
list<multitype> cl;
bool filterClass (multitype column,list<multitype> row,table tb){
    if (!column.equal("Class"))
        return false;
    multitype value=row.at(tb.get_key(column));
    for (int i=0;i<cl.size();i++){
        if (cl.at(i).equal(value))
            return false;
    }
    cl.push_back(value);
    return true;
}

multitype s;
bool filterStudent (multitype column,list<multitype> row,table tb){
    if (!column.equal("Fullname"))
        return false;
    return row.at(3).equal(s);
}

void viewClass(){
    using namespace Csv;
    Interface::print_table(students.get_table().filter(filterClass),"Class");
}

void viewStudentInClass(){
    Interface::input_menu menu;
    menu.set_title("View Student");
    menu.add_item("Class: ",false);
    list<multitype> res=menu.print_menu_and_wait(false);
    s=res.at(0);
    Interface::print_table(students.get_table().filter(filterStudent),"Students");
}

}


