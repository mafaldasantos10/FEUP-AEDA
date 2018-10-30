/*
 * College.h
 *
 *  Created on: 15/10/2018
 */

#ifndef COLLEGE_H_
#define COLLEGE_H_

#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

//PROTOTYPES
class Department;
class Course;
class Uc;


class College{
	string colName;
	vector<Department> vecDep;
public:
	College(string name); //class constructor
	void showDepartments();
	string getName();
	void addDepartment();
	~College(); //class destructor
};


class Department {
   string depName, depAddress, depDirector;
   int depCode, depPhone;
   vector<Course> vecCourse;
public:
   Department(string name, int code, string address, int phone, string director); //class constructor
   ~Department();

   string getName();
   string getAddress();
   string getDirector();
   int getCode();
   int getPhone();
   vector<Course> getCourses();

   void addCourse();
};


class Course{
	string csType, csPtName, csEngName;
	int csCode;
	vector<Uc> vecUC;
public:
	Course(string type, string engName, string ptName, int code);
	~Course();

	string getType();
	string getPtName();
	string getEngName();
	int getCode();
	vector<Course> getUCs();

	void addUC();
};


class Uc{
	string ucName;
	vector<string> ucTeacher; //sendo que o que se encontra na posicao 0 é o regente
	vector<string> ucStudent;
	int ucYear, ucECTS, ucWorkload;
public:
	Uc(string name, vector<string> teacher, vector<string> student, int year, int ects, int workload);
	~Uc();

	string getName();
	int getYear();
	int getECTS();
	int getWorkload();
	vector<Uc> getTeachers();
	vector<Uc> getStudents();

};

#endif /*COLLEGE_H_*/
