#include "courses.h"
#include <iostream>
using namespace Csv;
using namespace std;
namespace SMS
{

    academic_year* create_academic_year() {  //checked
        academic_year *y = new academic_year();
        return y;
    }

    void school::add_year(academic_year *y){ //checked
        a.push_back(y);
    }

    void school::delete_academic_year (academic_year *&y) { //checked
        for (int i=0;i<a.size();i++) {
            if (a.at(i) == y) {
                a.delete_at(i);
                break;
            }
        }
    }

    void school::view_academic_year() { //checked
        for (int i=0;i<a.size();i++) {
            cout << "School Year " << a.at(i)->school_year.to_str() << endl;
        }
    }

    semester* create_semester() { //checked
        semester *s= new semester();
        return s;
    }

    void academic_year::add_semester (semester *&sem) { //checked
        s.push_back(sem);
        sem->semester_name = s.size();
    }

    void academic_year::delete_semester (semester *&sem) { //checked
        for (int i=0;i<s.size();i++) {
            if (sem==s.at(i)) {
                s.delete_at(i);
                break;
            }
        }
    }

    multitype academic_year::get_school_year () { //checked
        return school_year;
    }

    void academic_year::set_school_year (const multitype &name) { //checked
        school_year = name;
    }

    void academic_year::view_semester() {   //checked
        for (int i=0;i<s.size();i++) {
            cout << "Semester " << s.at(i)->semester_name.to_str() << endl;
        }
    }

    multitype semester::get_semester_name () {  //checked
        return semester_name;
    }

    course* create_course() {   //checked
        course *crse=new course();
        return crse;
    }

    void semester::add_course(course *crse) {   //checked
        csv_handler course_file("19APCS1-Schedule.csv");
        if (!course_file.init_read()) {
            cout << "Error!";
            return;
        }
        course_file.read_and_terminate();
        table data_table=course_file.get_table();
        crse->data[0]=data_table.num_rows()+1;
        c.push_back(crse);
    }

    void semester::view_course() {  //checked
        for (int i=0;i<c.size();i++) {
            cout << "Course " << c.at(i)->data[2].to_str() << endl;
        }
    }

    void semester::import_course() { ////// checked
        csv_handler course_file("19APCS1-Schedule.csv");
        if (!course_file.init_read()) {
            cout << "Error!";
            return;
        }
        course_file.read_and_terminate();
        table data_table=course_file.get_table();

        csv_handler student_file("19APCS1-Student.csv");
        if (!student_file.init_read()) {
            cout << "Error!";
            return;
        }
        student_file.read_and_terminate();
        table *student_table=&student_file.get_table();

        for (int i=0;i<data_table.num_rows();i++) {
            course* new_course=create_course();
            add_course(new_course);
            for (int j=0;j<16;j++) {
                new_course->data[j]=data_table.get_row(i).at(j);
            }

            for (int j=0;j<student_table->num_rows();j++) {
                if (student_table->get_row(j).at(4).equal(new_course->data[3])) {
                    student* new_student=create_student();
                    new_course->add_student(new_student);
                    for (int k=0;k<5;k++) {
                        new_student->data[k]=student_table->get_row(j).at(k);
                    }
                }
            }

        }
    }

