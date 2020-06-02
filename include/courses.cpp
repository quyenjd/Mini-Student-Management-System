#include "courses.h"
#include <iostream>
using namespace Csv;
using namespace std;
namespace SMS
{
    void create_academic_year() {   //checked
        csv_handler year_file("years.csv");
        year_file.init_read();
        year_file.read_and_terminate();

        Interface::input_menu menu;
        menu.set_title("School Year");
        menu.add_item("School Year",true);
        list<multitype> res=menu.print_menu_and_wait();

        for (int i=0;i<year_file.get_table().num_rows();i++) {
            if (year_file.get_table().get_row(i).at(1).equal(res.at(0))) {
                cout << "This school year has already been in the list";
                return;
            }
        }
        year_file.get_table().add_row();
        year_file.get_table().get_row(year_file.get_table().num_rows()-1).at(0).assign(year_file.get_table().num_rows());
        year_file.get_table().get_row(year_file.get_table().num_rows()-1).at(1).assign(res.at(0));
        year_file.init_write();
        year_file.write_and_terminate();
    }

    void add_new_semester_to_academic_year() {
        csv_handler year_file("years.csv");
        year_file.init_read();
        year_file.read_and_terminate();

        csv_handler yearsemester_file("yearsemester.csv");
        yearsemester_file.init_read();
        yearsemester_file.read_and_terminate();

        csv_handler semester_file("semesters.csv");
        semester_file.init_read();
        semester_file.read_and_terminate();

        Interface::select_menu year_menu;
        year_menu.set_title("School Year");

        //Show menu years to choose
        for (int i=0;i<year_file.get_table().num_rows();i++) {
            year_menu.add_item(i+1,year_file.get_table().get_row(i).at(1));
        }

        year_menu.add_item(year_file.get_table().num_rows()+1,"Exit");
        int select;

        //Choosing a specific year
        do {
            select=year_menu.print_menu_and_wait().to_int();
            if (select>=1 && select<=year_file.get_table().num_rows()) {
                Interface::input_menu menu;
                menu.set_title("Semesters");
                menu.add_item("Semester name",true);

                list<multitype> res=menu.print_menu_and_wait(false);

                for (int j=0;j<semester_file.get_table().num_rows();j++) {
                    if (semester_file.get_table().get_row(j).at(1).equal(res.at(0))) {
                        cout << "This semester has already been in this school year" << endl;
                        return;
                    }
                }

                //add semester to yearsemester.csv
                yearsemester_file.get_table().add_row();
                yearsemester_file.get_table().get_row(yearsemester_file.get_table().num_rows()-1).at(0).assign(select-1);
                yearsemester_file.get_table().get_row(yearsemester_file.get_table().num_rows()-1).at(1).assign(yearsemester_file.get_table().num_rows());

                //add semester to semesters.csv
                semester_file.get_table().add_row();
                semester_file.get_table().get_row(semester_file.get_table().num_rows()-1).at(0).assign(yearsemester_file.get_table().get_row(yearsemester_file.get_table().num_rows()-1).at(1));
                semester_file.get_table().get_row(semester_file.get_table().num_rows()-1).at(1).assign(res.at(0));
            }
        } while (select!=year_file.get_table().num_rows()+1);

        yearsemester_file.init_write();
        yearsemester_file.write_and_terminate();

        semester_file.init_write();
        semester_file.write_and_terminate();
    }


    void create_new_course_manually() {
        csv_handler course_file("courses.csv");
        course_file.init_read();
        course_file.read_and_terminate();

        Interface::input_menu menu;
        menu.set_title("Course Information");
        menu.add_item("Course ID",false);
        menu.add_item("Course Name",true);
        menu.add_item("Class",false);
        menu.add_item("Start Date",false);
        menu.add_item("End Date",false);
        menu.add_item("Day of Week",false);
        menu.add_item("Start hour", false);
        menu.add_item("Start Minute",false);
        menu.add_item("End hour",false);
        menu.add_item("End Minute",false);
        menu.add_item("Room",false);

        list<multitype> res=menu.print_menu_and_wait();

        for (int i=0;i<course_file.get_table().num_rows();i++) {
            if (course_file.get_table().get_row(i).at(1).equal(res.at(1))) {
                cout << "This course has already been in the list" << endl;
                return;
            }
        }

        course_file.get_table().add_row();
        for (int j=0;j<12;j++) course_file.get_table().get_row(course_file.get_table().num_rows()-1).at(j).assign(res.at(j));

        course_file.init_write();
        course_file.write_and_terminate();
    }

