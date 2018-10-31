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
#include "People.h"

using namespace std;

//PROTOTYPES
class Department;
class Course;
class Uc;


class College{
	string colName;
	vector<Department > vecDep;
public:
	College(string name); //class constructor
	//~College(); //class destructor

	string getName();
	void setName(string name);

	void showDepartments();
    vector<Department> getDepartments();
	string getName();
	void addDepartment();
	void removeDepartment();
};


class Department {
   string depName, depAddress, depDirector;
   int depCode, depPhone;
   vector<Course > vecCourse;
public:
   Department(string name, int code, string address, int phone, string director); //class constructor
   //~Department();

   string getName();
   void setName(string name);
   string getAddress();
   void setAddress(string address);
   string getDirector();
   void setDirector(string director);
   int getCode();
   void setCode(int code);
   int getPhone();
   void setPhone(int phone);
   vector<Course> getCourses();

   void addCourse();
   void removeCourse();
};


class Course{
	string csType, csPtName, csEngName;
	int csCode;
	vector<Uc > vecUC;
public:
	Course(string type, string engName, string ptName, int code);
	//~Course();

	string getType();
	void setType(string type);
	string getPtName();
	void setPtName(string ptName);
	string getEngName();
	void setEngName(string engName);
	int getCode();
	void setCode(int code);
	vector<Uc> getUCs();

	void addUC();
	void removeUC();
};


class Uc{
    string ucName;
    vector<string> ucTeacher; //sendo que o que se encontra na posicao 0 � o regente
    vector<string> ucStudent;
    int ucYear, ucECTS, ucWorkload;
public:
	Uc(string name, vector<string> teacher, vector<string> student, int year, int ects, int workload);
	//~Uc();

	string getName();
	void setName(string name);
    int getYear();
    void setYear(int year);
    int getECTS();
    void setECTS(int ects);
	int getWorkload();
	void setWorkload(int workload);
	vector<string> getTeachers();
	vector<string> getStudents();

	void addTeacher();
	void removeTeacher();
	void addStudent();
	void removeStudent();
};

#endif /*COLLEGE_H_*/
