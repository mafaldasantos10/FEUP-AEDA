//============================================================================
// Name        : Proj1.cpp
// Author      : Mafalda Santos, Diogo Silva, Alexandre Carqueja
// Version     :
// Copyright   : AEDA-2018
// Description : College Management
//============================================================================

#include <iostream>
#include "College.h"
#include <sstream>
#include <fstream>
#include <map>

using namespace std;

int access = 0; //Global variable to determine type of user
string user_id;

////CURRENT YEAR//// (used for ids)
time_t theTime = time(NULL);
struct tm *aTime = localtime(&theTime);

int current_year = aTime->tm_year + 1900; // Year is # years since 1900
////////////////////

////GENERAL FUNCTIONS//// (used thoughout project, mostly for input verification)
int Nav(int bottom, int top){ //tests for valid input keys and returns the inputted char
    int key;
    while(cin >> key){ //Problem with cin getting corrupted if several characters are introduced
        cin.clear();
        cin.ignore();
        if(key >= bottom && key <= top) break;
        else cout << "Invalid Input!" << endl;
    }
    return key;
}

date* readDate(){
    unsigned int day, month, year;
    char c = '/';
    string data;
    while(1){
        cout << "\nInsert Birthday(dd/mm/yyyy): " << flush;
        getline(cin,data);
        data = data.substr(0,data.find('\n'));
        stringstream ss(data);
        ss >> day >> c >> month >> c >> year;
        if(day < 0 || day > 31
                || month < 0 || month > 12
                || year < 1900 || year > 2018) cout << "\nInvalid date!" << endl;
        else break;
    }
    date* d = new date();
    d->day = day; d->month = month; d->year = year;
    return d;
}
//////////////////////

template<class T>
void editInfo(T &obj) {
    int n, i;
    while (1) {
        obj.showInfo();
        n = obj.editInfo();
        i = Nav(0,n);
        if(i == n) return;
        else obj.Set(i);
    }
}

//////////////////////

int Main_Menu(){
    cout << "----------------------" << endl;
    cout << "|      MAIN MENU     |" << endl;
    cout << "----------------------" << endl;
    cout << "0:   CREATE COLLEGE" << endl;
    cout << "1:   LOAD COLLEGE" << endl;
    cout << "2:   EXIT" << endl;
    return Nav(0,2);
}

//////////////////////

void New_College(College &college){
    string college_name, admin;
    cout << "Insert your College Name: " << flush;
    getline(cin, college_name); //////////INPUT VALIDATION MISSING!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!(s� para ter a certeza q v�m)
    cout << endl << "Insert your Admin Code: " << flush;
    getline(cin, admin);
    college.setName(college_name);
    college.setAdmin(admin);
    cout << "\n\n\n" << endl;
}

//////////////////////

template<class T>
T* Search_Menu(vector<T*> vec){
    string name;
    T* t;
    while(1){
        cout << "Insert the name you want to search for(! to cancel): " << flush;
        getline(cin,name);
        if(name == "!") return nullptr;
        try{
            t = SearchVec(vec,name);
        }
        catch(NoNameFound &err){
            cout << err.errorMessage() << endl;
            continue;
        }
        break;
    }
    return t;
}

//////////////////////

void Course_Menu(Course& course){
    while(1){
        course.showInfo();
        cout << "0:   EDIT INFO" << endl;
        cout << "1:   SHOW COURSE PROGRAM" << endl;
        cout << "2:   ADD UC" << endl;
        cout << "3:   REMOVE UC" << endl;
        cout << "4:   SEARCH UC" << endl;
        cout << "5:   PREVIOUS MENU" << endl;
        switch(Nav(0,5)){
            case 0:
                editInfo(course);
                break;
            case 1:
                course.showSyllabus();
                break;
            case 2:
                course.addUC();
                break;
            case 3:
                try{
                    course.removeUC();
                }
                catch(NoNameFound &err){
                    cout << err.errorMessage() << endl;
                    continue;
                }
                break;
            case 4:
                Uc* ptr;
                try{
                    ptr = Search_Menu(course.getUCs());
                }
                catch(NoNameFound &err){
                    cout << err.errorMessage() << endl;
                    continue;
                }
                //Uc_Menu(*ptr);
            case 5:
                return;
        }
    }
}

//////////////////////