    void update_course_manually() {
        csv_handler course_file ("courses.csv");
        course_file.init_read();
        course_file.read_and_terminate();

        Interface::select_menu course_menu;
        course_menu.set_title("Courses");
        for (int i=0;i<course_file.get_table().num_rows();i++) {
            course_menu.add_item(i+1,course_file.get_table().get_row(i).at(1));
        }
        course_menu.add_item(course_file.get_table().num_rows()+1,"Exit");
        int select;

        do {
            select=course_menu.print_menu_and_wait().to_int();
            if (select >=1 && select <= course_file.get_table().num_rows()) {

                Interface::input_menu menu;

                menu.set_title("Course Information");
                menu.add_item("Course ID",false);
                menu.add_item("Course Name",true);
                menu.add_item("Class",false);
                menu.add_item("Start Date",false);
                menu.add_item("End Date",false);
                menu.add_item("Day of Week",false);
                menu.add_item("Start hour", false);
                menu.add_item("Start Minute",false);
                menu.add_item("End hour",false);
                menu.add_item("End Minute",false);
                menu.add_item("Room",false);

                list<multitype> res=menu.print_menu_and_wait();

                for (int j=0;j<12;j++) course_file.get_table().get_row(select-1).at(j).assign(res.at(j));
                break;
            }
        } while (select != course_file.get_table().num_rows()+1);


        course_file.init_write();
        course_file.write_and_terminate();
    }

    void delete_course() {
        csv_handler course_file("courses.csv");
        course_file.init_read();
        course_file.read_and_terminate();

        Interface::select_menu course_menu;
        course_menu.set_title("Courses");
        for (int i=0;i<course_file.get_table().num_rows();i++) {
            course_menu.add_item(i+1,course_file.get_table().get_row(i).at(1));
        }
        course_menu.add_item(course_file.get_table().num_rows()+1,"Exit");

        int select;
        do {
            select=course_menu.print_menu_and_wait().to_int();
            if (select>=1 && select <= course_file.get_table().num_rows()) {
                course_file.get_table().rm_row(select-1);
                break;
            }
        } while (select != course_file.get_table().num_rows()+1);

    }

    void update_academic_year_name() {
        csv_handler year_file("years.csv");
        year_file.init_read();
        year_file.read_and_terminate();

        Interface::select_menu year_menu;
        year_menu.set_title("School Year");

        //Show menu years to choose
        for (int i=0;i<year_file.get_table().num_rows();i++) {
            year_menu.add_item(i+1,year_file.get_table().get_row(i).at(1));
        }

        year_menu.add_item(year_file.get_table().num_rows()+1,"Exit");
        int select;

        do {
            select=year_menu.print_menu_and_wait().to_int();
            if (select>=1 && select <=year_file.get_table().num_rows()) {
                Interface::input_menu year_update_menu;
                year_update_menu.set_title("School Year");
                year_update_menu.add_item("New School Year",true);
                list<multitype> res=year_update_menu.print_menu_and_wait();

                year_file.get_table().get_row(select-1).at(1).assign(res.at(0));
                break;
            }
        } while (select != year_file.get_table().num_rows()+1);

        year_file.init_write();
        year_file.write_and_terminate();
    }

