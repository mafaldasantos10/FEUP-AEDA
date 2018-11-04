/*
 * People.cpp
 *
 *  Created on: Oct 17, 2018
 *
 */

#include "People.h"
#include "College.h"
#include <map>

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

int People::Edit_Info() {
    cout << "0:   NAME" << endl;
    return 1;
}

void People::Set(int n) {
    switch(n){
        case 0:
            return;
    }
}

void People::Show_Info() {
    cout << "| " << name << endl;
}

//////STUDENT//////

Student::Student(string name, string address, date birthday, unsigned int phone, unsigned int cod, Course* course, map <Uc*, float> subjects)
: People(name, address, birthday, phone, cod){
	this->course = course;
	grade = 0;
}

Course* Student::getCourse()
{
	return course;
}
 int Student::Special_Info(){
    cout << "0:   SHOW GRADES" << endl;
     return 1;
}

map <Uc*, float>* Student::getGrades() {
    return &subjects;
}

string Student::getCourseName()
{
	return course->getEngName();
}

void Student::showInfo(){

	cout << "|      " << getName() << "      |" << endl;
	cout << "| Address: " << getAddress() << endl;
	cout << "| Code: " << getCode() << " Phone: " << getPhone() << endl;
	cout << "| Birthday: " << getDate() << endl;
	cout << "| Course: " << getCourseName() << endl;
	cout << "|-----------------------------------------" << endl;
}

void Student::addUCGrade(string name, float grade)
{
	Uc* uc;

	for(unsigned int i = 0; i < course->getUCs().size(); i++)
	{
		if(course->getUCs().at(i).getName() == name)
		{
			uc = &course->getUCs().at(i);
			break;
		}
	}

	subjects.insert(pair <Uc*, float> (uc, grade));
}

void Student::removeFromMap(string name)
{
	Uc* uc;

	for(unsigned int i = 0; i < course->getUCs().size(); i++)
	{
		if(course->getUCs().at(i).getName() == name)
		{
			uc = &course->getUCs().at(i);
			break;
		}
	}

	for (auto it = subjects.find(uc); it != subjects.end(); it++)
	{
		subjects.erase(uc);
		break;
	}
}

void Student::changeGrade(string name)
{
	Uc* uc;

	for(unsigned int i = 0; i < course->getUCs().size(); i++)
	{
		if(course->getUCs().at(i).getName() == name)
		{
			uc = &course->getUCs().at(i);
			break;
		}
	}

	for (auto it = subjects.find(uc); it != subjects.end(); it++)
	{
		  it->second = grade;
		  break;
	}
}

void Student::showUCGrade(string name)
{
	Uc* uc;

	for(unsigned int i = 0; i < course->getUCs().size(); i++)
	{
		if(course->getUCs().at(i).getName() == name)
		{
			uc = &course->getUCs().at(i);
			break;
		}
	}

	cout << "MODULE\tGRADE\n";

	for (auto it = subjects.find(uc); it != subjects.end(); it++)
	{
		cout << it->first
			 << '\t' << it->second << '\n';
		break;
	}
}

void Student::showAllGrades()
{
	cout << "MODULE\tGRADE\n";

	for (map<Uc*,float>::iterator it=subjects.begin(); it!=subjects.end(); ++it)
	{
		cout << it->first
			 << '\t' << it->second << '\n';
	}
}


//////EMPLOYEE//////

Employee::Employee(string name, string address, date birthday, unsigned int phone, unsigned int cod, float salary, unsigned int nif)
: People(name, address, birthday, phone, cod){
	this->salary = salary;
	this->nif = nif;
}

int Employee::Special_Info(){
    cout << "| nif: " << getNIF() << " salary: " << getSalary() << endl;
    return 0;
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

void Teacher::showInfo()
{
	cout << "|      " << getName() << "      |" << endl;
	cout << "| Address: " << getAddress() << endl;
	cout << "| Code: " << getCode() << " Phone: " << getPhone() << endl;
	cout << "| Birthday: " << getDate() << endl;
	cout << "| Salary: "<< getSalary() << endl;
	cout << "| NIF: "<< getNIF() << endl;
	cout << "| Category: " << category << endl;
	cout << "|-----------------------------------------" << endl;
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

void Staff::showInfo()
{
	cout << "|      " << getName() << "      |" << endl;
	cout << "| Address: " << getAddress() << endl;
	cout << "| Code: " << getCode() << " Phone: " << getPhone() << endl;
	cout << "| Birthday: " << getDate() << endl;
	cout << "| Salary: "<< getSalary() << endl;
	cout << "| NIF: "<< getNIF() << endl;
	cout << "| Work Area: " << getWorkArea() << endl;
	cout << "|-----------------------------------------" << endl;
}

People::~People() {
	// TODO Auto-generated destructor stub
}

