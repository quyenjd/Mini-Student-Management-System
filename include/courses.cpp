#include "courses.h"
#include <iostream>
using namespace Csv;
using namespace std;
namespace SMS
{

<<<<<<< Updated upstream
    academic_year* create_academic_year() {
=======
    academic_year* create_academic_year() {  //check
>>>>>>> Stashed changes
        academic_year *y = new academic_year();
        return y;
    }

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
        semester *s= new semester();
        return s;
    }

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
        csv_handler course_file("19APCS1-Schedule.csv");
        if (!course_file.init_read()) {
            cout << "Error!";
            return;
        }
        course_file.read_and_terminate();
>>>>>>> Stashed changes
    }

};