    void update_semester_name() {
        csv_handler semester_file("semesters.csv");
        semester_file.init_read();
        semester_file.read_and_terminate();

        Interface::select_menu semester_menu;
        semester_menu.set_title("Semesters");
        for (int i=0;i<semester_file.get_table().num_rows();i++) {
            semester_menu.add_item(i+1,semester_file.get_table().get_row(i).at(1));
        }
        semester_menu.add_item(semester_file.get_table().num_rows()+1,"Exit");
        int select;
        do {
            select=semester_menu.print_menu_and_wait().to_int();
            if (select >=1 && select <= semester_file.get_table().num_rows()) {

                Interface::input_menu semester_update_menu;
                semester_update_menu.set_title("Semesters");
                semester_update_menu.add_item("Semester",true);

                list<multitype> res=semester_update_menu.print_menu_and_wait();

                semester_file.get_table().get_row(select-1).at(1).assign(res.at(0));
                break;
            }
        } while (select != semester_file.get_table().num_rows()+1);
        semester_file.init_write();
        semester_file.write_and_terminate();
    }

    void add_student_to_course() {
        csv_handler student_file ("students.csv");
        student_file.init_read();
        student_file.read_and_terminate();

        csv_handler coursestudent_file ("coursestudent.csv");
        coursestudent_file.init_read();
        coursestudent_file.read_and_terminate();

        csv_handler course_file ("courses.csv");
        course_file.init_read();
        course_file.read_and_terminate();

        Interface::select_menu course_menu;
        course_menu.set_title("Courses");
        for (int i=0;i<course_file.get_table().num_rows();i++) {
            course_menu.add_item(i+1,course_file.get_table().get_row(i).at(0));
        }
        course_menu.add_item(course_file.get_table().num_rows()+1,"Exit");

        int select;

        do {
            select=course_menu.print_menu_and_wait().to_int();
            if (select >=1 && select <= course_file.get_table().num_rows()) {
                Interface::input_menu student_menu;
                student_menu.set_title("Student's Information");
                student_menu.add_item("Student ID",false);
                student_menu.add_item("Fullname",true);
                student_menu.add_item("Date of Birth",false);
                student_menu.add_item("Class",false);
                list<multitype> res=student_menu.print_menu_and_wait();

                for (int i=0;i<coursestudent_file.get_table().num_rows();i++) {
                    if (coursestudent_file.get_table().get_row(i).at(0).equal(course_file.get_table().get_row(select-1).at(0)) && coursestudent_file.get_table().get_row(i).at(1).equal(res.at(0))) {
                        cout << "This student has already been in this course" << endl;
                        return;
                    }
                }

                //add student to coursestudent.csv
                coursestudent_file.get_table().add_row();
                coursestudent_file.get_table().get_row(coursestudent_file.get_table().num_rows()-1).at(0).assign(course_file.get_table().get_row(select-1).at(0));
                coursestudent_file.get_table().get_row(coursestudent_file.get_table().num_rows()-1).at(1).assign(res.at(0));

                //add student to student.csv

                for (int i=0;i<student_file.get_table().num_rows();i++) {
                    if (student_file.get_table().get_row(i).at(0).equal(res.at(0))) return;
                }

                student_file.get_table().add_row();
                for (int i=0;i<4;i++) {
                    student_file.get_table().get_row(student_file.get_table().num_rows()-1).at(i).assign(res.at(i));
                }
                break;
            }
        } while (select != course_file.get_table().num_rows()+1);

        coursestudent_file.init_write();
        coursestudent_file.write_and_terminate();

        student_file.init_write();
        student_file.write_and_terminate();
    }

