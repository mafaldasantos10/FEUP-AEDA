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

int Main_Menu(){
    cout << "|      MAIN MENU     |" << endl;
    cout << "----------------------" << endl;
    cout << "0:   CREATE COLLEGE" << endl;
    cout << "1:   LOAD COLLEGE" << endl;
    cout << "2:   EXIT" << endl;
    return Nav(0,2);
}

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

void Course_Menu(Course& course){
    while(1){
        course.showInfo();
        cout << "0:   EDIT INFO" << endl;
        cout << "1:   SHOW COURSE PROGRAM" << endl;
        cout << "2:   ADD UC" << endl;
        cout << "3:   REMOVE UC" << endl;
        cout << "4:   PREVIOUS MENU" << endl;
        switch(Nav(0,4)){
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
                course.removeUC();
                break;
            case 4:
                return;
        }
    }
}

template<class T>
void Courses_Menu(T obj){ //Can be either college or Department
    while(1){
        obj.showInfo();
        Print_Vec(obj.getCourses());
        size_t n = obj.getCourses().size();
        cout << n << ":   ADD COURSE" << endl;
        cout << ++n << ":   REMOVE COURSE" << endl;
        cout << ++n << ":   PREVIOUS MENU" << endl;
        unsigned int i = Nav(0,n);
        if(i == n) return;
        else if(i == n-1) obj.removeCourse();
        else if(i == n-2) obj.addCourse();
        else Course_Menu(*(obj.getCourses().at(i)));
    }
}

void Dep_Menu(Department& department){
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

void Departments_Menu(College &college){
    int n;
    while(1) {
        n = college.getDepartments().size();
        college.showInfo();
        Print_Vec(college.getDepartments());
        cout << n << ":   ADD DEPARTMENT" << endl;
        cout << ++n << ":   REMOVE DEPARTMENT" << endl;
        cout << ++n << ":   PREVIOUS MENU" << endl;
        int i = Nav(0, n);
        if (i == n) { //Previous
            return;
        } else if (i == (n - 2)) { //Add department
            college.addDepartment();
        } else if (i == (n - 1)) { //Remove department
            college.removeDepartment();
        } else { //Enter department
            Dep_Menu(*college.getDepartments().at(i));
        }
    }
}

void Grades_Menu(People &person){
    Student *st = dynamic_cast<Student*>(&person);
    st->showAllGrades();
}

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

void List_Staff(College &college){
    int s, i;
    while(1){
        Print_Vec(college.getStaff());
        cout << s << ":   PREVIOUS MENU" << endl;
        i = Nav(0,s);
        if(i == s) return;
        else Person_Menu(*(college.getStudents().at(i)));
    }
}

void List_Teachers(College &college){
    int s, i;
    while(1){
        s = college.getTeachers().size();
        Print_Vec(college.getTeachers());
        cout << s << ":   PREVIOUS MENU" << endl;
        i = Nav(0,s);
        if(i == s) return;
        else Person_Menu(*(college.getStudents().at(i)));
    }
}

void List_Students(College &college){
    int s, i;
    while(1){
        s = college.getStudents().size();
        Print_Vec(college.getStudents());
        cout << s << ":   PREVIOUS MENU" << endl;
        i = Nav(0,s);
        if(i == s) return;
        else Person_Menu(*(college.getStudents().at(i)));
    }
}

void People_Menu(College &college){
    int i;
    while(1) {
        college.showInfo();
        cout << "0:   LIST ALL STUDENTS" << endl;
        cout << "1:   LIST ALL TEACHERS" << endl;
        cout << "2:   LIST ALL STAFF" << endl;
        cout << "3:   SEARCH PEOPLE" << endl;
        cout << "4:   ADD PERSON" << endl;
        cout << "5:   REMOVE PERSON" << endl;
        cout << "6:   PREVIOUS MENU" << endl;
        switch (i = Nav(0, 6)) {
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
                //Search people by name or id
                break;
            case 4:
                college.addPerson();
                break;
            case 5:
                //Remove_Person(id);
                break;
            case 6:
                return;
        }
    }
}

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
                //Courses_Menu(college);
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
                //Courses_Menu(college);
                break;
            case 2:
                //Destroy College and go back to main menu
                return;
        }
    }
}

void Admin_Menu(College &college){
    while(1){
        college.showInfo();
        cout << "0:   DEPARTMENTS" << endl;
        cout << "1:   COURSES" << endl;
        cout << "2:   PEOPLE" << endl;
        cout << "3:   SAVE CHANGES" << endl;
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
                //Write everything on file
                break;
            case 4:
                //Destroy College and go back to main menu
                return;
        }
    }
}

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
