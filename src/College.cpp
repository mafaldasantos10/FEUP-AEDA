	/*
 * College.cpp
 *
 *  Created on: 15/10/2018
 */

#include "College.h"

using namespace std;

//COLLEGE//
//////////////////////
College::College(string name) /*college constructor*/
{
	colName = name; /*name of the college 1*/
}

string College::getName()
{
	return colName;
}

void College::setName(string name)
{
	colName = name;
}

void College::showDepartments()
{
	for(unsigned int i = 0; i < vecDep.size(); i++)
	{
		cout << i << ": 	" <<vecDep.at(i).getName() << endl;
	}
}

vector<Department> College::getDepartments(){
    return vecDep;
}

vector<vector<People*>> College::getPeople(){
    return people;
}

void College::addDepartment()
{
	string name, address, directorName;
	int code, phone;
	bool differentCode = true;

	cout << "Enter the name of the Department: "<< endl;
	getline(cin, name);

	cout << "Enter the address of the Department: "<< endl;
	getline(cin, address);

	cout << "Enter the name of the director of the Department: "<< endl;  //NEEDS TO TEST IF DIRECTOR_NAME BELONGS TO AN EXISTING TEACHER
	getline(cin, directorName);
    int i = 0;  //This is just so that the code can compile
    Teacher* director;
    if(people.at(0).at(i)->getName() == directorName){
        director = dynamic_cast<Teacher*>(people.at(0).at(i)); //dynamic cast testa e transforma o apontador de people num apontador de teacher
    }

	cout << "Enter the code of the Department: "<< endl;  //NEEDS TO TEST IF IT'S DIFFERENT FROM OTHER DEP CODES
	do{
		cin >> code;

		for(unsigned int i = 0; i < vecDep.size(); i++)
		{
			if(vecDep.at(i).getCode() == code)
			{
				cout << "The code you entered is already associated to Department" << "'" << vecDep.at(i).getName() << "'" << endl;
				cout << "Enter a new one: " << endl;
				differentCode = false;
				break;
			}
		}

	} while (!differentCode);

	cout << "Enter the phone of the Department: "<< endl;
	cin >> phone;

	Department newDepartment(name, code, address, phone, director);
	vecDep.push_back(newDepartment);
}

