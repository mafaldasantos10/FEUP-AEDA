//============================================================================
// Name        : Proj1.cpp
// Author      : Mafalda Santos, Diogo Silva, Alexandre Carqueja
// Version     :
// Copyright   : AEDA-2018
// Description : College Management
//============================================================================

#include <iostream>
#include "College.h"
#include <map>

using namespace std;

time_t theTime = time(NULL);
struct tm *aTime = localtime(&theTime);

int current_year = aTime->tm_year + 1900; // Year is # years since 1900

int access = 0; //Global variable to determine type of user
string user_id;

int Nav(int bottom, int top){ //tests for valid input keys and returns the inputted char
    int key;
    while(cin >> key){
        cin.ignore();
        cin.clear();
        if(key >= bottom && key <= top) break;
        else cout << "Invalid Input!" << endl;
    }
    return key;
}

template<class T>
void Print_Vec(vector<T*> vec){  //Prints name of every object in vector of objects
    for(unsigned int i = 0; i < vec.size() ; i++){
        cout << i << ":   " << vec.at(i)->getName() << endl;
    }
}

template<class T>
void editInfo(T &obj) {
   // int n, i;
    while (1) {
        obj.showInfo();
      //  n = obj.editInfo();
      //  i = Nav(0,n);
       // if(n == i) return;
      //  else obj.Set(n);
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
    getline(cin, college_name);
    cout << endl << "Insert your Admin Code: " << flush;
    getline(cin, admin);
    college.setName(college_name);
    college.setAdmin(admin);
    cout << "\n\n\n" << endl;
}

template<class T>
void Courses_Menu(T obj){ //Can be either college or Department
    obj.showInfo();
    obj.Show_Courses;
    cout << ":   ADD COURSE" << endl;
    cout << ":   REMOVE COURSE" << endl;
    cout << ":   PREVIOUS" << endl;
}

void Dep_Menu(Department& department){
    department.showInfo();
    cout << "0:   DEPARTMENT COURSES" << endl;
    cout << "1:   DEPARTMENT SUBJECTS" << endl;
    cout << "2:   EDIT INFO" << endl;
    cout << "3:   PREVIOUS MENU" << endl;
    switch(Nav(0,3)){
        case 0:
            //Courses_Menu(department);
            break;
        case 1:
            //Subjects_Menu(department);  //Organized by course
            break;
        case 2:
            editInfo(department);
            break;
        case 3:
            return;
    }
}

void Departments_Menu(College &college){
    int n;
    while(1) {
        n = college.getDepartments().size();
        college.showInfo();
        college.showDepartments();
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

void Add_Student(College& college, string name, string address, unsigned int phone, string cod, date& birthday){
    Course* course;
    int year;
    float grade;
    map<Uc*,float> subjects;
    unsigned int i;
    cod = "0" + to_string(current_year) + to_string(Student::student_count);  //student id is assigned
    cout << "\nChoose Student's Course:" << endl;  //Needs exception in case there are no Courses Created
    Print_Vec(college.getCourses());
    course = college.getCourses().at(Nav(0,college.getCourses().size()-1));
    cout << "\nInsert Student's Grade: " << flush;
    cin >> year;
    while(1){
        cout << "\nChoose Student's Ucs: " << endl;
        Print_Vec(course->getUCs());
        cout << course->getUCs().size() << ":   DONE" << endl;
        i = Nav(0,course->getUCs().size());
        if(i == course->getUCs().size()) break;
        else if(subjects.find(course->getUCs().at(i)) != subjects.end()){
            cout << "Insert student's grade on this subject(-1 for no grade): " << flush;
            cin >> grade;
            subjects.insert(pair<Uc*,float>(course->getUCs().at(i),grade));
        }
        else cout << "Student's already enrolled in this Uc!" << endl;
    }
    Student* st = new Student(name, address, birthday, phone, cod, course, subjects);
    college.addPeople(0, st); //dynamic_cast<People*>(st) if there's an error
}

void Add_Person(College& college, int type = -1){ //Needs general function to check input
    string name, address;
    unsigned int phone;
    string cod;
    date birthday;
    if(type == -1){
        cout << "What Type of person would you like to add?" << endl;
        cout << "0:   STUDENT" << endl;
        cout << "1:   TEACHER" << endl;
        cout << "2:   STAFF" << endl;
        cout << "3:   CANCEL" << endl;
        type = Nav(0,3);
    }
    if(type == 3) return;
    cout << "Insert Name: " << flush;
    cin >> name;
    cin.clear();
    cin.ignore();
    cout << "\nInsert Address: " << flush;
    getline(cin,address);
    cin.clear();
    cin.ignore();
    cout << "\nInsert Phone Number: " << flush;
    cin >> phone;
    cin.clear();
    cin.ignore();
    cout << "\nInsert Birthday(dd/mm/yyyy): " << flush;
    //Read_date(&birthday) //Tests if date is written correctly
    switch(type){
        case 0:
            Add_Student(college, name, address, phone, cod, birthday);
            break;
        case 1:
            break;
        case 2:
            break;
    }
}

void Person_Menu(People &person){
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

void List_People(College &college, int n){
    int s, i;
    while(1){
        s = college.getPeople().at(n).size();
        for(int j = 0; j < s; j++){
            cout << j << ":   " << college.getPeople().at(n).at(j)->getName() << endl;
        }
        cout << s << ":   PREVIOUS MENU" << endl;
        i = Nav(0,s);
        if(i == s) return;
        else Person_Menu(*(college.getPeople().at(n).at(i)));
    }
}

void People_Menu(College &college){
    int i;
    while(1) {
        college.showInfo();
        cout << "0:   LIST ALL TEACHERS" << endl;
        cout << "1:   LIST ALL STUDENTS" << endl;
        cout << "2:   LIST ALL STAFF" << endl;
        cout << "3:   SEARCH PEOPLE" << endl;
        cout << "4:   ADD PERSON" << endl;
        cout << "5:   REMOVE PERSON" << endl;
        cout << "6:   PREVIOUS MENU" << endl;
        switch (i = Nav(0, 6)) {
            case 0:
            case 1:
            case 2:
                List_People(college,i);
                break;
            case 3:
                //Search people by name or id
                break;
            case 4:
                Add_Person(college);
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
                //Courses_Menu(college);
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
