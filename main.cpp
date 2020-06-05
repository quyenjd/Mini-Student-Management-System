#include <iostream>
#include "csv.h"
#include "interface.h"
#include "csv_import.h"
#include "class.h"
#include "courses.h"
#include "lecturer.h"
#include "scoreboard.h"
#include "attendancelist.h"

using namespace std;
using namespace Csv;
using namespace Interface;
using namespace SMS;

multitype authorized_userid, authorized_role;

/* OPERATIONS (quyen) */
void operations_driver (int N, multitype *operations, void (*functions[])(), multitype title);

void staff_menu__student();
void staff_menu__class();
void staff_menu__year();
void staff_menu__semester();
void staff_menu__course();
void staff_menu__lecturer();
void staff_menu__scoreboard();
void staff_menu__attendance_list();
void staff_menu();

void lecturer_menu();

void student_menu__checkin();
void student_menu__view_checkin();
void student_menu__view_schedules();
void student_menu__view_scoreboard();
void student_menu();

/* OTHER FUNCTIONS (tuong) */
bool checkLogin (const multitype& username, const multitype& password);
void login();
void homepage();
bool lecturer_filter (multitype column, list<multitype> row, table tabl);
bool student_filter (multitype column, list<multitype> row, table tabl);
void profile_info();
void change_password();
void logout();



/* === OPERATIONS (quyen) === */

void operations_driver (int N, multitype *operations, void (*functions[])(), multitype title)
{
    select_menu select;
    select.set_title(title);
    for (int i = 0; i < N; ++i)
        select.add_item(i + 1, operations[i]);
    select.add_item(N + 1, "Back");

    int chosen;
    do
    {
        chosen = select.print_menu_and_wait().to_int();
        if (chosen >= 1 && chosen <= N)
            functions[chosen - 1]();
    }
    while (chosen != N + 1);
}

void staff_menu__student()
{
    multitype staff_operations__student[] = {"Import students of a class from a csv file", // an
                                             "Add new student", // an
                                             "Edit a student", // an
                                             "Remove a student" // an
                                            };
    void (*__student[])() = {newClass, addStudent, editStudent, removeStudent};
    operations_driver(4, staff_operations__student, __student, "Student menu");
}

void staff_menu__class()
{
    multitype staff_operations__class[] = {"View list of classes", // an
                                           "View list of students in a class" // an
                                          };
    void (*__class[])() = {viewClass, viewStudentInClass};
    operations_driver(2, staff_operations__class, __class, "Class menu");
}

void staff_menu__year()
{
    multitype staff_operations__year[] = {"Create academic year", // dat
                                          "Edit academic year", // dat
                                          "Remove academic year", // dat
                                          "View all academic years" // dat
                                         };
    void (*__year[])() = {create_academic_year, update_academic_year_name, delete_academic_year, view_all_academic_year};
    operations_driver(4, staff_operations__year, __year, "Academic year menu");
}

void staff_menu__semester()
{
    multitype staff_operations__semester[] = {"Add new semester to academic year", // dat
                                              "Edit semester", // dat
                                              "Remove semester from academic year", // dat
                                              "View all semesters in an academic year" // dat
                                             };
    void (*__semester[])() = {add_new_semester_to_academic_year, update_semester_name,
                              delete_semester_from_academic_year, view_semester_in_academic_year};
    operations_driver(4, staff_operations__semester, __semester, "Semester menu");
}

void staff_menu__course()
{
    multitype staff_operations__course[] = {"Import courses to a semester from csv file", // dat
                                            "Add new course", // dat
                                            "Edit a course", // dat
                                            "Remove a course", // dat
                                            "Add a course to a semester", // dat
                                            "Remove a course from a semester", // dat
                                            "Add a student to a course", // dat
                                            "Remove a student from a course", // dat
                                            "View list of courses of a semester", // dat
                                            "View list of students in a course" // dat
                                           };
    void (*__course[])() = {import_course_from_csv, create_new_course_manually,
                            update_course_manually, delete_course,
                            add_course_to_semester, delete_course_from_semester,
                            add_student_to_course, remove_student_from_course,
                            view_course_of_semester, view_students_of_course};
    operations_driver(10, staff_operations__course, __course, "Course menu");
}

