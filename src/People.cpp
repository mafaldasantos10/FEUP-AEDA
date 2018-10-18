/*
 * People.cpp
 *
 *  Created on: Oct 17, 2018
 *      Author: alexandrecarqueja
 */

#include "People.h"

People::People(string name, string adress, date birthday, unsigned int phone, unsigned int cod) {
	this-> name = name;
	this->adress = adress;
	this->birthday = birthday;
	this->phone = phone;
	this->cod = cod;
}

Student::Student(string name, string adress, date birthday, unsigned int phone, unsigned int cod, Course *course)
: People(name,adress,birthday,phone,cod){
	this->course = course;
}

Employee::Employee(string name, string adress, date birthday, unsigned int phone, unsigned int cod, float salary, unsigned int nif)
: People(name,adress,birthday,phone,cod){
	this->salary = salary;
	this->nif = nif;
}

Teacher::Teacher(string name, string adress, date birthday, unsigned int phone, unsigned int cod, float salary, unsigned int nif, string category, vector<Uc *> subjects)
: Employee(name, adress, birthday, phone, cod, salary, nif){
	this->category = category;
	this->subjects = subjects;
}

Staff::Staff(string name, string adress, date birthday, unsigned int phone, unsigned int cod, float salary, unsigned int nif, string work_area)
: Employee(name, adress, birthday, phone, cod, salary, nif){
	this->work_area = work_area;
}

People::~People() {
	// TODO Auto-generated destructor stub
}

