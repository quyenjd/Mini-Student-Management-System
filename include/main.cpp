#include <iostream>
#include "csv.h"

using namespace std;
using namespace Csv;

void welcomeMessage();
void login();
void userLogout();
void menu();

struct StudentInfo {
	bool isStudent = true;
	char* user = new char[20];
	char* pass = new char[20];
	string fullName, dob, classID;
};
StudentInfo info;

bool loadProfileInfo(StudentInfo &info) {
	csv_handler student("19APCS1-Student.csv");
	if (!student.init_read()) {
		cout << "Error!";
		return false;
	}
	student.read_and_terminate();
	if (student.get_table().get_row_where("Student ID", info.user).empty()) return false;
	info.fullName = student.get_table().get_row_where("Student ID", info.user).at(2).to_str();
	info.dob = student.get_table().get_row_where("Student ID", info.user).at(3).to_str();
	info.classID = student.get_table().get_row_where("Student ID", info.user).at(4).to_str();
}
bool checkLogin(){
	csv_handler student("idpass.csv");
	if (!student.init_read()) {
		cout << "Error!";
		return false;
	}
	student.read_and_terminate();
	if (!student.get_table().get_row_where("ID", info.user).empty() && student.get_table().get_row_where("ID", info.user).at(2).equal(info.pass))
	{
		if (!student.get_table().get_row_where("ID", info.user).at(3).equal("Student")) info.isStudent = false;
		loadProfileInfo(info);
		return true;
	}else return false;
}
string getName(){
    return info.fullName;
}
void profileInfo() {
	cout << endl << "                       USER INFORMATION" << endl;
	cout << "      User ID: ";
	for (int i = 0; i < 20; i++) if (info.user[i] != '\0') cout << info.user[i]; else break;
	cout << endl << "      Full name: " + info.fullName;
	cout << endl << "      Date of birth: " + info.dob;
	cout << endl << "      Class: " + info.classID;
	cout << endl << "      Role: " << (info.isStudent ? "Student" : "Teacher") << endl;
	cout << endl << "              Continue using the application? (y/n)";
	char ans = '1';
	while (ans != 'y' && ans != 'n') cin >> ans;
	if (ans == 'y') menu();
}
void changePass(){
	char* pass = new char[20];
	char* pass2 = new char[20];
	cout << "      Password: ";
	cin >> pass;
	cout << "      Confirm Password: ";
	cin >> pass2;
	bool checkPass = true;
	for (int i = 0; i < 20; i++) {
		if (pass[i] != pass2[i]) checkPass = false;
		if (pass[i] == '\0' || pass2[i] == '\0') break;
	}
	if (checkPass) {
		csv_handler student("idpass.csv");
		if (!student.init_read()) {
			cout << "Error!";
			return;
		}
		student.read_and_terminate();
		student.get_table().get_row_where("ID", info.user).at(2).assign(pass);
		if (!student.init_write()) {
			cout << "Error!";
			return;
		}
		student.write_and_terminate();
		cout << endl << "                 YOU HAVE SUCCESSFULLY CHANGED YOUR PASSWORD" << endl;
		userLogout();
	}
	else {
		cout << endl << "                 WARNING: Your confirm password did not match";
		changePass();
	}
}
void userLogout(){
	info.user = new char[20];
	info.pass = new char[20];
	welcomeMessage();
}
void menu(){
    cout<<"-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-"<<endl;
    cout<<"     ___ ___   ____  ____  ____       ____   ____   ____    ___ "<<endl;
    cout<<"    |   |   | /    ||    ||    \\     |    \\ /    | /    |  /  _]"<<endl;
    cout<<"    | _   _ ||  o  | |  | |  _  |    |  o  )  o  ||   __| /  [_ "<<endl;
    cout<<"    |  \\_/  ||     | |  | |  |  |    |   _/|     ||  |  ||    _]"<<endl;
    cout<<"    |   |   ||  _  | |  | |  |  |    |  |  |  _  ||  |_ ||   [_ "<<endl;
    cout<<"    |   |   ||  |  | |  | |  |  |    |  |  |  |  ||     ||     |"<<endl;
    cout<<"    |___|___||__|__||____||__|__|    |__|  |__|__||___,_||_____|"<<endl;
    cout<<"-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-"<<endl;
    cout<<"                  W E L C O M E "<<getName()<<endl;
    cout<<"      1. Your profile information"<<endl;
    cout<<"      2. Change your password"<<endl;
    cout<<"      3. Logout"<<endl;
    cout<<endl<<"Choose your option: ";
    int i = -1;
    while(i > 3 || i < 0) cin>>i;
    if(i == 1) profileInfo();
    else if(i == 2) changePass();
    else if(i == 3) userLogout();
}

void loginPanel() {
	cout << "                       L O G I N    P A N E L" << endl;
	cout << "                   You have an account yet? (y/n)";
	char ans = '1';
	while (ans != 'y' && ans != 'n') cin >> ans;
	if (ans == 'y') login();
	//Out luon
}
void login(){
    cout<<"       StudentID: ";
    cin>>info.user;
    cout<<"       Password: ";
    cin>>info.pass;
    if(checkLogin()){
        menu();
    }else{
        cout<<"       You entered the wrong password or the ID did not exist, please try again"<<endl;
		loginPanel();
    }
}

void welcomeMessage(){
    cout<<"======================================================================"<<endl;
    cout<<"=  _____ _             _            _    ______          _        _  ="<<endl;
    cout<<"= /  ___| |           | |          | |   | ___ \\        | |      | | ="<<endl;
    cout<<"= \\ `--.| |_ _   _  __| | ___ _ __ | |_  | |_/ /__  _ __| |_ __ _| | ="<<endl;
    cout<<"=  `--. \\ __| | | |/ _` |/ _ \\ '_ \\| __| |  __/ _ \\| '__| __/ _` | | ="<<endl;
    cout<<"= /\\__/ / |_| |_| | (_| |  __/ | | | |_  | | | (_) | |  | || (_| | | ="<<endl;
    cout<<"= \\____/ \\__|\\__,_|\\__,_|\\___|_| |_|\\__| \\_|  \\___/|_|   \\__\\__,_|_| ="<<endl;
    cout<<"======================================================================"<<endl;
	loginPanel();
}

int main()
{
    welcomeMessage();
    return 0;
}
