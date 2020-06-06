#include "class.h"
#include "date.h"

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
        Interface::input_menu menu;
        menu.set_title("Add Student");
        menu.add_item("Student ID");
        menu.add_item("Fullname");
        menu.add_item("DoB (YYYY/MM/DD)");
        menu.add_item("Gender");
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
        students.get_table().get(students.get_table().num_rows()-1,"Gender").assign(res.at(3));
        students.get_table().get(students.get_table().num_rows()-1,"Class").assign(res.at(4));
        if (students.init_write()==false){
            return;
        }
        students.write_and_terminate();
        users.get_table().add_row();
        users.get_table().get(users.get_table().num_rows()-1,"ID").assign(res.at(0));
        users.get_table().get(users.get_table().num_rows()-1,"Role").assign("Student");
        users.get_table().get(users.get_table().num_rows()-1,"Pass").assign(date().parse(res.at(2), "YYYY/MM/DD").compile("YYYYMMDD"));
        if (users.init_write()==false){
            return;
        }
        users.write_and_terminate();
        Interface::print_note("Added successfully","Result");
    }

    void editStudent(){
        Interface::input_menu menu;
        menu.set_title("Edit Student");
        menu.add_item("Student ID");
        list<multitype> res=menu.print_menu_and_wait(true);
        Interface::select_menu menu2;
        menu2.set_title(multitype("Editing student ").append(res.at(0)));
        menu2.add_item(1,"Student ID");
        menu2.add_item(2,"Fullname");
        menu2.add_item(3,"Date of birth");
        menu2.add_item(4,"Gender");
        menu2.add_item(5,"Class");
        menu2.add_item(6,"Exit");
        if (checkExist(res.at(0))==false){
            Interface::print_note("The student does not exist","Error");
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
                menu.add_item("Date of birth (YYYY/MM/DD)");
                list<multitype> res2=menu.print_menu_and_wait(true);
                students.get_table().get_row_where("Student ID",res.at(0)).at(2).assign(res2.at(0));
                break;
            }
            case (4):{
                Interface::input_menu menu;
                menu.set_title("Edit Student");
                menu.add_item("Gender");
                list<multitype> res2=menu.print_menu_and_wait(true);
                students.get_table().get_row_where("Student ID",res.at(0)).at(3).assign(res2.at(0));
                break;
            }
            case (5):{
                Interface::input_menu menu;
                menu.set_title("Edit Student");
                menu.add_item("Class");
                list<multitype> res2=menu.print_menu_and_wait(true);
                students.get_table().get_row_where("Student ID",res.at(0)).at(4).assign(res2.at(0));
                break;
            }
            case (6):break;
            default : break;
            }
        }
        while (num!=6);
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
            users.get_table().get(users.get_table().num_rows()-1,"Pass").assign(date().parse(students.get_table().get(i,"DoB"), "YYYY/MM/DD").compile("YYYYMMDD"));
            if (users.init_write()==false){
                return;
            }
            users.write_and_terminate();
        }
    }

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
        return row.at(4).equal(s);
    }

    void viewClass(){
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
        import.get_table().fix_keys({"Student ID","Fullname","Gender","DoB"});
        for (int i=0;i<import.get_table().num_rows();i++){
            students.get_table().add_row();
            users.get_table().add_row();
            students.get_table().get(students.get_table().num_rows()-1,"Student ID").assign(import.get_table().get(i,"Student ID"));
            users.get_table().get(users.get_table().num_rows()-1,"ID").assign(import.get_table().get(i,"Student ID"));
            students.get_table().get(students.get_table().num_rows()-1,"Fullname").assign(import.get_table().get(i,"Fullname"));
            students.get_table().get(students.get_table().num_rows()-1,"DoB").assign(import.get_table().get(i,"DoB"));
            students.get_table().get(students.get_table().num_rows()-1,"Gender").assign(import.get_table().get(i,"Gender"));
            users.get_table().get(users.get_table().num_rows()-1,"Pass").assign(date().parse(import.get_table().get(i,"DoB"), "YYYY/MM/DD").compile("YYYYMMDD"));
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
