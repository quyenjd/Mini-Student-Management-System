#include "courses.h"
#include <iostream>
using namespace Csv;
using namespace std;
namespace SMS
{
    void create_academic_year() {   //checked
        csv_handler year_file("years.csv");
        year_file.init_read();
        year_file.read_and_terminate();

        Interface::input_menu menu;
        menu.set_title("School Year");
        menu.add_item("School Year",true);
        list<multitype> res=menu.print_menu_and_wait();

        for (int i=0;i<year_file.get_table().num_rows();i++) {
            if (year_file.get_table().get_row(i).at(1).equal(res.at(0))) {
                cout << "This school year has already been in the list";
                return;
            }
        }
        year_file.get_table().add_row();
        year_file.get_table().get_row(year_file.get_table().num_rows()-1).at(0).assign(year_file.get_table().num_rows());
        year_file.get_table().get_row(year_file.get_table().num_rows()-1).at(1).assign(res.at(0));
        year_file.init_write();
        year_file.write_and_terminate();
    }

    void add_new_semester_to_academic_year() {
        csv_handler year_file("years.csv");
        year_file.init_read();
        year_file.read_and_terminate();

        csv_handler yearsemester_file("yearsemester.csv");
        yearsemester_file.init_read();
        yearsemester_file.read_and_terminate();

        csv_handler semester_file("semesters.csv");
        semester_file.init_read();
        semester_file.init_write();

        Interface::select_menu year_menu;
        year_menu.set_title("School Year");

        //Show menu years to choose
        for (int i=0;i<year_file.get_table().num_rows();i++) {
            year_menu.add_item(i+1,year_file.get_table().get_row(i).at(1));
        }

        year_menu.add_item(year_file.get_table().num_rows()+1,"Exit");
        int select;

        //Choosing a specific year
        do {
            select=year_menu.print_menu_and_wait().to_int();
            if (select>=1 && select<=year_file.get_table().num_rows()) {
                Interface::input_menu menu;
                menu.set_title("Semester name");
                menu.add_item("Semester name",true);

                list<multitype> res=menu.print_menu_and_wait(false);

                for (int j=0;j<semester_file.get_table().num_rows();j++) {
                    if (semester_file.get_table().get_row(j).at(1).equal(res.at(0)) && semester_file.get_table().get_row(j).at(0).equal(year_file.get_table().get_row(select-1).at(1))) {
                        cout << "This semester has already been in this school year" << endl;
                        return;
                    }
                }

                //add semester to yearsemester.csv
                yearsemester_file.get_table().add_row();
                yearsemester_file.get_table().get_row(yearsemester_file.get_table().num_rows()-1).at(0).assign(select-1);
                yearsemester_file.get_table().get_row(yearsemester_file.get_table().num_rows()-1).at(1).assign(yearsemester_file.get_table().num_rows());

                //add semester to semesters.csv
                semester_file.get_table().add_row();
                semester_file.get_table().get_row(semester_file.get_table().num_rows()-1).at(0).assign(year_file.get_table().get_row(select-1).at(1));
                semester_file.get_table().get_row(semester_file.get_table().num_rows()-1).at(1).assign(res.at(0));
            }
        } while (select!=year_file.get_table().num_rows()+1);

        yearsemester_file.init_write();
        yearsemester_file.write_and_terminate();

        semester_file.init_write();
        semester_file.write_and_terminate();
    }


    void create_new_course_manually() {
        csv_handler course_file("courses.csv");
        course_file.init_read();
        course_file.read_and_terminate();

        Interface::input_menu menu;
        menu.set_title("Course Information");
        menu.add_item("Course ID",false);
        menu.add_item("Course Name",true);
        menu.add_item("Class",false);
        menu.add_item("Start Date",false);
        menu.add_item("End Date",false);
        menu.add_item("Day of Week",false);
        menu.add_item("Start hour", false);
        menu.add_item("Start Minute",false);
        menu.add_item("End hour",false);
        menu.add_item("End Minute",false);
        menu.add_item("Room",false);

        list<multitype> res=menu.print_menu_and_wait();

        for (int i=0;i<course_file.get_table().num_rows();i++) {
            if (course_file.get_table().get_row(i).at(1).equal(res.at(1))) {
                cout << "This course has already been in the list" << endl;
                return;
            }
        }

        course_file.get_table().add_row();
        course_file.get_table().get_row(course_file.get_table().num_rows()-1).at(0).assign(course_file.get_table().num_rows());
        for (int j=1;j<13;j++) course_file.get_table().get_row(course_file.get_table().num_rows()-1).at(j).assign(res.at(j));

        course_file.init_write();
        course_file.write_and_terminate();
    }

