//============================================================================
// Name        : Proj1.cpp
// Author      : Mafalda Santos, Diogo Silva, Alexandre Carqueja
// Version     :
// Copyright   : AEDA-2018
// Description : College Management
//============================================================================

#include <iostream>
#include "College.h"

using namespace std;

template<class T>
void Show_Info(T obj){
    obj.Show_Info();
}

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

int Main_Menu(){
    cout << "|      MAIN MENU     |" << endl;
    cout << "----------------------" << endl;
    cout << "0:   CREATE COLLEGE" << endl;
    cout << "1:   LOAD COLLEGE" << endl;
    cout << "2:   EXIT" << endl;
    return Nav(0,2);
}

void New_College(string & college_name){
    cout << "Insert your College Name: " << flush;
    getline(cin, college_name);
    cout << "\n\n\n" << endl;
}

int College_Menu(College &college){
    cout << "|      " << college.getName() <<"     |" << endl;
    cout << "----------------------" << endl;
    cout << "0:   DEPARTMENTS" << endl;
    cout << "1:   COURSES" << endl;
    cout << "2:   PEOPLE" << endl;
    cout << "3:   SAVE CHANGES" << endl;
    cout << "4:   EXIT COLLEGE" << endl;
    return(Nav(0,4));
}

void Dep_Menu(Department& department){
    Show_Info(department);
    cout << "0:     DEPARTMENT COURSES" << endl;
    cout << "1:     DEPARTMENT SUBJECTS" << endl;
    cout << "2:     EDIT INFO" << endl;
    cout << "3:     PREVIOUS MENU" << endl;
    switch(Nav(0,3)){
        case 0:
            //Courses_Menu(department);
            break;
        case 1:
            //Subjects_Menu(department);
            break;
        case 2:
            //Edit_Info(department);
            break;
        case 3:
            return;
    }
}

void Departments_Menu(College &college){
    int n = college.getDepartments().size();
    college.showDepartments();
    cout << n << ":   ADD DEPARTMENT" << endl;
    cout << ++n << ":   PREVIOUS MENU" << endl;
    int i = Nav(0,n);
    if(i == n){ //Previous
        return;
    }
    else if( i == (n-1)){ //Add department
        college.addDepartment();
    }
    else{ //Enter department
        Dep_Menu(college.getDepartments().at(i));
    }
}

int main() {
    string college_name;
    switch(Main_Menu()){ //0 for create College, 1 for Load college
        case 0:
            New_College(college_name);
            break;
        case 1:
            //display created college files and read a College from a .txt file
            break;
        case 2:
            return 0;
        default:
            return -1;
    }
    College college(college_name);
    switch(College_Menu(college)){
        case 0:
            Departments_Menu(college);
        case 1:
            //List all courses
        case 2:
            //Show all categories of people
        case 3:
            //Write everything on file
        case 4:
            break;
            //Destroy College and go back to main menu
    }
    return 0;
}