void staff_menu__lecturer()
{
    multitype staff_operations__lecturer[] = {"Add new lecturer", // quyen
                                              "Edit a lecturer", // quyen
                                              "Remove a lecturer", // quyen
                                              "Add a lecturer to a course", // dat
                                              "Remove a lecturer from a course", // dat
                                              "View all lecturers", // quyen
                                              "View list of lecturers in a course" // quyen
                                             };
    void (*__lecturer[])() = {add_lecturer, edit_lecturer, delete_lecturer,
                              add_lecturer_to_course, remove_lecturer_from_course,
                              view_all_lecturers, view_lecturers_of_course};
    operations_driver(7, staff_operations__lecturer, __lecturer, "Lecturer menu");
}

void staff_menu__scoreboard()
{
    multitype staff_operations__scoreboard[] = {"View the scoreboard of a course", // quyen
                                                "Export a scoreboard to a csv file" // quyen
                                               };
    void (*__scoreboard[])() = {view_scoreboard, export_scoreboard_to_csv};
    operations_driver(2, staff_operations__scoreboard, __scoreboard, "Scoreboard menu");
}

void staff_menu__attendance_list()
{
    multitype staff_operations__attendance_list[] = {"View attendance list of a course", // quyen
                                                     "Export an attendance list to a csv file" // quyen
                                                    };
    void (*__attendance_list[])() = {view_attendance_list, export_attendance_list_to_csv};
    operations_driver(2, staff_operations__attendance_list, __attendance_list, "Attendance list menu");
}

void staff_menu()
{
    multitype staff_operations__main[] = {"Student menu", "Class menu", "Academic year menu",
                                          "Semester menu", "Course menu", "Lecturer menu",
                                          "Scoreboard menu", "Attendance list menu"};
    void (*__main[])() = {staff_menu__student, staff_menu__class, staff_menu__year,
                          staff_menu__semester, staff_menu__course, staff_menu__lecturer,
                          staff_menu__scoreboard, staff_menu__attendance_list};
    operations_driver(8, staff_operations__main, __main, "Main menu");
}

void lecturer_menu()
{
    multitype lecturer_operations__main[] = {"View list of courses of a semester", // dat
                                             "View list of students in a course", // dat
                                             "View attendance list of a course", // quyen
                                             "Edit an attendance", // quyen
                                             "Import scoreboard of a course from a csv file", // quyen
                                             "Edit grade of a student", // quyen
                                             "View the scoreboard of a course" // quyen
                                            };
    void (*__main[])() = {view_course_of_semester, view_students_of_course,
                          view_attendance_list, edit_attendance,
                          import_scoreboard, edit_scoreboard, view_scoreboard};
    operations_driver(7, lecturer_operations__main, __main, "Main menu");
}

void student_menu__checkin()
{
    student_check_in(authorized_userid);
}

void student_menu__view_checkin()
{
    view_check_in(authorized_userid);
}

void student_menu__view_schedules()
{
    view_schedule_of_student(authorized_userid);
}

void student_menu__view_scoreboard()
{
    student_view_scoreboard(authorized_userid);
}

void student_menu()
{
    multitype student_operations__main[] = {"Check-in", // quyen
                                            "View my check-in result", // quyen
                                            "View my schedules", // dat
                                            "View my scoreboard" // quyen
                                           };
    void (*__main[])() = {student_menu__checkin, student_menu__view_checkin,
                          student_menu__view_schedules, student_menu__view_scoreboard};
    operations_driver(4, student_operations__main, __main, "Main menu");
}



/* === OTHER FUNCTIONS (tuong) === */

bool checkLogin (const multitype& username, const multitype& password)
{
    list<multitype> user_db = users.get_table().get_row_where("ID", username);
	if (!user_db.empty() && user_db.at(1).equal(password))
	{
	    authorized_userid = username;
	    authorized_role = user_db.at(2);
		return true;
	}
	return false;
}