    void semester::set_course_data_manually (course *&crse) {   //checked
        char id[100];
        cin.ignore();
        cout << "Enter Course ID: ";
        cin.get(id,100);
        crse->data[1]=id;

        char c_name[100];
        cin.ignore();
        cout << "Enter Course Name: ";
        cin.get(c_name,100);
        crse->data[2]=c_name;

        char c_class[100];
        cin.ignore();
        cout << "Enter Class: ";
        cin.get(c_class,100);
        crse->data[3]=c_class;

        char l_user[100];
        cin.ignore();
        cout << "Enter Lecturer Username: ";
        cin.get(l_user,100);
        crse->data[4]=l_user;

        char l_name[100];
        cin.ignore();
        cout << "Enter Lecturer Name: ";
        cin.get(l_name,100);
        crse->data[5]=l_name;

        char l_degree[100];
        cin.ignore();
        cout << "Enter Lecturer Degree: ";
        cin.get(l_degree,100);
        crse->data[6]=l_degree;

        char l_gender[100];
        cin.ignore();
        cout << "Enter Lecturer Gender: ";
        cin.get(l_gender,100);
        crse->data[7]=l_gender;

        char s_date[100];
        cin.ignore();
        cout << "Enter Start Date: ";
        cin.get(s_date,100);
        crse->data[8]=s_date;

        char e_date[100];
        cin.ignore();
        cout << "Enter End Date: ";
        cin.get(e_date,100);
        crse->data[9]=e_date;

        char d_o_w[100];
        cin.ignore();
        cout << "Enter Day of Week: ";
        cin.get(d_o_w,100);
        crse->data[10]=d_o_w;

        char s_hour[10];
        cin.ignore();
        cout << "Enter Start Hour: ";
        cin.get(s_hour,10);
        crse->data[11]=s_hour;

        char e_hour[10];
        cin.ignore();
        cout << "Enter End Hour: ";
        cin.get(e_hour,10);
        crse->data[12]=e_hour;

        char s_minute[10];
        cin.ignore();
        cout << "Enter Start Minute: ";
        cin.get(s_minute,10);
        crse->data[13]=s_minute;

        char e_minute[10];
        cin.ignore();
        cout << "Enter End Minute: ";
        cin.get(e_minute,10);
        crse->data[14]=e_minute;

        char room[10];
        cin.ignore();
        cout << "Enter Room: ";
        cin.get(room,10);
        crse->data[15]=room;
    }

    void semester::add_course_manually() {  //checked
        course *new_course= new course();
        add_course(new_course);
        set_course_data_manually(new_course);

        csv_handler course_file("19APCS1-Schedule.csv");
        if (!course_file.init_read()) {
            cout << "Error!";
            return;
        }
        course_file.read_and_terminate();
//        table data_table=course_file.get_table();

        if (!course_file.init_write()) {
            cout << "Error!";
            return;
        }
        course_file.get_table().add_row();
        for (int i=0;i<16;i++) {
            course_file.get_table().get_row(course_file.get_table().num_rows()-1).at(i)=new_course->data[i];
        }
        course_file.write_and_terminate();
    }

    void semester::delete_course(course *&crse) { //checked
        csv_handler course_file("19APCS1-Schedule.csv");
        if (!course_file.init_read()) {
            cout << "Error!";
            return;
        }
        course_file.read_and_terminate();
        table *data_table=&course_file.get_table();

        if (!course_file.init_write()) {
            cout << "Error!";
            return;
        }

        for (int i=0;i<c.size();i++) {
            if (c.at(i)==crse) {
                data_table->rm_row_where("No",c.at(i)->data[0]);
                c.delete_at(i);
                break;
            }
        }
        course_file.write_and_terminate();
    }

    void semester::update_course(course *&crse) {   //checked
        csv_handler course_file("19APCS1-Schedule.csv");
        if (!course_file.init_read()) {
            cout << "Error!";
            return;
        }
        course_file.read_and_terminate();
        table *data_table=&course_file.get_table();

        if (!course_file.init_write()) {
            cout << "Error!";
            return;
        }

        for (int i=0;i<c.size();i++) {
            if (c.at(i)==crse) {
                set_course_data_manually(c.at(i));
                for (int j=1;j<16;j++) {
                    data_table->get_row_where("No",crse->data[0]).at(j)=c.at(i)->data[j];
                }
            }
        }

        course_file.write_and_terminate();
    }

    student* create_student() { //checked
        student *stud= new student();
        return stud;
    }

    void course::add_student(student *&stud) {  //checked
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
            cout << "   " << st.at(i)->data[2].to_str() << "-" << st.at(i)->data[1].to_str();
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
        }
    }

    void course::remove_student_from_course(student *&stud) {   //checked
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

    }
};
