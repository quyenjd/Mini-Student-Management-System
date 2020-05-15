#include "courses.h"
#include <iostream>
using namespace Csv;
using namespace std;
namespace SMS
{

<<<<<<< Updated upstream
<<<<<<< Updated upstream
    academic_year* create_academic_year() {
=======
    academic_year* create_academic_year() {  //check
>>>>>>> Stashed changes
=======
    academic_year* create_academic_year() {  //checked
>>>>>>> Stashed changes
        academic_year *y = new academic_year();
        return y;
    }

<<<<<<< Updated upstream
    void school::add_year(academic_year *y){
        a.push_back(y);
    }

<<<<<<< Updated upstream
=======
    void school::delete_academic_year (academic_year *year) {
        for (int i=0;i<a.size();i++) {
            if (a.at(i) == year) a.delete_at(i);
        }
    }

    void school::view_academic_year() {
        for (int i=0;i<a.size();i++) {
            cout << "School Year: " << a.at(i)->school_year.to_str() << endl;
        }
    }

>>>>>>> Stashed changes
    semester* create_semester() {
=======
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
>>>>>>> Stashed changes
        semester *s= new semester();
        return s;
    }

<<<<<<< Updated upstream
    void academic_year::add_semester (semester *sem) {
        s.push_back(sem);
    }

<<<<<<< Updated upstream
    multitype academic_year::get_school_year () {
=======
    void academic_year::delete_semester (semester *sem) {
        for (int i=0;i<s.size();i++) {
            if (sem==s.at(i)) s.delete_at(i);
        }
    }

    multitype academic_year::get_school_year () { //check
>>>>>>> Stashed changes
        return school_year;
    }

    void academic_year::set_school_year (const multitype &name) {
        school_year = name;
    }

<<<<<<< Updated upstream
    void school::delete_academic_year (academic_year *year) {
        for (int i=0;i<a.size();i++) {
            if (a.at(i) == year) a.delete_at(i);
        }
=======
    void academic_year::view_semester() {
        for (int i=0;i<s.size();i++) {
            cout << "Semester" << i+1 << endl;
        }
    }

    void semester::import_course() { ////// Còn phần student
=======
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

    course* create_course() {
        course *crse=new course();
        return crse;
    }

    void semester::add_course(course *crse) {
        c.push_back(crse);
    }

    void semester::import_course() { ////// student chua xong
>>>>>>> Stashed changes
        csv_handler course_file("19APCS1-Schedule.csv");
        if (!course_file.init_read()) {
            cout << "Error!";
            return;
        }
        course_file.read_and_terminate();
<<<<<<< Updated upstream
>>>>>>> Stashed changes
=======
        table data_table=course_file.get_table();

        for (int i=1;i<=data_table.num_rows();i++) {
            course* new_course=create_course();
            for (int j=0;j<16;i++) {
                new_course->data[j]=data_table.get_row(i).at(j);
            }
            add_course(new_course);
        }
    }

    void semester::set_course_data_manually (course *&crse) {
        crse->data[0]=c.size();
        int id;
        cout << "Enter Course ID: "; cin >> id;
        crse->data[1]=id;

        char c_name[100];
        cout << "Enter Course Name: ";
        cin.ignore();
        cin.get(c_name,100);
        crse->data[2]=c_name;

        char c_class[100];
        cout << "Enter Class: ";
        cin.get(c_class,100);
        crse->data[3]=c_class;

        char l_user[100];
        cout << "Enter Lecturer Username: ";
        cin.get(l_user,100);
        crse->data[4]=l_user;

        char l_name[100];
        cout << "Enter Lecturer Name: ";
        cin.get(l_name,100);
        crse->data[5]=l_name;

        char l_degree[100];
        cout << "Enter Lecturer Degree: ";
        cin.get(l_degree,100);
        crse->data[6]=l_degree;

        char l_gender[100];
        cout << "Enter Lecturer Gender: ";
        cin.get(l_gender,100);
        crse->data[7]=l_gender;

        char s_date[100];
        cout << "Enter Start Date: ";
        cin.get(s_date,100);
        crse->data[8]=s_date;

        char e_date[100];
        cout << "Enter End Date: ";
        cin.get(e_date,100);
        crse->data[9]=e_date;

        char d_o_w[100];
        cout << "Enter Day of Week: ";
        cin.get(d_o_w,100);
        crse->data[10]=d_o_w;

        int s_hour;
        cout << "Enter Start Hour: ";
        cin >> s_hour;
        crse->data[11]=s_hour;

        int e_hour;
        cout << "Enter End Hour: ";
        cin >> e_hour;
        crse->data[12]=e_hour;

        int s_minute;
        cout << "Enter Start Minute: ";
        cin >> s_minute;
        crse->data[13]=s_minute;

        int e_minute;
        cout << "Enter End Minute: ";
        cin >> e_minute;
        crse->data[14]=e_minute;

        char room[10];
        cin.ignore();
        cin.get(room,10);
        crse->data[15]=room;
    }

    void semester::add_course_manually() {
        course *new_course= new course();
        set_course_data_manually(new_course);
        add_course(new_course);
    }

    void semester::delete_course(course &crse) {
        for (int i=0;i<c.size();i++) {
            if (c.at(i)==crse) {
                c.delete_at(i);
                break;
            }
        }
>>>>>>> Stashed changes
    }

};