void College::removeDepartment()
{
	int code;
	string name;

	cout << "Enter the code of the Department to remove: "<< endl;
	cin >> code; //input validation

	for(unsigned int i = 0; i <= vecDep.size(); i++)
	{
		if(vecDep.at(i).getCode() == code)
		{
			name = vecDep.at(i).getName();

			vecDep.erase(vecDep.begin() + i);
			cout << "Department " << code << "(" << name << ")" << " has been successfully removed. "<< endl;
			return;
		}
	}

	throw NoCodeFound(code);
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

void Department::Show_Info() {
    cout << "|      " << depName << "      |" << endl;
    cout << "| Address: " << depAddress << endl;
    cout << "| Code: " << depCode << " Phone: " << depPhone << endl;
    cout << "| Dep. Director: " << depDirector->getName() << endl;
    cout << "|-----------------------------------------" << endl;
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
vector<Course> Department::getCourses()
{
	return vecCourse;
}

void Department::addCourse()
{
	string type, ptName, engName;
	int code;

	cout << "Enter the name of the course in Portuguese: "<< endl;
	cin >> ptName;

	cout << "Enter the name of the course in English: "<< endl;
	cin >> engName;

	cout << "What type of course is it? "<< endl;
	cin >> type;

	cout << "Enter the code of the course: "<< endl;
	cin >> code;

	Course newCourse(type, engName, ptName, code);
	vecCourse.push_back(newCourse);
}

void Department::removeCourse()
{
	int code;
	string name;

	cout << "Enter the code of the Course to remove: "<< endl;
	cin >> code; //input validation

	for(unsigned int i = 0; i <= vecCourse.size(); i++)
	{
		if(vecCourse.at(i).getCode() == code)
		{
			name = vecCourse.at(i).getEngName();

			vecCourse.erase(vecCourse.begin() + i);
			cout << "Course " << code << "(" << name << ")" << " has been successfully removed. "<< endl;
			return;
		}
	}

	throw NoCodeFound(code);
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

string Course::getType()
{
	return csType;
}

void Course::setType(string type)
{
	csType=type;
}

string Course::getPtName()
{
	return csPtName;
}

void Course::setPtName(string ptName)
{
	csPtName=ptName;
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

vector<Uc> Course::getUCs()
{
	return vecUC;
}

void Course::addUC()
{
	string name, nameT, nameS;
	int year, ects, workload, nS, nT;
	vector<string> teachers, students;

	cout << "Enter the name of the Curricular Unit: "<< endl;
	cin >> name;

	cout << "In which year is it taught? "<< endl;
	cin >> year;

	cout << "How many ETCS does it have? "<< endl;
	cin >> ects;

	cout << "How many hours of workload? "<< endl;
	cin >> workload;

	cout << "Enter the number of students: "<< endl;
	cin >> nS ;

	cout << "Enter their names one by one: "<<endl;

	for(int i = 1; i <= nS; i++)
	{
		cout <<"  "<< i << ": ";
		cin >> nameS;
		students.push_back(nameS);
	}

	cout << "Enter the number of teachers: "<< endl;
	cin >> nT ;

	cout << "Enter their names one by one, starting by the Regent: "<<endl;

	for(int i = 1; i <= nT; i++)
	{
		cout << "  "<< i <<": ";
		cin >> nameT;
		teachers.push_back(nameT);
	}

	Uc newUC(name, teachers, students, year, ects, workload);
	vecUC.push_back(newUC);
}

void Course::removeUC()
{
	string name;

	cout << "Enter the name of the UC to remove: "<< endl;
	cin >> name; //input validation

	for(unsigned int i = 0; i <= vecUC.size(); i++)
	{
		if(vecUC.at(i).getName() == name)
		{
			vecUC.erase(vecUC.begin() + i);
			cout << "Course " << name << " has been successfully removed. "<< endl;
			return;
		}
	}

	throw NoNameFound(name);
}

void Course::showSyllabus()
{
	sortUc();

		for(unsigned int i=0; i<vecUC.size();i++)
		{
			if(i==0)
			{
				cout<<"First year Modules: "<<endl<<endl;
			}

			if(vecUC.at(i).getYear() == 1)
			{
				cout<<vecUC.at(i).getName()<<endl;
			}

			if(vecUC.at(i-1).getYear() == 1 && vecUC.at(i).getYear()==2)
			{
				cout<<"Second year Modules"<<endl<<endl;
			}

			if(vecUC.at(i).getYear()== 2)
			{
				cout<<vecUC.at(i).getName()<<endl;
			}

			if(vecUC.at(i-1).getYear()== 2 && vecUC.at(i).getYear() == 3)
			{
				if(csType == "M")
				{
					return;
				}
				cout<<"Third year Modules"<<endl<<endl;
			}
			if(vecUC.at(i).getYear() == 3)
			{
				cout<<vecUC.at(i).getName()<<endl;
			}

			if(vecUC.at(i-1).getYear()== 3 && vecUC.at(i).getYear() == 4)
			{
				if(csType == "L")
				{
					return;
				}
				cout<<"Fourth year Modules"<<endl<<endl;
			}

			if(vecUC.at(i).getYear() == 4)
			{
				cout<<vecUC.at(i).getName()<<endl;
			}

			if(vecUC.at(i-1).getYear()== 4 && vecUC.at(i).getYear() == 5)
			{
				cout<<"Fourth year Modules"<<endl<<endl;
			}

			if(vecUC.at(i).getYear() == 5)
			{
				cout<<vecUC.at(i).getName()<<endl;
			}

		}

}

//UC//
//////////////////////
Uc::Uc(string name, vector<string> teacher, vector<string> student, int year, int ects, int workload)
{
	ucECTS = ects;
	ucName = name;
	ucStudent = student;
	ucTeacher = teacher;
	ucWorkload = workload;
	ucYear = year;
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

vector<string> Uc::getTeachers()
{
	return ucTeacher;
}

vector<string> Uc::getStudents()
{
	return ucStudent;
}

void Uc::addTeacher()
{
	string name;

	cout << "Enter the name of the Teacher: "<< endl;
	cin >> name;

	string newTeacher = name; //temporary while no teacher class is available
	ucTeacher.push_back(newTeacher);
}

void Uc::removeTeacher()
{
	string name;

	cout << "Enter the name of the Teacher to remove: "<< endl;
	cin >> name; //input validation

	if(remove(ucTeacher,name))
	{
		cout << "Teacher " << name << " has been successfully removed. "<< endl;
		return;
	}

	throw NoNameFound(name);
}

void Uc::addStudent()
{
	string name;

	cout << "Enter the name of the Student: "<< endl;
	cin >> name;

	string newStudent = name; //temporary while no student class is available
	ucStudent.push_back(newStudent);
}

void Uc::removeStudent()
{
	string name;

	cout << "Enter the name of the Student to remove: "<< endl;
	cin >> name; //input validation

	if(remove(ucStudent, name))
	{
		cout <<"Student"<< name << " has been successfully removed. "<< endl;
		return;
	}

	throw NoNameFound(name);
}

//Compare Ucs
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

void Course::sortUc()
{
	for(unsigned int j= vecUC.size() -1; j>0; j--)
	{
		bool troca = false;
		for(unsigned int i=0; i<j; i++)
		{
			if(vecUC.at(i+1).getYear() < vecUC.at(i).getYear())
			{
				swap(vecUC.at(i), vecUC.at(i+1));
				troca = true;
			}

			if(vecUC.at(i+1).getYear() < vecUC.at(i).getYear())
			{
				if(vecUC.at(i+1).getName() < vecUC.at(i).getName())
				{
					swap(vecUC.at(i), vecUC.at(i+1));
					troca = true;
				}
			}
		}

		if (!troca) return;
	}
}