    void remove_student_from_course() {
        csv_handler course_file ("courses.csv");
        course_file.init_read();
        course_file.read_and_terminate();

        csv_handler coursestudent_file("coursestudent.csv");
        coursestudent_file.init_read();
        coursestudent_file.read_and_terminate();

        Interface::select_menu course_menu;
        course_menu.set_title("Courses");
        for (int i=0;i<course_file.get_table().num_rows();i++) {
            course_menu.add_item(i+1,course_file.get_table().get_row(i).at(0));
        }
        course_menu.add_item(course_file.get_table().num_rows()+1,"Exit");

        int select;

        do {
            select=course_menu.print_menu_and_wait().to_int();
            if (select>=1 && select <= course_file.get_table().num_rows()) {
                Interface::input_menu student_menu;
                student_menu.add_item("Student Remove ID",false);
                list<multitype> res=student_menu.print_menu_and_wait();

                for (int i=0;i<coursestudent_file.get_table().num_rows();i++) {
                    if (coursestudent_file.get_table().get_row(i).at(1).equal(res.at(0)) && coursestudent_file.get_table().get_row(i).at(0).equal(course_file.get_table().get_row(select-1).at(0))) {
                        coursestudent_file.get_table().rm_row(i);
                    }
                }
                break;
            }
        } while (select != course_file.get_table().num_rows()+1);
        coursestudent_file.init_write();
        coursestudent_file.write_and_terminate();
    }

    void add_lecturer_to_course() {
        csv_handler lecturer_file ("lecturers.csv");
        lecturer_file.init_read();
        lecturer_file.read_and_terminate();

        csv_handler courselecturer_file ("courselecturer.csv");
        courselecturer_file.init_read();
        courselecturer_file.read_and_terminate();

        csv_handler course_file ("courses.csv");
        course_file.init_read();
        course_file.read_and_terminate();

        Interface::select_menu course_menu;
        course_menu.set_title("Courses");
        for (int i=0;i<course_file.get_table().num_rows();i++) {
            course_menu.add_item(i+1,course_file.get_table().get_row(i).at(0));
        }
        course_menu.add_item(course_file.get_table().num_rows()+1,"Exit");

        int select;

        do {
            select=course_menu.print_menu_and_wait().to_int();
            if (select >=1 && select <= course_file.get_table().num_rows()) {
                Interface::input_menu lecturer_menu;
                lecturer_menu.set_title("Lecturer's Information");
                lecturer_menu.add_item("Lecturer username",false);
                lecturer_menu.add_item("Fullname",true);
                lecturer_menu.add_item("Degree",false);
                lecturer_menu.add_item("Gender",false);
                list<multitype> res=lecturer_menu.print_menu_and_wait();

                for (int i=0;i<courselecturer_file.get_table().num_rows();i++) {
                    if (courselecturer_file.get_table().get_row(i).at(0).equal(course_file.get_table().get_row(select-1).at(0)) && courselecturer_file.get_table().get_row(i).at(1).equal(res.at(0))) {
                        cout << "This lecturer has already been in this course" << endl;
                        return;
                    }
                }

                //add lecturer to courselecturer.csv
                courselecturer_file.get_table().add_row();
                courselecturer_file.get_table().get_row(courselecturer_file.get_table().num_rows()-1).at(0).assign(course_file.get_table().get_row(select-1).at(0));
                courselecturer_file.get_table().get_row(courselecturer_file.get_table().num_rows()-1).at(1).assign(res.at(0));

                //add lecturer to lecturer.csv

                for (int i=0;i<lecturer_file.get_table().num_rows();i++) {
                    if (lecturer_file.get_table().get_row(i).at(0).equal(res.at(0))) return;
                }

                lecturer_file.get_table().add_row();
                for (int i=0;i<4;i++) {
                    lecturer_file.get_table().get_row(lecturer_file.get_table().num_rows()-1).at(i).assign(res.at(i));
                }
                break;
            }
        } while (select != course_file.get_table().num_rows()+1);

        courselecturer_file.init_write();
        courselecturer_file.write_and_terminate();

        lecturer_file.init_write();
        lecturer_file.write_and_terminate();
    }

