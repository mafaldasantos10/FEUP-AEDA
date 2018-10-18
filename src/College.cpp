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


//COURSE//
//////////////////////
Course::Course(string type, string engName, string ptName, int code)
{
	csCode = code;
	csType = type;
	csEngName = engName;
	csPtName = ptName;
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
