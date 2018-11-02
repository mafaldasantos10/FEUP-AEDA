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
    vector<vector<People*>> people; //1º vec. for teachers, 2º for students, 3º for staff
public:
	College(string name); //class constructor
	//~College(); //class destructor

    vector<vector<People*>> getPeople();

	string getName();
	void setName(string name);

	void showDepartments();
    vector<Department> getDepartments();
	void addDepartment();
	void removeDepartment();
};


class Department {
   string depName, depAddress;
   Teacher* depDirector;
   int depCode, depPhone;
   vector<Course > vecCourse;
public:
   Department(string name, int code, string address, int phone, Teacher* director); //class constructor
   //~Department();

   void Show_Info();
   string getName();
   void setName(string name);
   string getAddress();
   void setAddress(string address);
   Teacher* getDirector();
   void setDirector(Teacher* director);
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
	void sortUc();
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

	bool operator<(Uc uc2);

};

//Exceptions

class NoCodeFound{
	int code;
public:
	NoCodeFound(int code){this->code=code;};
	int getCode(){return code;};
};



template <class T>
bool remove(vector<T> &vector, string name)
{
	for(unsigned int i = 0; i <= vector.size(); i++)
		{
			if(vector.at(i) == name)
			{
				vector.erase(vector.begin() + i);
				return true;


			}
		}
	return false;

}




#endif /*COLLEGE_H_*/
