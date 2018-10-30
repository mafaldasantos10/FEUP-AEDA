	/*
 * College.cpp
 *
 *  Created on: 15/10/2018
 */

#include "College.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

//COLLEGE//
//////////////////////
College::College(string name)
{
	colName = name;
}

void College::showDepartments()
{
	for(unsigned int i = 0; i < vecDep.size(); i++)
	{
		cout << vecDep.at(i).getName() << endl;
	}
}

string College::getName()
{
	return colName;
}

void College::addDepartment()
{
	string name, address, director;
	int code, phone;

	cout << "Enter name of the department"<< endl;
	cin >> name;

	cout << "Enter address of the department"<< endl;
	cin >> address;

	cout << "Enter name of the director of the department"<< endl;
	cin >> director;

	cout << "Enter code of the department"<< endl;
	cin >> code;

	cout << "Enter phone of the department"<< endl;
	cin >> phone;

	Department newDepartment(name, code, address, phone, director);
	vecDep.push_back(newDepartment);

}

//DEPARTMENT//
//////////////////////
Department:: Department(string name, int code, string address, int phone, string director)
{
	depName = name;
	depCode = code;
	depAddress = address;
	depPhone = phone;
	depDirector = director;
}

string Department::getName()
{
	return depName;
}

string Department::getAddress()
{
	return depAddress;
}

string Department::getDirector()
{
	return depDirector;
}

int Department::getCode()
{
	return depCode;
}

int Department::getPhone()
{
	return depPhone;
}

vector<Course> Department::getCourses()
{
	return vecCourse;
}

void Department::addCourse()
{
	string type, ptName, engName;
	int code;

	cout << "Enter name of the course in portuguese"<< endl;
	cin >> ptName;

	cout << "Enter name of the course in english"<< endl;
	cin >> engName;

	cout << "What type of course is it?"<< endl;
	cin >> type;

	cout << "Enter code of the course"<< endl;
	cin >> code;

	Course newCourse(type, engName, ptName, code);
	vecCourse.push_back(newCourse);
}

//COURSE//
//////////////////////
Course::Course(string type, string engName, string ptName, int code)
{
	csCode = code;
	csType = type;
	csEngName = engName;
	csPtName = ptName;
}

string Course::getType()
{
	return csType;
}

string Course::getPtName()
{
	return csPtName;
}

string Course::getEngName()
{
	return csEngName;
}

int Course::getCode()
{
	return csCode;
}

vector<Course> Course::getUCs()
{
	return vecUC;
}

void Course::addUC()
{
	string name, nameT, nameS;
	int year, ects, workload, nS, nT;
	vector<string> teachers, students;

	cout << "Enter name of the Curricular Unit"<< endl;
	cin >> name;

	cout << "In which year is it taught?"<< endl;
	cin >> year;

	cout << "How many ETCS does it have?"<< endl;
	cin >> ects;

	cout << "How many hours of workload?"<< endl;
	cin >> workload;

	cout << "Enter the number of students: "<< endl;
	cin >> nS ;

	cout << "Enter their names one by one: "<<endl;

	for( int i = 1; i <= nS; i++)
	{
		cout <<"  "<< i << ": ";
		cin >> nameS;
		students.push_back(nameS);
	}

	cout << "Enter the number of teachers: "<< endl;
	cin >> nT ;

	cout << "Enter their names one by one, starting by the Regent: "<<endl;

	for(int i = 1; i <= nT; i++)
	{
		cout << "  "<< i <<": ";
		cin >> nameT;
		teachers.push_back(nameT);
	}

	Uc newUC(name, teachers, students, year, ects, workload);
	vecUC.push_back(newUC);
}

//UC//
//////////////////////
Uc::Uc(string name, vector<string> teacher, vector<string> student, int year, int ects, int workload)
{
	ucECTS = ects;
	ucName = name;
	ucStudent = student;
	ucTeacher = teacher;
	ucWorkload = workload;
	ucYear = year;
}

string Uc::getName()
{
	return ucName;
}

int Uc::getYear()
{
	return ucYear;
}

int Uc::getECTS()
{
	return ucECTS;
}

int Uc::getWorkload()
{
	return ucWorkload;
}

vector<Uc> Uc::getTeachers()
{
	return ucTeacher;
}

vector<Uc> Uc::getStudents()
{
	return ucStudent;
}
