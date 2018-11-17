	/*
 * College.cpp
 *
 *  Created on: 15/10/2018
 */

#include "College.h"

using namespace std;


//INPUT VALIDATION//
bool hasNoNumber(string s)
{
    return(s.find_first_of("0123456789") == string::npos);
}


//COLLEGE//
//////////////////////
College::College(string name)
{
	colName = name;
}

string College::getName() const
{
	return colName;
}

College::~College()
{
	dest_remove(students);
	dest_remove(teachers);
	dest_remove(staff);
	dest_remove(vecDep);
}

void College::setName(string name)
{
	colName = name;
}

string College::getAdmin(){
    return admin;
}

void College::setAdmin(string admin)
{
	this->admin = admin;
}

vector<Department*> College::getDepartments()
{
    return vecDep;
}

vector<Teacher *> College::getTeachers()
{
    return teachers;
}

vector<Student *> College::getStudents()
{
    return students;
}

vector<Staff *> College::getStaff()
{
    return staff;
}

void College::addTeacher(Teacher *teacher)
{
    teachers.push_back(teacher);
}

void College::addStudent(Student *student)
{
    students.push_back(student);
}

void College::addStaff(Staff *staff)
{

    this->staff.push_back(staff);
}

void College::showInfo()
{
    cout << "\n----------------------" << endl;
    cout << "|       " << colName <<"        |" << endl;
    cout << "----------------------" << endl;
}

vector<Course *> College::getCourses()
{
    vector<Course *> vec;
    for(unsigned int i = 0; i < vecDep.size() ; i++)
    {
        for(unsigned int j = 0; j < vecDep.at(i)->getCourses().size(); j++)
        {
            vec.push_back(vecDep.at(i)->getCourses().at(j));
        }
    }
    return vec;
}

vector<Uc*> College::getUCs(){
    vector<Course *> cr = getCourses();
    vector<Uc*> vec;
    vector<Uc*> course_ucs;
    for(unsigned int i = 0; i < cr.size(); i++){
        course_ucs = cr.at(i)->getUCs();
        vec.insert(vec.end(),course_ucs.begin(),course_ucs.end());
    }
    return vec;
}

void College::removeStudent(Student* student) {

	 for(unsigned int i=0; i<students.size(); i++)
	   {
		   if(students.at(i) == student)
		   {
			   delete students.at(i);
			   students.erase(students.begin() + i);
		   }
	   }
}

void College::removeTeacher(Teacher* teacher){

   for(unsigned int i=0; i<teachers.size(); i++)
   {
	   if(teachers.at(i) == teacher)
	   {
		   delete teachers.at(i);
		   teachers.erase(teachers.begin() + i);
	   }
   }
}

void College::removeStaff(Staff* staffx){

	for(unsigned int i=0; i<staff.size(); i++)
   {
		if(staff.at(i) == staffx)
	   {
		   delete staff.at(i);
		   staff.erase(staff.begin() + i);
	   }
   }
}

void College::addDepartment()
{
	string name, address, directorName;
	int code, phone;
	bool differentCode = true;

	cout << "Enter the name of the Department: "<< endl;
	getline(cin, name);
	while(!hasNoNumber(name))
	{
		cout << "Invalid name, try again: "<< endl;
		getline(cin, name);
	}

	cout << "Enter the address of the Department: "<< endl;
	getline(cin, address);

	Teacher* director;

    while(1){ //Needs to check if Director Exists
        cout << "Enter the name of the director of the Department (! to skip/ ? for list): "<< endl;
        getline(cin, directorName);
        if (directorName == "!") break;
        else if(directorName == "?") Print_Vec(College::getTeachers());
        else{
            try{
                director = SearchVec(College::getTeachers(),directorName);
            }
            catch(NoNameFound &err){
                cout << err.errorMessage() << endl;
                cout << "Invalid name, try again: "<< flush;
                continue;
            }
            break;
        }
    }

	cout << "Enter the code of the Department: "<< endl;

	do{
		cin >> code;

		for(unsigned int i = 0; i < vecDep.size(); i++)
		{
			if(vecDep.at(i)->getCode() == code)
			{
				cout << "The code you entered is already associated to Department" << "'" << vecDep.at(i)->getName() << "'" << endl;
				cout << "Enter a new one: " << endl;
				differentCode = false;
				break;
			}
		}

	} while (!differentCode);

	//falta fazer validation do code!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	cout << "Enter the phone of the Department (9-digit): "<< endl;
	cin >> phone;
	while(cin.fail() || to_string(phone).size() != 9)
	{
		cout << "Invalid phone number, try again: "<< endl;
		cin.clear();
		cin.ignore(100, '\n');
		cin >> phone;
	}

	Department* dp;

	if (directorName != "!")
	{
		 dp = new Department(name, code, address, phone, director);
	}
	else
	{
		dp = new Department(name, code, address, phone);
	}
	vecDep.push_back(dp);
}