template<class T>
void Courses_Menu(T &obj){ //Can be either college or Department
    while(1){
        obj.showInfo();
        Print_Vec(obj.getCourses());
        size_t n = obj.getCourses().size();
        cout << n << ":   ADD COURSE" << endl;
        cout << ++n << ":   REMOVE COURSE" << endl;
        cout << ++n << ":   SEARCH COURSE" << endl;
        cout << ++n << ":   PREVIOUS MENU" << endl;
        int i = Nav(0,n);
        if(i == n) return;
        else if(i == n-1){
            Course* ptr;
            try{
                ptr = Search_Menu(obj.getCourses());
            }
            catch(NoNameFound &err){
                cout << err.errorMessage() << endl;
                continue;
            }
            Course_Menu(*ptr);
        }
        else if(i == n-2){
            auto ptr = Search_Menu(obj.getCourses());
            if(ptr != nullptr) Course_Menu(*ptr);
        }
        else if(i == n-3) obj.addCourse();
        else Course_Menu(*(obj.getCourses().at(i)));
    }
}

//////////////////////

void Dep_Menu(Department& department){
    while(1){
        department.showInfo();
        cout << "0:   DEPARTMENT COURSES" << endl;
        cout << "1:   EDIT INFO" << endl;
        cout << "2:   PREVIOUS MENU" << endl;
        switch(Nav(0,3)){
            case 0:
                Courses_Menu(department);
                break;
            case 1:
                editInfo(department);
                break;
            case 2:
                return;
        }
    }
}

//////////////////////

void Departments_Menu(College &college){
    int n;
    while(1) {
        n = college.getDepartments().size();
        college.showInfo();
        Print_Vec(college.getDepartments());
        cout << n << ":   ADD DEPARTMENT" << endl;
        cout << ++n << ":   REMOVE DEPARTMENT" << endl;
        cout << ++n << ":   SEARCH DEPARTMENT" << endl;
        cout << ++n << ":   PREVIOUS MENU" << endl;
        int i = Nav(0, n);
        if (i == n) { //Previous
            return;
        } else if (i == (n - 3)) { //Add department
            college.addDepartment();
        } else if (i == (n - 2)) { //Remove department
            try {
                college.removeDepartment();
            }
            catch(NoCodeFound &err){
                cout << err.errorMessage() << endl;
                continue;
            }
        } else if (i == (n - 1)) { //Search Department by name
            auto ptr = Search_Menu(college.getDepartments());
            if(ptr != nullptr) Dep_Menu(*ptr);
        } else { //Enter department
            Dep_Menu(*college.getDepartments().at(i));
        }
    }
}

//////////////////////

void Grades_Menu(People &person){
    Student *st = dynamic_cast<Student*>(&person);
    st->showAllGrades();
}

//////////////////////

template<class T>
void Person_Menu(T &person){
    int n = -1, i;
    while(1){
        person.showInfo();
        if((access == 1 && user_id == person.getCode()) || access == 2){
            n = person.Special_Info();
            cout << n << ":   EDIT INFO" << endl;
        }
        cout << ++n << ":   PREVIOUS MENU" << endl;
        i = Nav(0,n);
        if(i == n) return;
        else if( i == n-1) editInfo(person);
        else if(i == n-2) Grades_Menu(person);
    }
}

//////////////////////

void Remove_Person(College &college){
    int i;
    while(1) {
        cout << "What Type of person would you like to remove?" << endl;
        cout << "0:   STUDENT" << endl;
        cout << "1:   TEACHER" << endl;
        cout << "2:   STAFF" << endl;
        cout << "3:   CANCEL" << endl;
        i = Nav(0,3);
        if(i == 3) return;
        else if(i == 0){
            auto ptr = Search_Menu(college.getStudents());
            if(ptr != nullptr) college.removeStudent(ptr);
        }
        else if(i == 1) {
            auto ptr = Search_Menu(college.getTeachers());
            if(ptr != nullptr) college.removeTeacher(ptr);
        }
        else if(i == 2){
            auto ptr = Search_Menu(college.getStaff());
            if(ptr != nullptr) college.removeStaff(ptr);
        }
    }
}

//////////////////////

void List_Staff(College &college){
    int s, i;
    while(1){
        Print_Vec(college.getStaff());
        cout << s << ":   ADD STAFF" << endl;
        cout << ++s << ":   REMOVE STAFF" << endl;
        cout << ++s << ":   SEARCH STAFF" << endl;
        cout << ++s << ":   PREVIOUS MENU" << endl;
        i = Nav(0,s);
        if(i == s) return;
        else if(i == s-3){
            auto *stf = new Staff();
            stf->addPerson(college);
        }
        else if(i == s-2){
            //Remove_Person(college);
        }
        else if(i == s-1){
            auto ptr = Search_Menu(college.getStaff());
            if(ptr != nullptr) Person_Menu(*ptr);
        }
        else Person_Menu(*(college.getStaff().at(i)));
    }
}

