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

bool checkExist2(multitype s){
    for (int i=0;i<coursestudent.get_table().num_rows();i++){
        if (coursestudent.get_table().get(i,"Student ID").equal(s)){
            return true;
        }
    }
    return false;
}

void removeStudent(){
    using namespace Csv;
    Interface::input_menu menu;
    menu.set_title("Delete Student");
    menu.add_item("Student ID");
    list<multitype> res=menu.print_menu_and_wait(true);
    if (checkExist(res.at(0))==false){
        Interface::print_note("The student is not exist","Error");
        return;
    }
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
    while (checkExist2(res.at(0))){
        coursestudent.get_table().rm_row_where("Student ID",res.at(0));
    }
    if (coursestudent.init_write()==false){
        return;
    }
    coursestudent.write_and_terminate();
    Interface::print_note("Remove successfully","Result");
}

void addStudent(){
    using namespace Csv;
    Interface::input_menu menu;
    menu.set_title("Add Student");
    menu.add_item("Student ID");
    menu.add_item("Fullname");
    menu.add_item("Date of birth");
    menu.add_item("Class");
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
    Interface::print_note("Add successfully","Result");
}

void editStudent(){
    using namespace Csv;
    Interface::input_menu menu;
    menu.set_title("Edit Student");
    menu.add_item("Student ID");
    list<multitype> res=menu.print_menu_and_wait(true);
    Interface::select_menu menu2;
    menu2.set_title(multitype("Editing student ").append(res.at(0)));
    menu2.add_item(1,"Student ID");
    menu2.add_item(2,"Fullname");
    menu2.add_item(3,"Date of birth");
    menu2.add_item(4,"Class");
    menu2.add_item(5,"Exit");
    if (checkExist(res.at(0))==false){
        Interface::print_note("The student is not exist","Error");
        return;
    }
    int num;
    do
    {
        num=menu2.print_menu_and_wait().to_int();
        switch (num){
        case (1):{
            Interface::input_menu menu;
            menu.set_title("Edit Student");
            menu.add_item("Student ID");
            list<multitype> res2=menu.print_menu_and_wait(true);
            students.get_table().get_row_where("Student ID",res.at(0)).at(0).assign(res2.at(0));
            users.get_table().get_row_where("ID",res.at(0)).at(0).assign(res2.at(0));
            while (checkExist2(res.at(0))){
                coursestudent.get_table().get_row_where("Student ID",res.at(0)).at(1).assign(res2.at(0));
            }
            break;
        }
        case (2):{
            Interface::input_menu menu;
            menu.set_title("Edit Student");
            menu.add_item("Fullname");
            list<multitype> res2=menu.print_menu_and_wait(true);
            students.get_table().get_row_where("Student ID",res.at(0)).at(1).assign(res2.at(0));
            break;
        }
        case (3):{
            Interface::input_menu menu;
            menu.set_title("Edit Student");
            menu.add_item("Date of birth");
            list<multitype> res2=menu.print_menu_and_wait(true);
            students.get_table().get_row_where("Student ID",res.at(0)).at(2).assign(res2.at(0));
            break;
        }
        case (4):{
            Interface::input_menu menu;
            menu.set_title("Edit Student");
            menu.add_item("Class");
            list<multitype> res2=menu.print_menu_and_wait(true);
            students.get_table().get_row_where("Student ID",res.at(0)).at(3).assign(res.at(0));
            break;
        }
        case (5):break;
        }
    }
    while (num!=5);
    if (students.init_write()==false){
        return;
    }
    if (users.init_write()==false){
        return;
    }
    if (coursestudent.init_write()==false){
        return;
    }
    students.write_and_terminate();
    users.write_and_terminate();
    coursestudent.write_and_terminate();
    Interface::print_note("Edit successfully","Result");
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
    menu.add_item("Class");
    list<multitype> res=menu.print_menu_and_wait(false);
    s=res.at(0);
    Interface::print_table(students.get_table().filter(filterStudent),"Students");
}
void newClass(){
    Interface::input_menu menu;
    menu.set_title("Import Student");
    menu.add_item("Class");
    menu.add_item("File link");
    list<multitype> res=menu.print_menu_and_wait(true);
    csv_handler import(res.at(1).to_str());
    if (import.init_read()==false){
        Interface::print_note(Csv::multitype("Your file '").append(res.at(1)).append("' is corrupted. Please try again."), "Failed");
        Interface::pause();
        return;
    }
    import.read_and_terminate();
    for (int i=0;i<import.get_table().num_rows();i++){
        students.get_table().add_row();
        users.get_table().add_row();
        students.get_table().get(students.get_table().num_rows()-1,"Student ID").assign(import.get_table().get(i,"Student ID"));
        users.get_table().get(users.get_table().num_rows()-1,"ID").assign(import.get_table().get(i,"Student ID"));
        students.get_table().get(students.get_table().num_rows()-1,"Fullname").assign(import.get_table().get(i,"Fullname"));
        students.get_table().get(students.get_table().num_rows()-1,"DoB").assign(import.get_table().get(i,"DoB"));
        char* dobb=new char[20];
        char* temp=new char[20];
        temp=import.get_table().get(i,"DoB").to_str();
        int j=0;
        for (int i=0;i<strlen(temp);i++){
            if (temp[i]!='/'){
                dobb[j]=temp[i];
                j++;
            }
        }
        users.get_table().get(users.get_table().num_rows()-1,"Pass").assign(dobb);
        users.get_table().get(users.get_table().num_rows()-1,"Role").assign("Student");
        students.get_table().get(students.get_table().num_rows()-1,"Class").assign(res.at(0));
    }
    if (students.init_write()==false){
        return;
    }
    if (users.init_write()==false){
        return;
    }
    students.write_and_terminate();
    users.write_and_terminate();
}

}