void College::removeDepartment()
{
	int code;
	string name;

	cout << "Enter the code of the Department to remove: "<< endl;
	cin >> code;
	while(cin.fail())
	{
		cout << "Invalid code, try again: "<< endl;
		cin.clear();
		cin.ignore(100, '\n');
		cin >> code;
	}

	for(unsigned int i = 0; i < vecDep.size(); i++)
	{
		if(vecDep.at(i)->getCode() == code)
		{
			name = vecDep.at(i)->getName();
			delete vecDep.at(i);
			vecDep.erase(vecDep.begin() + i);
			cout << "Department " << code << "(" << name << ")" << " has been successfully removed. "<< endl;
			return;
		}
	}

	throw NoCodeFound(code);
}

void College::addCourse(){
    cout << "In Which Department do you want to add a course?" << endl;
    Print_Vec(vecDep);
    cout << vecDep.size() << ":   PREVIOUS MENU" << endl;
    unsigned int i = Nav(0,vecDep.size());
    if(i == vecDep.size()) return;
    else vecDep.at(i)->addCourse();
}
void College::removeCourse(){
    cout << "In Which Department do you want to remove a course?" << endl;
    Print_Vec(vecDep);
    cout << vecDep.size() << ":   PREVIOUS MENU" << endl;
    unsigned int i = Nav(0,vecDep.size());
    if(i == vecDep.size()) return;
    else vecDep.at(i)->removeCourse();
}

void College::searchDepartment(string name)
{
	Department* dep;
	dep = SearchVec(vecDep, name);
	dep->showInfo();
}

ostream& operator<< (ostream& os, const College &college){
    os << college.colName << "|" << college.admin << endl;
    return os;
}

//DEPARTMENT//
//////////////////////
Department:: Department(string name, int code, string address, int phone, Teacher* director)
{
	depName = name;
	depCode = code;
	depAddress = address;
	depPhone = phone;
	depDirector = director;
}

Department:: Department(string name, int code, string address, int phone)
{
    depDirector = nullptr;
	depName = name;
	depCode = code;
	depAddress = address;
	depPhone = phone;
}

Department::~Department()
{
	dest_remove(vecCourse);
	delete depDirector;
}
void Department::showInfo() {
    string dep_name;
    if(depDirector != nullptr) dep_name = depDirector->getName();
    else dep_name = "!Unassigned!";
    cout << "\n|-----------------------------------------" << endl;
    cout << "|      " << depName << "      " << endl;
    cout << "| Address: " << depAddress << endl;
    cout << "| Code: " << depCode << " Phone: " << depPhone << endl;
    cout << "| Dep. Director: " << dep_name << endl;
    cout << "|-----------------------------------------" << endl;
}

int Department::editInfo(){
    showInfo();
    cout << "Which parameter do you want to edit?" << endl;
    cout << "0:   NAME" << endl;
    cout << "1:   ADDRESS" << endl;
    cout << "2:   CODE" << endl;
    cout << "3:   PHONE" <<   endl;
    cout << "4:   DIRECTOR" << endl;
    cout << "5:   PREVIOUS" << endl;
    return 5;
}

void Department::Set(int n){
    string s;
    int i;
    switch(n){
        case 0:
            cout << "Insert new name: " << flush;
            cin >> s;
            while(!hasNoNumber(s))
            {
               	cout<<"Invalid name, try again"<<endl;
               	cin >> s;
            }
            setName(s);
            break;
        case 1:
            cout << "Insert new address: " << flush;
            cin >> s;
            setAddress(s);
            break;
        case 2:
            cout << "Insert new code: " << flush;
            cin >> i;
            while(cin.fail())
            {
            	cout << "Invalid code, try again: "<< endl;
            	cin.clear();
            	cin.ignore(100, '\n');
            	cin >> i;
            }

            setCode(i);
            break;
        case 3:
            cout << "Insert new phone number: " << flush;
            cin >> i;
            while(cin.fail() || to_string(i).size() != 9)
            {
               	cout << "Invalid phone number, try again: "<< endl;
               	cin.clear();
               	cin.ignore(100, '\n');
               	cin >> i;
            }
            setPhone(i);
            break;
        case 4: //NEEDS TO TEST IF NEW TEACHER EXISTS!!
            cout << "Insert new Director name: " << flush;
            cin >> s;
            Teacher* Dir;
            setDirector(Dir);
            break;
    }
}

