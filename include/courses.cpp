#include "courses.h"
#include <iostream>
using namespace Csv;
using namespace std;
namespace SMS
{

<<<<<<< Updated upstream
    academic_year::academic_year()
    {
        for (int i=0;i<3;i++) s[i] = semester();
    }

    academic_year* create_academic_year() {
=======
    academic_year* create_academic_year() {  //checked
>>>>>>> Stashed changes
        academic_year *y = new academic_year();
        return y;
    }

<<<<<<< Updated upstream
    void school::add_year(academic_year *y)
    {
        a.push_back(y);
    }
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
        c.push_back(crse);
    }

    void semester::view_course() {  //checked
        for (int i=0;i<c.size();i++) {
            cout << "Course " << c.at(i)->data[2].to_str() << endl;
        }
    }

    void semester::import_course() { ////// student chua xong + loi
        csv_handler course_file("19APCS1-Schedule.csv");
        if (!course_file.init_read()) {
            cout << "Error!";
            return;
        }
        course_file.read_and_terminate();
        table data_table=course_file.get_table();

        for (int i=1;i<=data_table.num_rows();i++) {
            course* new_course=create_course();
            for (int j=0;j<16;i++) {
                new_course->data[j]=data_table.get_row(i).at(j);
            }
            add_course(new_course);
        }
    }

    void semester::set_course_data_manually (course *&crse) {   //checked
        crse->data[0]=c.size();
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
    }

    void semester::delete_course(course *&crse) { //checked
        for (int i=0;i<c.size();i++) {
            if (c.at(i)==crse) {
                c.delete_at(i);
                break;
            }
        }
    }

>>>>>>> Stashed changes
};