    void update_course_manually() {
        csv_handler course_file ("courses.csv");
        course_file.init_read();
        course_file.read_and_terminate();

        Interface::select_menu course_menu;
        course_menu.set_title("Courses");
        for (int i=0;i<course_file.get_table().num_rows();i++) {
            course_menu.add_item(i+1,course_file.get_table().get_row(i).at(1));
        }
        course_menu.add_item(course_file.get_table().num_rows()+1,"Exit");
        int select;

        do {
            select=course_menu.print_menu_and_wait().to_int();
            if (select >=1 && select <= course_file.get_table().num_rows()) {

                Interface::input_menu menu;

                menu.set_title("Course Information");
                menu.add_item("Course ID",false);
                menu.add_item("Course Name",true);
                menu.add_item("Class",false);
                menu.add_item("Start Date",false);
                menu.add_item("End Date",false);
                menu.add_item("Day of Week",false);
                menu.add_item("Start hour", false);
                menu.add_item("Start Minute",false);
                menu.add_item("End hour",false);
                menu.add_item("End Minute",false);
                menu.add_item("Room",false);

                list<multitype> res=menu.print_menu_and_wait();

                for (int j=1;j<13;j++) course_file.get_table().get_row(select-1).at(j).assign(res.at(j));
                break;
            }
        } while (select != course_file.get_table().num_rows()+1);


        course_file.init_write();
        course_file.write_and_terminate();
    }

