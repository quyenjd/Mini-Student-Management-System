#ifndef COURSES_H
#define COURSES_H
#include "csv.h"
using namespace Csv;
using namespace std;
namespace SMS
{
    class student {
    public:
        multitype data[5];  //data[0-4] respectively
                            //No,Student ID, Fullname, DoB, Class
    };

    class course
    {
    public:
        list<student*> st;  //list of students of a course

        multitype data[16]; //data[0-15] respectively
                            //no,course_id,course_name,course_class,lec_user,lec_name,lec_degree,lec_gender
                            //st_date,en_date,day_of_week,st_hour,st_minute,en_hour,en_minute,room

        void add_student(student *&stud);   //add a non-data student to list student st above

        void view_student_list();   //view list of students of a course

        void add_student_to_course ();  //add one specific student to a course

        bool check_student_in_course (student *stud);   //check if student exist in course or not (use Student ID)

        void remove_student_from_course (student *&stud); //remove one specific student from a course
    };



    class semester
    {
    public:
        list<course*> c;    //list of course of a semester

        multitype semester_name; //semester name

        void import_course();   //import courses from csv file (file used in this function: "19APCS1-Schedule.csv")

        multitype get_semester_name (); //get semester name

        void add_course (course *crse); //add non-data course to list of course c above

        void add_course_manually (); //add course + data to course list

        void set_course_data_manually(course *&crse); //set course data from keyboard (edit a course)

        void delete_course (course *&crse); //delete a course from a list course (in the same semester)

        void view_course ();   //view course list of a semester

        void update_course (course *&crse); //update, edit a specific course data
    };



    class academic_year
    {
    public:
        list<semester*> s;  //list of semesters in 1 year

        multitype school_year; //school year

        multitype get_school_year (); // get school year name multitype -> convert to_str() to print

        void set_school_year (const multitype &name); // update school_year or set a name to a school year

        void add_semester (semester *&sem); //add semester to a specific year

        void delete_semester(semester *&sem); //delete a specific semester from a year

        void view_semester();   //view list of semesters in 1 year
    };



    class school
    {
    public:
        list<academic_year*> a; //list of school years

        void add_year (academic_year *y);   //add new school year

        void delete_academic_year (academic_year *&y);  //delete  a school year

        void view_academic_year();  // view list of school years
    };

    class lecturer
    {
    public:
        multitype data[4]; //username, name, degree, gender
    };

    course* create_course();    //create a new non-data course

    semester* create_semester();    //create a new non-data semester

    academic_year* create_academic_year();  //create a non-data academic year

    student* create_student();  //create a new non-data student

    void view_list_course_current(school *sch); //view list of courses in current semester

    extern list<lecturer*> lect;    //list of lecturers

    lecturer* create_lecturer (); //create one new non-data lecturer

    void add_lecturer (lecturer *new_lec); //add one lecturer to the list of lecturers

    void create_lecturer_list(); //create a list of lecturers from courses csv file
                                 //This file used in this function was 19APCS1-Schedule.csv

    bool check_exist_lecturer_in_list(lecturer *new_lec);   //check if the lecturer is in list or not
                                                        //check by using username because difference lecturers have difference usernames

    void view_lecturer_list();  //view the list of lecturers

    bool set_lecturer_data(lecturer *&new_lec); //set one lecturer data after checking lecturer exist in list before or not

    void add_lecturer_manually(); //add one lecturer to the list - entered by keyboard

    void update_lecturer(lecturer *&new_lec);   //update one lecturer data

    void delete_lecturer(lecturer *&new_lec);   //delete one lecturer from the list
};
#endif // COURSES_H
