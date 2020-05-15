#ifndef COURSES_H
#define COURSES_H
#include "csv.h"
using namespace Csv;
using namespace std;
namespace SMS
{
    struct student {};
    class course
    {
<<<<<<< Updated upstream
        list<student*> st;
        multitype no;
=======
    public:
        list<student*> st;
        /*multitype no;
>>>>>>> Stashed changes
        multitype course_id,course_name,course_class;
        multitype lec_user,lec_name,lec_degree,lec_gender;
        multitype st_date,en_date,day_of_week,st_hour,st_minute,en_hour,en_minute;
        multitype room;*/

        multitype data[16];

    };



    class semester
    {
    public:
        list<course*> c;
<<<<<<< Updated upstream

        void import_course();
=======
        multitype semester_name;

        void import_course();
        multitype get_semester_name ();
        void add_course (course *crse);
        void add_course_manually ();
        void set_course_data_manually(course *&crse); //set course data or update a course (edit a course)
        void delete_course (course *&crse);
>>>>>>> Stashed changes
    };



    class academic_year
    {
    public:
<<<<<<< Updated upstream
<<<<<<< Updated upstream
        //constructor
        //academic_year();
=======
>>>>>>> Stashed changes
        list<semester*> s;
        multitype school_year;

        void add_semester (semester *sem);
<<<<<<< Updated upstream
        multitype get_school_year ();
        void set_school_year (const multitype &name); // or update school_year
=======
        multitype get_school_year (); // get school year name multitype -> convert to_str() to print
        void set_school_year (const multitype &name); // or update school_year or set a name to a school year
        void delete_semester(semester *sem);
        void view_semester();
>>>>>>> Stashed changes
=======
        list<semester*> s;
        multitype school_year;
        multitype get_school_year (); // get school year name multitype -> convert to_str() to print
        void set_school_year (const multitype &name); // or update school_year or set a name to a school year
        void add_semester (semester *&sem);
        void delete_semester(semester *&sem);
        void view_semester();
>>>>>>> Stashed changes
    };



    class school
    {
<<<<<<< Updated upstream
        list<academic_year*> a;
<<<<<<< Updated upstream
        void add_year (academic_year *y);
        void delete_academic_year (academic_year *year);
=======

        void add_year (academic_year *y);
        void delete_academic_year (academic_year *year);
        void view_academic_year();
>>>>>>> Stashed changes
=======
    public:
        list<academic_year*> a;

        void add_year (academic_year *y);
        void delete_academic_year (academic_year *&y);
        void view_academic_year();
>>>>>>> Stashed changes
    };

    course* create_course();
    semester* create_semester();
    academic_year* create_academic_year();

};
#endif // COURSES_H
