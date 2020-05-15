#include "courses.h"
#include <iostream>
using namespace Csv;
using namespace std;
namespace SMS
{

    academic_year* create_academic_year() {
        academic_year *y = new academic_year();
        return y;
    }

    void school::add_year(academic_year *y){
        a.push_back(y);
    }

    semester* create_semester() {
        semester *s= new semester();
        return s;
    }

    void academic_year::add_semester (semester *sem) {
        s.push_back(sem);
    }

    multitype academic_year::get_school_year () {
        return school_year;
    }

    void academic_year::set_school_year (const multitype &name) {
        school_year = name;
    }

    void school::delete_academic_year (academic_year *year) {
        for (int i=0;i<a.size();i++) {
            if (a.at(i) == year) a.delete_at(i);
        }
    }

};
