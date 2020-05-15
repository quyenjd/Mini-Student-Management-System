#ifndef COURSES_H
#define COURSES_H
#include "csv.h"
using namespace Csv;
using namespace std;
namespace SMS
{
    struct student {};
    struct course
    {
        list<student*> s;
        multitype no;
        multitype course_id,course_name,course_class;
        multitype lec_user,lec_name,lec_degree,leg_gender;
        multitype st_date,en_date,day_of_week,st_hour,st_minute,en_hour,en_minute;
    };



    class semester
    {
    public:
        list<course*> c;
    };



    class academic_year
    {
    public:
        //constructor
        //academic_year();
        list<semester*> s;
        multitype school_year;

        void add_semester (semester *sem);
        multitype get_school_year ();
        void set_school_year (const multitype &name); // or update school_year
    };



    class school
    {
        list<academic_year*> a;
        void add_year (academic_year *y);
        void delete_academic_year (academic_year *year);
    };

    course* create_course();
    semester* create_semester();
    academic_year* create_academic_year();

};
#endif // COURSES_H