//////////////////////

void List_Teachers(College &college){
    int s, i;
    while(1){
        s = college.getTeachers().size();
        Print_Vec(college.getTeachers());
        cout << s << ":   ADD TEACHER" << endl;
        cout << ++s << ":   REMOVE TEACHER" << endl;
        cout << ++s << ":   SEARCH TEACHER" << endl;
        cout << ++s << ":   PREVIOUS MENU" << endl;
        i = Nav(0,s);
        if(i == s) return;
        else if(i == s-3){
            auto *tch = new Teacher();
            tch->addPerson(college);
        }
        else if(i == s-2){
            //Remove_Person(college);
        }
        else if(i == s-1){
            auto ptr = Search_Menu(college.getTeachers());
            if(ptr != nullptr) Person_Menu(*ptr);
        }
        else Person_Menu(*(college.getTeachers().at(i)));
    }
}

//////////////////////

void List_Students(College &college){
    int s, i;
    while(1){
        s = college.getStudents().size();
        Print_Vec(college.getStudents());
        cout << s << ":   ADD STUDENT" << endl;
        cout << ++s << ":   REMOVE STUDENT" << endl;
        cout << ++s << ":   SEARCH STUDENT" << endl;
        cout << ++s << ":   PREVIOUS MENU" << endl;
        i = Nav(0,s);
        if(i == s) return;
        else if(i == s-3){
            auto *st = new Student();
            st->addPerson(college);
        }
        else if(i == s-2){
            //Remove_Person(college);
        }
        else if(i == s-1){
            auto ptr = Search_Menu(college.getStudents());
            if(ptr != nullptr) Person_Menu(*ptr);
        }
        else Person_Menu(*(college.getStudents().at(i)));
    }
}

//////////////////////

void Add_Person(College &college){
    int i;
    while(1) {
        cout << "What Type of person would you like to add?" << endl;
        cout << "0:   STUDENT" << endl;
        cout << "1:   TEACHER" << endl;
        cout << "2:   STAFF" << endl;
        cout << "3:   CANCEL" << endl;
        i = Nav(0, 3);

        if (i == 3) return;
        else if (i == 0) {
            Student *st = new Student();
            st->addPerson(college);
        } else if (i == 1) {
            Teacher *tch = new Teacher();
            tch->addPerson(college);
        } else if (i == 2) {
            Staff *stf = new Staff();
            stf->addPerson(college);
        }
    }
}

//////////////////////

void People_Menu(College &college){
    while(1) {
        college.showInfo();
        cout << "0:   LIST ALL STUDENTS" << endl;
        cout << "1:   LIST ALL TEACHERS" << endl;
        cout << "2:   LIST ALL STAFF" << endl;
        cout << "3:   ADD PERSON" << endl;
        cout << "4:   REMOVE PERSON" << endl;
        cout << "5:   PREVIOUS MENU" << endl;
        switch (Nav(0, 5)) {
            case 0:
                List_Students(college);
                break;
            case 1:
                List_Teachers(college);
                break;
            case 2:
                List_Staff(college);
                break;
            case 3:
                Add_Person(college);
                break;
            case 4:
                Remove_Person(college);
                break;
            case 5:
                return;
        }
    }
}

//////////////////////

void Member_Menu(College &college){ //Can only read
    while(1){
        college.showInfo();
        cout << "0:   DEPARTMENTS" << endl;
        cout << "1:   COURSES" << endl;
        cout << "2:   PEOPLE" << endl;
        cout << "3:   PROFILE" << endl;
        cout << "4:   EXIT COLLEGE" << endl;
        switch(Nav(0,4)){
            case 0:
                Departments_Menu(college);
                break;
            case 1:
                Courses_Menu(college);
                break;
            case 2:
                People_Menu(college);
                break;
            case 3:
                //Use Search_Person(id) to show personal info
                break;
            case 4:
                //Destroy College and go back to main menu
                return;
        }
    }
}

//////////////////////

