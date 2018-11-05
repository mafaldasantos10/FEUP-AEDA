/*
 * People.h
 *
 *  Created on: Oct 17, 2018
 *
 */

#ifndef PEOPLE_H_
#define PEOPLE_H_

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <time.h>

//PROTOTYPES//
//////////////////////
class College;
class Course;
class Uc;
int Nav(int bottom, int top);

using namespace std;

struct date {  //formated date string for better use
	unsigned int day, month, year;
    const string format = to_string(day) + "/" + to_string(month) + "/" + to_string(year);
};

class People {
	string name, address;
	unsigned int phone;
    string code;
	date* birthday;
public:
	People(string name, string address, date& birthday, unsigned int phone,string cod);

    virtual int Special_Info() = 0;
    virtual void showInfo();
    virtual int editInfo(); //Returns number of parameters

    virtual void Set(int n);
    void setName(string newName);
    string getName();
    string getAddress();
    void setAddress(string newAddress);
    int getPhone();
    void setPhone(int newPhone);
    string getCode();
    void setCode(string newCod);
    date* getDate();

	virtual ~People();
};

class Student : public People{
	Course* course; //pointer to current course the student is enrolled in
	int grade;  //year enrolled in
	map <Uc*, float> subjects; //In this map the Key is the subject and the float value corresponds to the grade of the student on that particular subject;
public:
	Student(string name, string address, date birthday, unsigned int phone, string cod, Course *course, map <Uc*, float> subjects);

    int Special_Info();
    void showInfo();

	Course* getCourse();
    map <Uc*, float>* getGrades();
	string getCourseName();
	void addUCGrade(string name, float grade);
	void removeFromMap(string name);
	void changeGrade(string name);
	void showUCGrade(string name);
	void showAllGrades();

    static int student_count;
};

class Employee : public People{
	float salary;
	unsigned int nif;
public:
	Employee(string name, string adress, date birthday, unsigned int phone, string cod, float salary, unsigned int nif);

    int Special_Info();

	float getSalary();
	void setSalary(float salary);
	unsigned int getNIF();
	void setNIF(unsigned int nif);
};

class Teacher : public Employee{
	string category;  //maybe the kind of degree the teacher has \(o.o)/
	vector <Uc*> subjects;  //subjects taught by the teacher
public:
	Teacher(string name, string adress, date birthday, unsigned int phone, string cod, float salary, unsigned int nif, string category, vector <Uc *> subjects);

    void showInfo();

	string getCategory();
	void setCategory(string category);
	vector<Uc*> getSubjects();
	void addSubject(Uc* uc); //for now it just adds a given UC

    static int teacher_count;
};

class Staff : public Employee{
	string work_area;
public:
	Staff(string name, string adress, date birthday, unsigned int phone, string cod, float salary, unsigned int nif, string work_area);

    void showInfo();

	string getWorkArea();
	void setWorkArea(string work_area);

    static int staff_count;
};

#endif /* PEOPLE_H_ */