    void remove_lecturer_from_course() {
        csv_handler course_file ("courses.csv");
        course_file.init_read();
        course_file.read_and_terminate();

        csv_handler courselecturer_file("courselecturer.csv");
        courselecturer_file.init_read();
        courselecturer_file.read_and_terminate();

        Interface::select_menu course_menu;
        course_menu.set_title("Courses");
        for (int i=0;i<course_file.get_table().num_rows();i++) {
            course_menu.add_item(i+1,course_file.get_table().get_row(i).at(0));
        }
        course_menu.add_item(course_file.get_table().num_rows()+1,"Exit");

        int select;

        do {
            select=course_menu.print_menu_and_wait().to_int();
            if (select>=1 && select <= course_file.get_table().num_rows()) {
                Interface::input_menu lecturer_menu;
                lecturer_menu.add_item("Lecturer Remove Username",false);
                list<multitype> res=lecturer_menu.print_menu_and_wait();

                for (int i=0;i<courselecturer_file.get_table().num_rows();i++) {
                    if (courselecturer_file.get_table().get_row(i).at(1).equal(res.at(0)) && courselecturer_file.get_table().get_row(i).at(0).equal(course_file.get_table().get_row(select-1).at(0))) {
                        courselecturer_file.get_table().rm_row(i);
                    }
                }
                break;
            }
        } while (select != course_file.get_table().num_rows()+1);
        courselecturer_file.init_write();
        courselecturer_file.write_and_terminate();
    }

    void delete_semester_from_academic_year() {
        csv_handler year_file("years.csv");
        year_file.init_read();
        year_file.read_and_terminate();

        csv_handler yearsemester_file("yearsemester.csv");
        yearsemester_file.init_read();
        yearsemester_file.read_and_terminate();

        csv_handler semester_file("semesters.csv");
        semester_file.init_read();
        semester_file.read_and_terminate();

        Interface::select_menu year_menu;
        year_menu.set_title("School Year");

        //Show menu years to choose
        for (int i=0;i<year_file.get_table().num_rows();i++) {
            year_menu.add_item(i+1,year_file.get_table().get_row(i).at(1));
        }

        year_menu.add_item(year_file.get_table().num_rows()+1,"Exit");
        int select_year;

        //Choosing a specific year
        do {
            select_year=year_menu.print_menu_and_wait().to_int();
            if (select_year>=1 && select_year<=year_file.get_table().num_rows()) {
                Interface::select_menu semester_menu;
                semester_menu.set_title("Semesters");
                int cnt=0;
                for (int i=0;i<yearsemester_file.get_table().num_rows();i++) {
                    if (yearsemester_file.get_table().get_row(i).at(0).equal(year_file.get_table().get_row(select_year-1).at(0))) {
                        cnt++;
                        semester_menu.add_item(cnt,semester_file.get_table().get_row_where("Semester ID",yearsemester_file.get_table().get_row(i).at(1)).at(1));
                    }
                }
                semester_menu.add_item(cnt+1,"Exit");

                int select_semester;
                do {
                    select_semester=semester_menu.print_menu_and_wait().to_int();
                    if (select_semester >=1 && select_semester <= cnt) {
                        //yearsemester_file.get_table().rm_row_where()
                        //semester_file.get_table().rm_row_where("Semester name",)
                    }
                } while (select_semester != cnt+1);
            }
        } while (select_year!=year_file.get_table().num_rows()+1);
        yearsemester_file.init_write();
        yearsemester_file.write_and_terminate();

        semester_file.init_write();
        semester_file.write_and_terminate();
    }

    void add_course_to_semester() {

    }

    void view_students_of_course() {
        csv_handler student_file ("students.csv");
        student_file.init_read();
        student_file.read_and_terminate();

        csv_handler coursestudent_file ("coursestudent.csv");
        coursestudent_file.init_read();
        coursestudent_file.read_and_terminate();

        csv_handler course_file ("courses.csv");
        course_file.init_read();
        course_file.read_and_terminate();

        Interface::select_menu course_menu;
        course_menu.set_title("Courses");
        for (int i=0;i<course_file.get_table().num_rows();i++) {
            course_menu.add_item(i+1,course_file.get_table().get_row(i).at(0));
        }
        course_menu.add_item(course_file.get_table().num_rows()+1,"Exit");

        int select;


    }
};
