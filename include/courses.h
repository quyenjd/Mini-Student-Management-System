#ifndef COURSES_H
#define COURSES_H
#include "csv.h"
#include "interface.h"
using namespace Csv;
using namespace std;
namespace SMS
{
    void create_academic_year();

    void add_new_semester_to_academic_year();

    void create_new_course_manually();

    void update_course_manually();

    void delete_course();

    void update_academic_year_name();

    void update_semester_name();

    void add_student_to_course();

    void remove_student_from_course();

    void add_lecturer_to_course();

    void remove_lecturer_from_course();

    void delete_semester_from_academic_year();

    void add_course_to_semester();

    void view_students_of_course();
};
#endif // COURSES_H