    void delete_course() {
        csv_handler course_file("courses.csv");
        course_file.init_read();
        course_file.read_and_terminate();

        Interface::select_menu course_menu;
        course_menu.set_title("Courses");
        for (int i=0;i<course_file.get_table().num_rows();i++) {
            course_menu.add_item(i+1,course_file.get_table().get_row(i).at(1));
        }
        course_menu.add_item(course_file.get_table().num_rows()+1,"Exit");

        int select;
        do {
            select=course_menu.print_menu_and_wait().to_int();
            if (select>=1 && select <= course_file.get_table().num_rows()) {
                for (int i=select;i<course_file.get_table().num_rows();i++) {
                    course_file.get_table().get_row(i).at(0).assign(course_file.get_table().get_row(i).at(0).to_int()-1);
                }
                course_file.get_table().rm_row(select-1);
                break;
            }
        } while (select != course_file.get_table().num_rows()+1);

    }
    /*void course::add_student(student *&stud) {  //checked
        csv_handler student_file("19APCS1-Student.csv");
        if (!student_file.init_read()) {
            cout << "Error!";
            return;
        }
        student_file.read_and_terminate();
        table student_table=student_file.get_table();
        stud->data[0]=student_table.num_rows()+1;
        st.push_back(stud);
    }

    void course::view_student_list() {  //checked
        cout << "List of students:"  << endl;
        for (int i=0;i<st.size();i++) {
            cout << "   " << i+1 << "." << st.at(i)->data[2].to_str() << "-" << st.at(i)->data[1].to_str();
            cout << endl;
        }
    }

    bool course::check_student_in_course(student *stud) {   //checked
        for (int i=0;i<st.size();i++) {
            if (stud->data[1].equal(st.at(i)->data[1])) return true;
        }
        return false;
    }

    void course::add_student_to_course() {  //checked
        student *new_stud=create_student();

        new_stud->data[0]=st.size()+1;

        char id[15];
        cout << "Student ID: ";
        cin.ignore();
        cin.get(id,15);
        new_stud->data[1]=id;

        if (check_student_in_course(new_stud)) {
            cout << "This student was in this course, you cannot add anymore" << endl;
            return;
        } else {
            char name[50];
            cout << "Student Name: ";
            cin.ignore();
            cin.get(name,50);
            new_stud->data[2]=name;

            char  dob[15];
            cout << "Date of Birth: ";
            cin.ignore();
            cin.get(dob,15);
            new_stud->data[3]=dob;

            char st_class[15];
            cout << "Student class: ";
            cin.ignore();
            cin.get(st_class,15);
            new_stud->data[4]=st_class;

            add_student(new_stud);

            csv_handler student_file("19APCS1-Student.csv");
            if (!student_file.init_read()) {
                cout << "Error!";
                return;
            }

            student_file.read_and_terminate();
            table *student_table=&student_file.get_table();
            student_table->add_row();

            if (!student_file.init_write()) {
                cout << "Error!";
                return;
            }

            for (int i=0;i<5;i++) {
                student_table->get_row(student_table->num_rows()-1).at(i)=new_stud->data[i];
            }
            student_file.write_and_terminate();

            cout << "Added Successfully" << endl;
        }
    }

    void course::remove_student_from_course(student *&stud) {   //checked
        if (check_student_in_course(stud)) {
            csv_handler student_file("19APCS1-Student.csv");
            if (!student_file.init_read()) {
                cout << "Error!";
                return;
            }

            student_file.read_and_terminate();
            table *student_table=&student_file.get_table();

            if (!student_file.init_write()) {
                cout << "Error!";
                return;
            }

            for (int i=0;i<st.size();i++) {
                if (st.at(i)==stud) {
                    student_table->rm_row_where("No",st.at(i)->data[0]);
                    st.delete_at(i);
                    break;
                }
            }

            student_file.write_and_terminate();
        } else {
            cout << "This student doesn't exist in this course !" << endl;
            return;
        }
    }

    void view_list_course_current(school *sch) { //checked
        int k=sch->a.at(sch->a.size()-1)->s.at(sch->a.at(sch->a.size()-1)->s.size()-1)->c.size();

        for (int i=0;i<k;i++) {
            cout << "Course " << sch->a.at(sch->a.size()-1)->s.at(sch->a.at(sch->a.size()-1)->s.size()-1)->c.at(i)->data[2].to_str() << endl;
        }
    }

    list<lecturer*> lect;

    bool check_exist_lecturer_in_list(lecturer* new_lec) {  //checked
        for (int i=0;i<lect.size();i++) {
            if (new_lec->data[0].equal(lect.at(i)->data[0])) return true;
        }
        return false;
    }

    void create_lecturer_list() {   //checked
        csv_handler course_file("19APCS1-Schedule.csv");

        if (!course_file.init_read()) {
            cout << "Error" << endl;
            return;
        }

        course_file.read_and_terminate();
        table *data_table=&course_file.get_table();
        for (int i=0;i<data_table->num_rows();i++) {
            lecturer *new_lec=create_lecturer();
            for (int j=0;j<4;j++) {
                new_lec->data[j]=data_table->get_row(i).at(j+4);
            }
            if (!check_exist_lecturer_in_list(new_lec)) add_lecturer(new_lec);
        }
    }

    lecturer* create_lecturer() {   //checked
        lecturer *new_lec = new lecturer();
        return new_lec;
    }
    void add_lecturer(lecturer *new_lec) {  //checked
        lect.push_back(new_lec);
    }
    void view_lecturer_list() { //checked
        cout << "Lecturers list: " << endl;
        for (int i=0;i<lect.size();i++) {
            cout <<"    " << i+1 <<"." << lect.at(i)->data[1].to_str() << endl;
        }
    }

    bool set_lecturer_data(lecturer *&new_lec) {    //checked
        char l_user[100];
        cin.ignore();
        cout << "Enter Lecturer Username: ";
        cin.get(l_user,100);
        for (int i=0;i<lect.size();i++) {
            if (lect.at(i)->data[0].equal(l_user)) return false;
        }
        new_lec->data[0]=l_user;

        char l_name[100];
        cin.ignore();
        cout << "Enter Lecturer Name: ";
        cin.get(l_name,100);
        new_lec->data[1]=l_name;

        char l_degree[100];
        cin.ignore();
        cout << "Enter Lecturer Degree: ";
        cin.get(l_degree,100);
        new_lec->data[2]=l_degree;

        char l_gender[100];
        cin.ignore();
        cout << "Enter Lecturer Gender: ";
        cin.get(l_gender,100);
        new_lec->data[3]=l_gender;
        return true;
    }

    void add_lecturer_manually() {  //checked
        lecturer *new_lec=create_lecturer();
        if (set_lecturer_data(new_lec))
        {
            add_lecturer(new_lec);
            cout << "Added Successfully" << endl;
        }
        else cout << "This lecturer was in this list before" << endl;
    }

    void update_lecturer(lecturer *&new_lec) {  //checked
        multitype temp=new_lec->data[0];
        bool check=set_lecturer_data(new_lec);
        if (check) return;
        else if (!check && new_lec->data[0].equal(temp) ) {
            char l_name[100];
            cin.ignore();
            cout << "Enter Lecturer Name: ";
            cin.get(l_name,100);
            new_lec->data[1]=l_name;

            char l_degree[100];
            cin.ignore();
            cout << "Enter Lecturer Degree: ";
            cin.get(l_degree,100);
            new_lec->data[2]=l_degree;

            char l_gender[100];
            cin.ignore();
            cout << "Enter Lecturer Gender: ";
            cin.get(l_gender,100);
            new_lec->data[3]=l_gender;
        } else if (!check && !new_lec->data[0].equal(temp)){
            cout << "This lecturer was in this list before. Please try again" << endl;
            return;
        }
    }

    void delete_lecturer(lecturer *&new_lec) {
        if (!check_exist_lecturer_in_list(new_lec)) {
            cout << "This lecturer was not in this list" << endl;
            return;
        }
        for (int i=0;i<lect.size();i++) {
            if (lect.at(i)==new_lec) {
                lect.delete_at(i);
                cout << "Removed Lecturer Successfully" << endl;
                break;
            }
        }
    }*/
};