string Department::getName()
{
	return depName;
}

void Department::setName(string name)
{
	depName = name;
}

string Department::getAddress()
{
	return depAddress;
}

void Department::setAddress(string address)
{
	depAddress = address;
}

Teacher* Department::getDirector()
{
	return depDirector;
}

void Department::setDirector(Teacher* director)
{
	depDirector = director;
}

int Department::getCode()
{
	return depCode;
}

void Department::setCode(int code)
{
	depCode = code;
}

int Department::getPhone()
{
	return depPhone;
}

void Department::setPhone(int phone)
{
	depPhone = phone;
}
vector<Course*> Department::getCourses()
{
	return vecCourse;
}

void Department::addCourse()
{
	string type, ptName, engName;
	int code;

	cout << "Enter the name of the course in Portuguese: "<< endl;
	getline(cin,ptName);
	while(!hasNoNumber(ptName))
	{
		cout << "Invalid name, try again"<<endl;
        getline(cin,ptName);
	}

	cout << "Enter the name of the course in English: " << endl;
    getline(cin,engName);
	while(!hasNoNumber(engName))
	{
		cout << "Invalid name, try again: " << endl;
        getline(cin,engName);
	}

	cout << "What type of course is it? (MI,M,L) "<< endl;
	cin >> type;
	while(!hasNoNumber(type) || (type != "MI" && type != "M" && type != "L"))
	{
		cout << "Invalid type, try again" << endl;
		cin >> type;
	}

	cout << "Enter the code of the course: "<< endl;
	cin >> code;
	while(cin.fail())
	{
	     cout << "Invalid code, try again: " << endl;
	     cin.clear();
	     cin.ignore(100, '\n');
	     cin >> code;
	}

	Course* newCourse = new Course(type, engName, ptName, code);
	vecCourse.push_back(newCourse);
}

void Department::removeCourse()
{
	int code;
	string name;

	cout << "Enter the code of the Course to remove: "<< endl;
	cin >> code;
	while(cin.fail())
	{
	    cout << "Invalid code, try again: "<< endl;
	    cin.clear();
	    cin.ignore(100, '\n');
	    cin >> code;
	}

	for(unsigned int i = 0; i < vecCourse.size(); i++)
	{
		if(vecCourse.at(i)->getCode() == code)
		{
			name = vecCourse.at(i)->getEngName();
			delete vecCourse.at(i);
			vecCourse.erase(vecCourse.begin() + i);
			cout << "Course " << code << "(" << name << ")" << " has been successfully removed. "<< endl;
			return;
		}
	}

	throw NoCodeFound(code);
}

void Department::searchCourse(string name)
{
	Course* cs;
	cs = SearchVec(vecCourse, name);
	cs->showInfo();
}

ostream& operator<< (ostream& os, const Department &dep){
    os << dep.depName << "|" << dep.depAddress << "|" << dep.depCode << "|" << dep.depPhone << endl;
    for(size_t i = 0; i < dep.vecCourse.size(); i++){
        os << "COURSE:" << endl;
        os << *dep.vecCourse.at(i);
    }
    return os;
}

//COURSE//
//////////////////////
Course::Course(string type, string engName, string ptName, int code)
{
	csCode = code;
	csType = type;
	csEngName = engName;
	csPtName = ptName;
}

Course::~Course()
{
	dest_remove(vecUC);
}
void Course::showInfo() {
    cout << "\n|-----------------------------------------" << endl;
    cout << "|      " << csEngName << endl;
    cout << "|      " << csPtName << endl;
    cout << "| Type: " << csType << endl;
    cout << "|-----------------------------------------" << endl;
}

int Course::editInfo(){
    showInfo();
    cout << "Which parameter do you want to edit?" << endl;
    cout << "0:   Pt_NAME" << endl;
    cout << "1:   Eng_NAME" << endl;
    cout << "2:   TYPE" << endl;
    cout << "3:   CODE" <<   endl;
    cout << "4:   PREVIOUS MENU" << endl;
    return 4;
}

void Course::Set(int n){
    string s;
    //int i;
    switch(n){
        case 0:
            cout << "\nInsert New Pt_name: " << flush;
            getline(cin, s);
            while(!hasNoNumber(s))
           	{
            	cout << "Invalid name, try again: " << endl;
           	    cin >> s;
           	}
            setPtName(s);
            break;
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
    }
}

