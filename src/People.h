/*
 * People.h
 *
 *  Created on: Oct 17, 2018
 *
 */

#ifndef SRC_PEOPLE_H_
#define SRC_PEOPLE_H_

#include <iostream>
#include <map>
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
	//virtual static void Build_Person(); //A ideia é usar isto como UI para pedir ao utilizador os parametros necessarios para construir um obj pessoa, ou seja pode ser feito sem objeto posterior
    virtual void Show_Info();
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
	map <Uc*, float> subjects; //In this map the Key is the subject and the float value corresponds to the grade of the student on that particular subject;
public:
	Student(string name, string address, date birthday, unsigned int phone, unsigned int cod, Course *course);  //map is missing(will be resolved when deciding UI for constructors)
	Course* getCourse();
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
};

class Teacher : public Employee{
	string category;  //maybe the kind of degree the teacher has \(o.o)/
	vector <Uc*> subjects;  //subjects taught by the teacher
public:
	Teacher(string name, string adress, date birthday, unsigned int phone, unsigned int cod, float salary, unsigned int nif, string category, vector <Uc *> subjects);
	string getCategory();
	void setCategory(string category);
	vector<Uc*> getSubjects();

	void addSubject(Uc* uc); //for now it just adds a given UC
};

class Staff : public Employee{
	string work_area;
public:
	Staff(string name, string adress, date birthday, unsigned int phone, unsigned int cod, float salary, unsigned int nif, string work_area);
	string getWorkArea();
	void setWorkArea(string work_area);
};

#endif /* SRC_PEOPLE_H_ */
