//============================================================================
// Name        : Proj1.cpp
// Author      : Mafalda Santos, Diogo Silva, Alexandre Carqueja
// Version     :
// Copyright   : AEDA-2018
// Description : College Management
//============================================================================

#include <iostream>
#include <vector>
#include "College.h"
#include "People.h"

using namespace std;

int Nav(char bottom, char top){ //tests for valid input keys and returns the inputted char
    char key;
    while(cin >> key){
        if(key >= bottom && key <= top)
            break;
        else{
            cin.ignore();
            cin.clear();
            cout << "Invalid Input!" << endl;
        }
    }
    return key;
}

int Main_Menu(){
    cout << "|      MAIN MENU     |" << endl;
    cout << "----------------------" << endl;
    cout << "0:   CREATE COLLEGE" << endl;
    cout << "1:   LOAD COLLEGE" << endl;
    cout << "2:   EXIT" << endl;
    return Nav('0','2');
}

void New_College(string & college_name){
    cout << "Insert your College Name: " << flush;
    getline(cin, college_name);
}

int College_Menu(College &college){
    cout << "|      " << toupper(college.getName()) <<"     |" << endl;
    cout << "----------------------" << endl;
    cout << "0:   DEPARTMENTS" << endl;
    cout << "1:   COURSES" << endl;
    cout << "2:   PEOPLE" << endl;
    cout << "3:   SAVE CHANGES" << endl;
    cout << "4:   EXIT COLLEGE" << endl;
    return(Nav('0','4'));
}

void Dep_Menu(Department& department){
    cout << "|      " << department.getName() << "      |" << endl;
    cout << "| Address: " << department.getAddress() << endl;
    cout << "| Code: " << department.getCode() << " Phone: " <<department.getPhone() << endl;
    //To be finished
}

void Departments_Menu(College &college){
    int n = college.getDepartments().size();
    college.showDepartments();
    cout << n << ":   ADD DEPARTMENT" << endl;
    cout << ++n << ":   PREVIOUS MENU" << endl;
    const int prev = n;
    const int add = n--;
    switch(int i = Nav('0','n')){
        case add:
            college.addDepartment();
            break;
        case prev:
            return;
        default:
            //call Department function
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
            //List all Departments plus add department option
        case 1:
            //List all courses
        case 2:
            //Show all categories of people
        case 3:
            //Write everything on file
        case 4:
            //Destroy College and go back to main menu
    }
}