void Course::showSyllabus()
{
	sortUc();

	for(unsigned int i = 0; i < vecUC.size(); i++)
	{
		if(i == 0)
		{
			cout << "First year Modules: " << endl << endl;
		}

		if(vecUC.at(i)->getYear() == 1)
		{
			cout << vecUC.at(i)->getName() << endl;
		}

		if((vecUC.at(i-1)->getYear() == 1||i==0) && vecUC.at(i)->getYear() == 2)
		{
			cout << "Second year Modules:" << endl << endl;
		}

		if(vecUC.at(i)->getYear() == 2)
		{
			cout << vecUC.at(i)->getName() << endl;
		}

		if((vecUC.at(i-1)->getYear() == 2 || i== 0) && vecUC.at(i)->getYear() == 3)
		{
			if(csType == "M")
			{
				return;
			}
			cout << "Third year Modules:" << endl << endl;
		}

		if(vecUC.at(i)->getYear() == 3)
		{
			cout << vecUC.at(i)->getName() << endl;
		}

		if((vecUC.at(i-1)->getYear() == 3 || i == 0)&& vecUC.at(i)->getYear() == 4)
		{
			if(csType == "L")
			{
				return;
			}
			cout << "Fourth year Modules:" << endl << endl;
		}

		if(vecUC.at(i)->getYear() == 4)
		{
			cout << vecUC.at(i)->getName() << endl;
		}

		if((vecUC.at(i-1)->getYear() == 4 || i==0) && vecUC.at(i)->getYear() == 5)
		{
			cout << "Fifth year Modules:" << endl << endl;
		}

		if(vecUC.at(i)->getYear() == 5)
		{
			cout << vecUC.at(i)->getName() << endl;
		}
	}
}

string Course::getType()
{
	return csType;
}

void Course::setType(string type)
{
	csType = type;
}

string Course::getName()
{
	return csPtName;
}

void Course::setPtName(string ptName)
{
	csPtName = ptName;
}

string Course::getEngName()
{
	return csEngName;
}

void Course::setEngName(string engName)
{
	csEngName = engName;
}

int Course::getCode()
{
	return csCode;
}

void Course::setCode(int code)
{
	csCode = code;
}

vector<Uc*> Course::getUCs()
{
	return vecUC;
}

void Course::addUC()
{
	string name, nameT, nameS;
	int year, ects, workload;// nS, nT;
	vector<string> teachers, students;

	cout << "Enter the name of the Curricular Unit: "<< endl;
	cin >> name;
	while(!hasNoNumber(name))
	{
		cout << "Invalid name, try again:" << endl;
		cin >> name;
	}

	cout << "In which year is it taught? "<< endl;
	cin >> year;
	while(cin.fail() || year > 5 || year < 1)
	{
		cout << "Invalid year, try again: "<< endl;
		cin.clear();
		cin.ignore(100, '\n');
		cin >> year;
	}

	cout << "How many ETCS does it have? "<< endl;
	cin >> ects;
	while(cin.fail() || ects > 10 || ects < 0)
	{
		cout << "Invalid number of etcs, try again: "<< endl;
		cin.clear();
		cin.ignore(100, '\n');
		cin >> year;
	}

	cout << "How many hours of workload? "<< endl;
	cin >> workload;
	while(cin.fail() || workload > 10 || workload < 0)
	{
		cout << "Invalid number of hours, try again: "<< endl;
		cin.clear();
		cin.ignore(100, '\n');
		cin >> workload;
	}

	Uc* newUC = new Uc(name, year, ects, workload);
	vecUC.push_back(newUC);
}

void Course::removeUC()
{
	string name;

	cout << "Enter the name of the UC to remove: "<< endl;
	getline(cin, name); //input validation
	while(!hasNoNumber(name))
	{
		cout<<"Invalid name, try again"<<endl;
		getline(cin, name);
	}

	for(unsigned int i = 0; i <= vecUC.size(); i++)
	{
		if(vecUC.at(i)->getName() == name)
		{
			delete vecUC.at(i);
			vecUC.erase(vecUC.begin() + i);
			cout << "Course " << name << " has been successfully removed. "<< endl;
			return;
		}
	}

	throw NoNameFound(name);
}

