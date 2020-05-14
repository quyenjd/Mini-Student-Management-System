#include <iostream>

using namespace std;


bool checkLogin(char user[], char pass[]){
    return true;
}
void registerPanel(){
    char user[50],pass[50];
    cout<<"       Username: ";
    cin>>user;
    cout<<"       Password: ";
    cin>>pass;
}
string getName(){
    return "Nguyen Lam Tuong";
}
void profileInfo(){
    
}
void changePass(){
    
}
void userLogout(){
    
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
void login(){
    char user[50],pass[50];
    cout<<"       Username: ";
    cin>>user;
    cout<<"       Password: ";
    cin>>pass;
    if(checkLogin(user,pass)){
        menu();
    }else{
        cout<<"       You entered the wrong password, please try again"<<endl;
        cout<<"              You have an account yet? (y/n)";
        char ans;
        while(ans != 'y' && ans != 'n') cin>>ans;
        if(ans == 'y') login();
        else registerPanel();
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
    cout<<"                       L O G I N    P A N E L"<<endl;
    cout<<"                   You have an account yet? (y/n)";
    char ans;
    while(ans != 'y' && ans != 'n') cin>>ans;
    if(ans == 'y') login();
    else registerPanel();
}

int main()
{
    welcomeMessage();
    return 0;
}
