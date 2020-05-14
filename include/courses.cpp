#include "courses.h"
#include <iostream>
using namespace Csv;
using namespace std;
namespace SMS
{

    academic_year::academic_year()
    {
        for (int i=0;i<3;i++) s[i] = semester();
    }

    academic_year* create_academic_year() {
        academic_year *y = new academic_year();
        return y;
    }

    void school::add_year(academic_year *y)
    {
        a.push_back(y);
    }
};
