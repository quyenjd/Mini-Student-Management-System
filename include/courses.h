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

   // void view_list_course_current(school *sch); //view list of courses in current semester

/*    extern list<lecturer*> lect;    //list of lecturers

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

    void delete_lecturer(lecturer *&new_lec);   //delete one lecturer from the list*/
};
#endif // COURSES_H