void Vis_Menu(College &college){ //Can only see info
    while(1){
        college.showInfo();
        cout << "0:   DEPARTMENTS" << endl;
        cout << "1:   COURSES" << endl;
        cout << "2:   EXIT COLLEGE" << endl;
        switch(Nav(0,2)){
            case 0:
                Departments_Menu(college);
                break;
            case 1:
                Courses_Menu(college);
                break;
            case 2:
                //Destroy College and go back to main menu
                return;
        }
    }
}

//////////////////////

string Choose_Colleges(){
    ifstream file;
    int x = -1,i = 0, input;
    string file_name = "college0.txt";
    string college_name;
    vector<string> colleges;
    while(i != 30){
        file.open(file_name);
        if(file.is_open()){
            getline(file, college_name);
            cout << ++x << ":   " << college_name << endl;
            colleges.push_back(file_name);
            file.close();
        }
        i++;
        file_name = "college" + to_string(i) + ".txt";
    }
    cout << ++x << ":   PREVIOUS MENU" << endl;
    input = Nav(0,x);
    if(input == x) return "";
    else return colleges.at(x);
}

//////////////////////

void Save_College(College &college){
    ifstream file;
    int i = 0;
    string file_name = "college0.txt";
    while(i != 30){
        file.open(file_name);
        if(!file.is_open()){
            break;
        }
        i++;
        file_name = "college" + to_string(i) + ".txt";
    }
    ofstream save_file (file_name);
    //------COLLEGE INFO------
    save_file << &college;
    //------ DEP/COURSE/UC INFO------
    for(size_t i = 0; i < college.getDepartments().size(); i++){
        save_file << "DEP:" << endl;
        save_file << college.getDepartments().at(i) << endl;
        save_file << endl;
    }
    //------STUDENTS INFO------
    save_file << "STUDENTS:" << endl;
    for(size_t i = 0; i < college.getStudents().size(); i++){
        save_file << college.getStudents().at(i) << endl; //CREATE << overload for people
    }
    save_file << endl;
    //------TEACHERS INFO------
    save_file << "TEACHER:" << endl;
    for(size_t i = 0; i < college.getTeachers().size(); i++){
        save_file << college.getTeachers().at(i) << endl; //CREATE << overload for people
    }
    save_file << endl;
    //------STAFF INFO------
    save_file << "STAFF:" << endl;
    for(size_t i = 0; i < college.getStaff().size(); i++){
        save_file << college.getStaff().at(i) << endl; //CREATE << overload for people
    }
    save_file << endl;
}

//////////////////////

bool Exit_College(College &college){
    college.showInfo();
    cout << "0:   SAVE AND EXIT" << endl;
    cout << "1:   EXIT WITHOUT SAVING" << endl;
    cout << "2:   CANCEL" << endl;
    switch(Nav(0,2)){
        case 0:
            Save_College(college);
            return true;
        case 1:
            return true;
        case 2:
            return false;
    }
}

//////////////////////

void Admin_Menu(College &college){
    while(1){
        college.showInfo();
        cout << "0:   DEPARTMENTS" << endl;
        cout << "1:   COURSES" << endl;
        cout << "2:   PEOPLE" << endl;
        cout << "3:   EXIT COLLEGE" << endl;
        switch(Nav(0,3)){
            case 0:
                Departments_Menu(college);
                break;
            case 1:
                Courses_Menu(college);
                break;
            case 2:
                People_Menu(college);
                break;
            case 3:
                if(Exit_College(college)) return;
                else break;
        }
    }
}

//////////////////////

int Log_In(College& college){
    int i;
    while(1){
        cout << "0:   CONTINUE AS VISITOR" << endl;
        cout << "1:   LOG IN AS MEMBER" << endl;
        cout << "2:   LOG IN AS ADMIN" << endl;
        cout << "3:   PREVIOUS MENU" << endl;
        i = Nav(0,3);
        switch(i){
            case 0:
                //Continue as visitor
                break;
            case 1:
                //Log in as member
                break;
            case 2:
                //Log in as admin
                break;
            case 3:
                break;
        }
        return i;
    }
}

//////////////////////

int main() {

    while(1){
        College college;
        switch(Main_Menu()){
            case 0:
                New_College(college);
                access = 2;
                break;
            case 1:
                // Load_College();
                // display created college files and read a College from a .txt file
                access = Log_In(college);
                break;
            case 2:
                return 0;
            default:
                return -1;
        }
        switch(access){
            case 0:
                Vis_Menu(college);
                break;
            case 1:
                Member_Menu(college);
                break;
            case 2:
                Admin_Menu(college);
                break;
            case 3:
                break;
            default:
                return -1;
        }
    }
}
