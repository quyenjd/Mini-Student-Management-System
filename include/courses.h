#ifndef COURSES_H
#define COURSES_H
#include "csv.h"
using namespace Csv;
using namespace std;
namespace SMS
{

    class student {
    public:
        multitype data[5];
    };

    class course
    {
    public:
        list<student*> st;
        /*multitype no;
        multitype course_id,course_name,course_class;
        multitype lec_user,lec_name,lec_degree,lec_gender;
        multitype st_date,en_date,day_of_week,st_hour,st_minute,en_hour,en_minute;
        multitype room;*/

        multitype data[16];
        void add_student(student *&stud);
        void view_student_list();
        void add_student_to_course ();
        bool check_student_in_course (student *stud);
        void remove_student_from_course (student *&stud);
    };



    class semester
    {
    public:
        list<course*> c;
        multitype semester_name;

        void import_course();
        multitype get_semester_name ();
        void add_course (course *crse);
        void add_course_manually ();
        void set_course_data_manually(course *&crse); //set course data or update a course (edit a course)
        void delete_course (course *&crse);
        void view_course ();
        void update_course (course *&crse);
    };



    class academic_year
    {
    public:
        list<semester*> s;
        multitype school_year;
        multitype get_school_year (); // get school year name multitype -> convert to_str() to print
        void set_school_year (const multitype &name); // or update school_year or set a name to a school year
        void add_semester (semester *&sem);
        void delete_semester(semester *&sem);
        void view_semester();
    };



    class school
    {
    public:
        list<academic_year*> a;

        void add_year (academic_year *y);
        void delete_academic_year (academic_year *&y);
        void view_academic_year();
    };

    course* create_course();
    semester* create_semester();
    academic_year* create_academic_year();
    student* create_student();

};
#endif // COURSES_H