void Course::sortUc()
{
	for(unsigned int j= vecUC.size() -1; j>0; j--)
	{
		bool troca = false;

		for(unsigned int i=0; i<j; i++)
		{
			if(vecUC.at(i+1)->getYear() < vecUC.at(i)->getYear())
			{
				swap(vecUC.at(i), vecUC.at(i+1));
				troca = true;
			}

			if(vecUC.at(i+1)->getYear() < vecUC.at(i)->getYear())
			{
				if(vecUC.at(i+1)->getName() < vecUC.at(i)->getName())
				{
					swap(vecUC.at(i), vecUC.at(i+1));
					troca = true;
				}
			}
		}

		if (!troca) return;
	}
}

void Course::searchUc(string name)
{
	Uc* uc;
	uc = SearchVec(vecUC, name);
	uc->showInfo();
}

ostream& operator<< (ostream& os, const Course &course){
    os << course.csPtName << "|" << course.csEngName << "|" << course.csCode << "|" << course.csType << endl;
    for(size_t i = 0; i < course.vecUC.size(); i++){
        os << "UC:" << endl;
        os << *course.vecUC.at(i);
    }
    return os;
}


//UC//
//////////////////////
Uc::Uc(string name, vector<Teacher*> teacher, vector<Student*> student, int year, int ects, int workload)
{
	ucECTS = ects;
	ucName = name;
	ucStudent = student;
	ucTeacher = teacher;
	ucWorkload = workload;
	ucYear = year;
}

Uc::Uc(string name, int year, int ects, int workload)
{
	ucECTS = ects;
	ucName = name;
	ucWorkload = workload;
	ucYear = year;
}

Uc::~Uc()
{
	dest_remove(ucStudent);
	dest_remove(ucTeacher);
}

void Uc::showInfo() {
    cout << "\n|-----------------------------------------" << endl;
    cout << "|      " << ucName << endl;
    cout << "| Year: " << ucYear << endl;
    cout << "| ECTS: " << ucECTS << endl;
    cout << "| Workload: " << ucWorkload << endl;
    cout << "| Regent: " << ucTeacher.at(0)->getName() << endl;
    cout << "|-----------------------------------------" << endl;
}

void Uc::showStudents()
{
	for(unsigned int i = 0; i < ucStudent.size(); i++)
	{
		cout << i << ": 	" <<ucStudent.at(i)->getName() << endl;
	}
}

void Uc::showTeachers()
{
	for(unsigned int i = 0; i < ucStudent.size(); i++)
	{
		cout << i << ": 	" <<ucStudent.at(i)->getName() << endl;
	}
}

string Uc::getName()
{
	return ucName;
}

void Uc::setName(string name)
{
	ucName = name;
}

int Uc::getYear()
{
	return ucYear;
}

void Uc::setYear(int year)
{
	ucYear = year;
}

int Uc::getECTS()
{
	return ucECTS;
}

void Uc::setECTS(int ects)
{
	ucECTS = ects;
}

int Uc::getWorkload()
{
	return ucWorkload;
}

void Uc::setWorkload(int workload)
{
	ucWorkload = workload;
}

vector<Teacher*> Uc::getTeachers()
{
	return ucTeacher;
}

vector<Student*> Uc::getStudents()
{
	return ucStudent;
}

void Uc::removeTeacher()
{
	string name;

	cout << "Enter the name of the Teacher to remove: "<< endl;
	cin >> name; //input validation
	while(!hasNoNumber(name))
	{
		cout << "Invalid name, try again" << endl;
		cin >> name;
	}

	if(remove(ucTeacher, name))
	{
		cout << "Teacher " << name << " has been successfully removed. "<< endl;
		return;
	}

	throw NoNameFound(name);
}

void Uc::removeStudent()
{
	string name;

	cout << "Enter the name of the Student to remove: "<< endl;
	cin >> name; //input validation
	while(!hasNoNumber(name))
	{
		cout << "Invalid name, try again: " << endl;
		cin >> name;
	}

	if(remove(ucStudent, name))
	{
		cout << "Student" << name << " has been successfully removed. "<< endl;
		return;
	}

	throw NoNameFound(name);
}

//Compare UCs
bool Uc::operator<(Uc uc2)
{
	if(ucECTS < uc2.getECTS())
	{
		return true;
	}

	if(ucECTS == uc2.getECTS())
	{
		if(ucWorkload < uc2.getWorkload())
		{
			return true;
		}
	}

	return false;
}

ostream& operator<< (ostream& os, const Uc &uc){
    os << uc.ucName << "|" << uc.ucYear << "|" << uc.ucECTS << "|" << uc.ucWorkload << endl;
    return os;
}