void login()
{
    input_menu login_menu;
    login_menu.set_title("Login");
    login_menu.add_item("Username");
    login_menu.add_item("Password");
    select_menu select;
    select.set_title("What do you want?");
    select.add_item(1, "Login");
    select.add_item(2, "Exit");
    while (true)
    {
        int chosen = select.print_menu_and_wait().to_int();
        if (chosen == 1)
        {
            list<multitype> res = login_menu.print_menu_and_wait();
            if (checkLogin(res.at(0), res.at(1)))
            {
                print_note("You have successfully logged in.", "Success");
                pause();
                break;
            }
            else
            {
                print_note("Username or password is incorrect. Please try again.", "Failed");
                pause();
            }
        }
        else
            return;
    }
    homepage();
}

void homepage()
{
    select_menu user;
    user.set_title(multitype("Welcome ").append(authorized_role).append(" @").append(authorized_userid));
    user.add_item(1, "Main menu");
    user.add_item(2, "Profile info");
    user.add_item(3, "Change password");
    user.add_item(4, "Logout");
    while (true)
    {
        int chosen = user.print_menu_and_wait().to_int();
        if (chosen == 1)
        {
            if (authorized_role.equal("Staff"))
                staff_menu();
            else
            if (authorized_role.equal("Lecturer"))
                lecturer_menu();
            else
                student_menu();
        }
        else
        if (chosen == 2)
            profile_info();
        else
        if (chosen == 3)
            change_password();
        else
            break;
    }
    logout();
}

bool lecturer_filter (multitype column, list<multitype> row, table tabl)
{
    return row.at(tabl.get_key("Username")).equal(authorized_userid);
}

bool student_filter (multitype column, list<multitype> row, table tabl)
{
    return row.at(tabl.get_key("Student ID")).equal(authorized_userid);
}

void profile_info()
{
    if (authorized_role.equal("Staff"))
    {
        table info;
        info.add_key("Username");
        info.add_key("Role");
        info.add_row();
        info.get_row(0).at(0).assign(authorized_userid);
        info.get_row(0).at(1).assign(authorized_role);
        print_table(info, "Profile Info", false, false);
        pause();
        return;
    }
    if (authorized_role.equal("Lecturer"))
    {
        print_table(lecturers.get_table().filter(lecturer_filter), "Profile Info", false, false);
        pause();
        return;
    }
    print_table(students.get_table().filter(student_filter), "Profile Info", false, false);
    pause();
}

void change_password()
{
    input_menu change_pw;
    change_pw.set_title("Change password");
    change_pw.add_item("Old password");
    change_pw.add_item("New password");
    change_pw.add_item("Confirm new password");
    list<multitype> res = change_pw.print_menu_and_wait(),
                    &row = users.get_table().get_row_where("ID", authorized_userid);
    if (row.at(1).equal(res.at(0)))
    {
        if (res.at(1).equal(res.at(2)))
        {
            row.at(1).assign(res.at(1));
            users.init_write();
            users.write_and_terminate();
            print_note("Changed your password successfully.", "Success");
            pause();
        }
        else
        {
            print_note("Please confirm your password again.", "Failed");
            pause();
        }
    }
    else
    {
        print_note("Wrong old password. Please try again.", "Failed");
        pause();
    }
}

void logout()
{
    authorized_userid.init();
    authorized_role.init();
    login();
}



/* === DRIVER === */

int main()
{
    cout << "======================================================================" << endl
         << "=  _____ _             _            _    ______          _        _  =" << endl
         << "= /  ___| |           | |          | |   | ___ \\        | |      | | =" << endl
         << "= \\ `--.| |_ _   _  __| | ___ _ __ | |_  | |_/ /__  _ __| |_ __ _| | =" << endl
         << "=  `--. \\ __| | | |/ _` |/ _ \\ '_ \\| __| |  __/ _ \\| '__| __/ _` | | =" << endl
         << "= /\\__/ / |_| |_| | (_| |  __/ | | | |_  | | | (_) | |  | || (_| | | =" << endl
         << "= \\____/ \\__|\\__,_|\\__,_|\\___|_| |_|\\__| \\_|  \\___/|_|   \\__\\__,_|_| =" << endl
         << "======================================================================" << endl
         << endl;

    // Import all
    cout << "Importing data... ";
    init_all_csvs();
    cout << "Done!" << endl
         << endl;
    pause();

    login();
    print_note("Thank you for using this system!", "Exiting SMS...");
    pause();
    return 0;
}
