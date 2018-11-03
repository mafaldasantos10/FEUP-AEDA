/*
 * People.cpp
 *
 *  Created on: Oct 17, 2018
 *
 */

#include "People.h"

//////PEOPLE//////

People::People(string name, string address, date& birthday, unsigned int phone, unsigned int cod) {
	this->name = name;
	this->address = address;
	this->birthday = &birthday;
	this->phone = phone;
	this->cod = cod;
}

string People::getName(){
    return name;
}

void People::setName(string newName)
{
	name=newName;
}

string People::getAddress()
{
	return address;
}

void People::setAddress(string newAddress)
{
	address=newAddress;
}

int People::getPhone()
{
	return phone;
}

void People::setPhone(int newPhone)
{
	phone = newPhone;
}

int People::getCode()
{
	return cod;
}

void People::setCode(int newCod)
{
	cod=newCod;
}

date* People::getDate()
{
	return birthday;
}

void People::Show_Info(){

}

//////STUDENT//////

Student::Student(string name, string address, date birthday, unsigned int phone, unsigned int cod, Course *course)
: People(name, address, birthday, phone, cod){
	this->course = course;
}

Course* Student::getCourse()
{
	return course;
}

//////EMPLOYEE//////

Employee::Employee(string name, string address, date birthday, unsigned int phone, unsigned int cod, float salary, unsigned int nif)
: People(name, address, birthday, phone, cod){
	this->salary = salary;
	this->nif = nif;
}

float Employee::getSalary()
{
	return salary;
}

void Employee::setSalary(float salary)
{
	this->salary = salary;
}

unsigned int Employee::getNIF()
{
	return nif;
}

void Employee::setNIF(unsigned int nif)
{
	this->nif = nif;
}


//////TEACHER//////

Teacher::Teacher(string name, string address, date birthday, unsigned int phone, unsigned int cod, float salary, unsigned int nif, string category, vector<Uc *> subjects)
: Employee(name, address, birthday, phone, cod, salary, nif){
	this->category = category;
	this->subjects = subjects;
}

string Teacher::getCategory()
{
	return category;
}

void Teacher::setCategory(string category)
{
	this->category = category;
}

vector<Uc*> Teacher::getSubjects()
{
	return subjects;
}

void Teacher::addSubject(Uc* uc)
{
	subjects.push_back(uc);
}

//////STAFF//////

Staff::Staff(string name, string address, date birthday, unsigned int phone, unsigned int cod, float salary, unsigned int nif, string work_area)
: Employee(name, address, birthday, phone, cod, salary, nif){
	this->work_area = work_area;
}

string Staff::getWorkArea()
{
	return work_area;
}

void Staff::setWorkArea(string work_area)
{
	this->work_area = work_area;
}

People::~People() {
	// TODO Auto-generated destructor stub
}

