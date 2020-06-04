#ifndef SCOREBOARD_QUYENJD_H
#define SCOREBOARD_QUYENJD_H

#include "csv.h"

namespace SMS
{
    void import_scoreboard();
    void edit_scoreboard();
    void view_scoreboard();
    void student_view_scoreboard (const Csv::multitype& studentID);
    void export_scoreboard_to_csv();
}

#endif // SCOREBOARD_QUYENJD_H
