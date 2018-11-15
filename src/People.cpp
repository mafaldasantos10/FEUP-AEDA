/*
 * People.cpp
 *
 *  Created on: Oct 17, 2018
 *
 */

#include "People.h"
#include "College.h"
#include <map>

int Student::student_count = 1;
int Teacher::teacher_count = 1;
int Staff::staff_count = 1;

//////PEOPLE//////

People::People(string name, string address, date& birthday, unsigned int phone, string cod) {
	this->name = name;
	this->address = address;
	this->birthday = &birthday;
	this->phone = phone;
	this->code = cod;
}

void People::addPerson(College &college) {
    cout << "Insert Name: " << flush;
    getline(cin, name);
    while(!hasNoNumber(name))
    {
        cout<<"Invalid name, try again"<<endl;
        getline(cin, name);
    }

    cout << "\nInsert Address: " << flush;
    getline(cin, address);

    cout << "\nInsert Phone Number (9-digit): " << flush;
    cin >> phone;
    while(cin.fail() || to_string(phone).size() != 9)
    {
        cout << "Invalid phone number, try again: "<< endl;
        cin.clear();
        cin.ignore(100, '\n');
        cin >> phone;
    }
    birthday = readDate(); //Tests if date is written correctly
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

string People::getCode()
{
	return code;
}

void People::setCode(string newCod)
{
	code=newCod;
}

date* People::getDate()
{
	return birthday;
}

int People::editInfo() {
    cout << "0:   NAME" << endl;
    return 1;
}

void People::Set(int n) {
    switch(n){
        case 0:
            return;
    }
}

void People::showInfo() {
    cout << "\n|-----------------------------------------" << endl;
    cout << "|      " << name << endl;
    cout << "| Address: " << address << endl;
    cout << "| Code: " << code << " Phone: " << phone << endl;
    cout << "| Birthday: " << birthday->format << endl;

}

ostream& People::write(ostream &os) {
    os << name << "|" << address << "|" << phone << "|" << code << "|" << birthday->format << "|";
    return os;
}

//////STUDENT//////

Student::Student(string name, string address, date birthday, unsigned int phone, string cod, Course* course, map <Uc*, float> subjects)
: People(name, address, birthday, phone, cod){
	this->course = course;
	year = 0;
    student_count++;
}

void Student::addPerson(College &college) {
    People::addPerson(college);
    string uc_name;
    Uc* uc;
    float grade;
    string code = "0" + to_string(current_year) + to_string(Student::student_count);  //student id is assigned
    setCode(code);

    cout << "\nChoose Student's Course:" << endl;  //Needs exception in case there are no Courses Created
    Print_Vec(college.getCourses());
    course = college.getCourses().at(Nav(0,college.getCourses().size()-1));

    cout << "\nInsert Student's Year: " << flush;
    cin >> year;
    while(cin.fail() || year > 5 || year < 0)
    {
        cout << "Invalid year, try again: "<< endl;
        cin.clear();
        cin.ignore(100, '\n');
        cin >> year;
    }

    bool end = false;
    while(1){
        while(1){
            cout << "\nInsert Student's UC(? - list/ ! - done): " << flush;
            getline(cin, uc_name);
            if(uc_name == "!"){
                end = true;
                break;
            }
            else if(uc_name == "?") Print_Vec(course->getUCs());
            else {
                try{
                    uc = (SearchVec(course->getUCs(),uc_name));
                }
                catch(string err){
                    cout << err << " " << "Try again:" << endl;
                    continue;
                }
                if(subjects.find(uc) == subjects.end()){
                    cout << "Student already enrolled in this course, try again: " << endl;
                    continue;
                }
                break;
            }
        }
        if(end) break;

        cout << "\nInsert Student's UC grade(-1 if not-evaluated): " << flush;
        cin >> grade;
        while(cin.fail() || grade > 20 || grade < -1)
        {
            cout << "Invalid grade, try again: "<< endl;
            cin.clear();
            cin.ignore(100, '\n');
            cin >> grade;
        }
        addUCGrade(uc, grade);
    }
    college.addStudent(this);
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
    People::showInfo();
	cout << "| Course: " << getCourseName() << endl;
    cout << "| Year: " << year << endl;
	cout << "|-----------------------------------------" << endl;
}

void Student::addUCGrade(Uc* uc, float grade)
{
	subjects.insert(pair <Uc*, float> (uc, grade));
}

void Student::removeFromMap(string name)
{
	Uc* uc;

	for(unsigned int i = 0; i < course->getUCs().size(); i++)
	{
		if(course->getUCs().at(i)->getName() == name)
		{
			uc = course->getUCs().at(i);
			break;
		}
	}

	for (auto it = subjects.find(uc); it != subjects.end(); it++)
	{
		subjects.erase(uc);
		break;
	}
}

void Student::changeGrade(string name, int grade)
{
	Uc* uc;

	for(unsigned int i = 0; i < course->getUCs().size(); i++)
	{
		if(course->getUCs().at(i)->getName() == name)
		{
			uc = course->getUCs().at(i);
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
		if(course->getUCs().at(i)->getName() == name)
		{
			uc = course->getUCs().at(i);
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

ostream& Student::write(ostream &os) {
    People::write(os);
    os << course->getName() << "|" << year << "|[" ;
    for(auto it = subjects.begin(); it != subjects.end(); it++){
        os << "(" << it->first->getName() << "," << it->second << ")";
    }
    os << "]" << endl;
}

//////EMPLOYEE//////

Employee::Employee(string name, string address, date birthday, unsigned int phone, string cod, float salary, unsigned int nif)
: People(name, address, birthday, phone, cod){
	this->salary = salary;
	this->nif = nif;
}

void Employee::addPerson(College &college){
    cout << "\nInsert Employee's Salary: " << flush;
    cin >> salary;
    cin.clear();
    cin.ignore(1000,'\n');
    cout << "\nInsert Employee's NIF: " << flush;
    cin >> nif;
    cin.clear();
    cin.ignore(1000,'\n');
}

int Employee::Special_Info(){
    cout << "| NIF: " << getNIF() << " salary: " << getSalary() << endl;
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

ostream& Employee::write(ostream& os){
    os << salary << "|" << nif << "|";
}

//////TEACHER//////

Teacher::Teacher(string name, string address, date birthday, unsigned int phone, string cod, float salary, unsigned int nif, string category, vector<Uc *> subjects)
: Employee(name, address, birthday, phone, cod, salary, nif){
	this->category = category;
	this->subjects = subjects;
}

Teacher::~Teacher()
{
	dest_remove(subjects);
}

void Teacher::addPerson(College &college){
    People::addPerson(college);
    Employee::addPerson(college);
    cout << "\nInsert Teacher's Category: " << flush; //Needs to check for valid category
    getline(cin,category);
    string uc_name;
    Uc* uc;
    while(1){
        cout << "\nInsert Teacher's Ucs(? - list/ ! - done): " << flush;
        getline(cin, uc_name);
        if(uc_name == "!") break;
        else if(uc_name == "?") {
            Print_Vec(college.getUCs());
        }
        else {
            try{
                uc = (SearchVec(college.getUCs(),uc_name));
            }
            catch(string err){
                cout << err << " " << "Try again:" << endl;
                continue;
            }
            subjects.push_back(uc);
        }
    }
    college.addTeacher(this);
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
	People::showInfo();
	cout << "| Category: " << category << endl;
	cout << "|-----------------------------------------" << endl;
}

ostream& Teacher::write(ostream &os) {
    People::write(os);
    Employee::write(os);
    os << category << "|[" ;
    for(int i = 0; i < subjects.size(); i++){
        os << "(" << subjects.at(i)->getName() << ")";
    }
    os << "]" << endl;
}

//////STAFF//////

Staff::Staff(string name, string address, date birthday, unsigned int phone, string cod, float salary, unsigned int nif, string work_area)
: Employee(name, address, birthday, phone, cod, salary, nif){
	this->work_area = work_area;
}

void Staff::addPerson(College &college){
    cout << "Insert Staff member's working area: " << flush;
    getline(cin,work_area);
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
	People::showInfo();
	cout << "| Work Area: " << getWorkArea() << endl;
	cout << "|-----------------------------------------" << endl;
}

ostream& Staff::write(ostream& os){
    People::write(os);
    Employee::write(os);
    os << work_area << endl;
}

ostream& operator<< (ostream& os, Staff &staff){
    staff.write(os);
    return os;
}

ostream& operator<< (ostream& os, Teacher &teacher){
    teacher.write(os);
    return os;
}

ostream& operator<< (ostream& os, Student &student){
    student.write(os);
    return os;
}
