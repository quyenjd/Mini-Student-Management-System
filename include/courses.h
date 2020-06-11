#ifndef COURSES_H
#define COURSES_H
#include "csv.h"
#include "interface.h"
#include "csv_import.h"

namespace SMS
{
    using namespace Csv;
    using namespace std;

    void create_academic_year();    // create new academic year

    void add_new_semester_to_academic_year();   // create a semester and add to one specific academic year

    void create_new_course_manually();  // add new course to courses.csv manually

    void update_course_manually();  // update a course in courses.csv manually // edit a course

    void delete_course();   // delete a course in courses.csv

    void update_academic_year_name();   // change name of an academic year

    void update_semester_name();    // change name of an semester

    void add_student_to_course();   // add new student to a course (choose course from menu)

    void remove_student_from_course(); // remove student from a course (choose course from menu)

    void add_lecturer_to_course(); // add new lecturer to a course (choose course from menu)

    void remove_lecturer_from_course(); // remove lecturer from a course (choose course from menu)

    void delete_semester_from_academic_year(); // like name of function

    void add_course_to_semester(); // add a course to a semester (choose semester from menu)

    void view_students_of_course(); // Choose a course and view list of students

    void delete_course_from_semester(); // like name of function

    void view_course_of_semester(); // view list courses in a semester

    void import_course_from_csv();  // import course from csv to a semester

    void view_schedule_of_student(multitype student_id);    // view student's schedule

    void view_all_academic_year(); // view list of academic year

    void view_semester_in_academic_year(); // view list semester in a academic year

    void delete_academic_year(); // delete academic year

};
#endif // COURSES_H
