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

void College::addDepartment()
{
	string name,address,director;
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

	Department depart(name, code, address, phone, director);
	vecDep.push_back(depart);


}

void Department::addCourse()
{
	string type, ptName,engName;
	int code;

		cout << "Enter name of the course in portuguese"<< endl;
		cin >> ptName;

		cout << "Enter name of the course in english"<< endl;
		cin >> engName;

		cout << "What type of course is it?"<< endl;
		cin >> type;

		cout << "Enter code of the course"<< endl;
		cin >> code;

		Course cs(type, engName, ptName, code);
		vecCourse.push_back(cs);
}

void Course::addUc()
{
	string name,namet,names;
	int year, ects, workload,n,nt;
	vector<string> teachers,students;

			cout << "Enter name of the curricular unity"<< endl;
			cin >> name;

			cout << "In which year is it taught?"<< endl;
			cin >> year;

			cout << "How many ectc does it have?"<< endl;
			cin >> ects;

			cout << "How much is the workload"<< endl;
			cin>>workload;

			cout << "Enter the number of students"<< endl;
			cin >> n ;

			cout << "Enter one by one it's names"<<endl;

			for( int i=1; i<=n; i++)
			{
				cout<<"  "<<i<<": ";

			}

			cout << "Enter the number of teachers"<< endl;
			cin >> nt ;

	        cout << "Enter one by one it's names"<<endl;

	        for(int i=1; i<=n; i++)
			{
		    	cout<<"  "<<i<<": ";
		    	cin>>namet;
		    	ucTeacher.push_back(namet);
		 	}

			Uc curricularunity (name, teachers, students, year, ects, workload);
			vecUc.push_back(curricularunity);
}
