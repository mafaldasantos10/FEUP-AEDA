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

//PROTOTYPES//
//////////////////////
class Course;
class Uc;

using namespace std;

struct date {  //formated date string for better use
	unsigned int day, month, year;
	const string format = to_string(day) + "/" + to_string(month) + "/" + to_string(year);
};

class People {
	string name, address;
	unsigned int phone, cod;
	date* birthday;
public:
	People(string name, string address, date& birthday, unsigned int phone, unsigned int cod);
	//virtual static void Add_Person(College& college); //A ideia é usar isto como UI para pedir ao utilizador os parametros necessarios para construir um obj pessoa, ou seja pode ser feito sem objeto posterior
    virtual void Show_Info();
    virtual int Edit_Info(); //Returns number of parameters
    virtual void Set(int n);
    virtual int Special_Info() = 0;
    void setName(string newName);
    string getName();
    string getAddress();
    void setAddress(string newAddress);
    int getPhone();
    void setPhone(int newPhone);
    int getCode();
    void setCode(int newCod);
    date* getDate();
	virtual ~People();
};

class Student : public People{
	Course* course; //pointer to current course the student is enrolled in
	float grade;
	map <Uc*, float> subjects; //In this map the Key is the subject and the float value corresponds to the grade of the student on that particular subject;

public:
	Student(string name, string address, date birthday, unsigned int phone, unsigned int cod, Course *course, map <Uc*, float> subjects);
	Student(string name, string address, unsigned int phone, unsigned int cod); // falta date
	Course* getCourse();
    int Special_Info();
    map <Uc*, float>* getGrades();
	string getCourseName();
	void showInfo();
	void addUCGrade(string name, float grade);
	void removeFromMap(string name);
	void changeGrade(string name);
	void showUCGrade(string name);
	void showAllGrades();
};

class Employee : public People{
	float salary;
	unsigned int nif;
public:
	Employee(string name, string adress, date birthday, unsigned int phone, unsigned int cod, float salary, unsigned int nif);
	float getSalary();
	void setSalary(float salary);
	unsigned int getNIF();
	void setNIF(unsigned int nif);
    int Special_Info();
};

class Teacher : public Employee{
	string category;  //maybe the kind of degree the teacher has \(o.o)/
	vector <Uc*> subjects;  //subjects taught by the teacher
public:
	Teacher(string name, string adress, date birthday, unsigned int phone, unsigned int cod, float salary, unsigned int nif, string category, vector <Uc *> subjects);
	string getCategory();
	void setCategory(string category);
	vector<Uc*> getSubjects();
	void showInfo();
	void addSubject(Uc* uc); //for now it just adds a given UC
};

class Staff : public Employee{
	string work_area;
public:
	Staff(string name, string adress, date birthday, unsigned int phone, unsigned int cod, float salary, unsigned int nif, string work_area);
	string getWorkArea();
	void setWorkArea(string work_area);
	void showInfo();
};

#endif /* PEOPLE_H_ */
