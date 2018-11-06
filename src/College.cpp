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

string College::getName()
{
	return colName;
}

void College::setName(string name)
{
	colName = name;
}

void College::setAdmin(string admin)
{
		this->admin = admin;
}

vector<Department*> College::getDepartments()
{
    return vecDep;
}

vector<vector<People*>> College::getPeople()
{
    return people;
}

void College::addPeople(int i, People* person)
{
    people.at(i).push_back(person);
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

	cout << "Enter the name of the director of the Department (! to skip): "<< endl;  //NEEDS TO TEST IF DIRECTOR_NAME BELONGS TO AN EXISTING TEACHER
	getline(cin, directorName);

	Teacher* director;

	if (directorName != "!")
	{

		while(!hasNoNumber(directorName))
		{
			cout << "Invalid name, try again: "<< endl;
			getline(cin, name);
		}

    	int i = 0;  //This is just so that the code can compile

    	if(people.at(0).at(i)->getName() == directorName){
    	director = dynamic_cast<Teacher*>(people.at(0).at(i)); //dynamic cast testa e transforma o apontador de people num apontador de teacher
    	}
	}

	cout << "Enter the code of the Department: "<< endl;  //NEEDS TO TEST IF IT'S DIFFERENT FROM OTHER DEP CODES

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

	//falta fazer validation do code!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! (mas estou à espera de saber se é para manter assim ou fazer random)

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

	for(unsigned int i = 0; i <= vecDep.size(); i++)
	{
		if(vecDep.at(i)->getCode() == code)
		{
			name = vecDep.at(i)->getName();

			vecDep.erase(vecDep.begin() + i);
			cout << "Department " << code << "(" << name << ")" << " has been successfully removed. "<< endl;
			return;
		}
	}

	throw NoCodeFound(code);
}

void College::addStudent(string name, string address, unsigned int phone, string cod, date& birthday){
    Course* course;
    int year;
    float grade;
    map<Uc*,float> subjects;
    string uc_name;
    cod = "0" + to_string(current_year) + to_string(Student::student_count);  //student id is assigned

    cout << "\nChoose Student's Course:" << endl;  //Needs exception in case there are no Courses Created
    Print_Vec(getCourses());
    course = getCourses().at(Nav(0,getCourses().size()-1));

    cout << "\nInsert Student's Year: " << flush;
    cin >> year;
    while(cin.fail() || year > 5 || year < 0)
    {
   		cout << "Invalid year, try again: "<< endl;
  		cin.clear();
  		cin.ignore(100, '\n');
  		cin >> year;
   	}

    Student* st = new Student(name, address, birthday, phone, cod, course, subjects);

    while(1){
        cout << "\nInsert Student's UC(? - list/ ! - done): " << flush;
        getline(cin, uc_name);
        while(!hasNoNumber(name))
        {
           	cout<<"Invalid name, try again"<<endl;
           	getline(cin, uc_name);
        }

        if(uc_name == "!") break;

        else if(uc_name == "?") Print_Vec(course->getUCs());
        cout << "\nInsert Student's Uc grade(-1 if not-evaluated): " << flush;
        cin >> grade;
        while(cin.fail() || grade > 20 || grade < -1)
        {
           	cout << "Invalid grade, try again: "<< endl;
           	cin.clear();
           	cin.ignore(100, '\n');
          	cin >> grade;
        }
        st->addUCGrade(uc_name, grade);
    }
    addPeople(0, st);
}

void College::addPerson(int type){ //Needs general function to check input
    string name, address;
    unsigned int phone;
    string cod;
    date* birthday;
    if(type == -1){
        cout << "What Type of person would you like to add?" << endl;
        cout << "0:   STUDENT" << endl;
        cout << "1:   TEACHER" << endl;
        cout << "2:   STAFF" << endl;
        cout << "3:   CANCEL" << endl;
        type = Nav(0,3);
    }
    if(type == 3) return;

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

    //cin.clear();
    // cin.ignore();
    birthday = readDate(); //Tests if date is written correctly
    switch(type){
        case 0:
            addStudent(name, address, phone, cod, *birthday);
            break;
        case 1:
            addTeacher(name, address, phone, cod, *birthday);
            break;
        case 2:
            addStaff(name, address, phone, cod, *birthday);
            break;
    }
}

void College::addTeacher(string name, string address, unsigned int phone, string cod, date& birthday){

}

void College::addStaff(string name, string address, unsigned int phone, string cod, date& birthday){

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
	Teacher* T;
	depDirector = T;
	depName = name;
	depCode = code;
	depAddress = address;
	depPhone = phone;
}

void Department::showInfo() {
    cout << "\n-----------------------------------------" << endl;
    cout << "|      " << depName << "      " << endl;
    cout << "| Address: " << depAddress << endl;
    cout << "| Code: " << depCode << " Phone: " << depPhone << endl;
    cout << "| Dep. Director: " << depDirector->getName() << endl;
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
	cin >> ptName;
	while(!hasNoNumber(ptName))
	{
		cout << "Invalid name, try again"<<endl;
	    cin >> ptName;
	}

	cout << "Enter the name of the course in English: " << endl;
	cin >> engName;
	while(!hasNoNumber(engName))
	{
		cout << "Invalid name, try again: " << endl;
		cin >> engName;
	}

	cout << "What type of course is it? (MI,M,L) "<< endl;
	cin >> type;
	while(!hasNoNumber(ptName) || (type != "MI" && type != "M" && type != "L"))
	{
		cout << "Invalid type, try again" << endl;
		cin >> ptName;
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

void Course::showInfo() {
    cout << "|\n-----------------------------------------" << endl;
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

		if(vecUC.at(i-1)->getYear() == 1 && vecUC.at(i)->getYear() == 2)
		{
			cout << "Second year Modules:" << endl << endl;
		}

		if(vecUC.at(i)->getYear() == 2)
		{
			cout << vecUC.at(i)->getName() << endl;
		}

		if(vecUC.at(i-1)->getYear() == 2 && vecUC.at(i)->getYear() == 3)
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

		if(vecUC.at(i-1)->getYear() == 3 && vecUC.at(i)->getYear() == 4)
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

		if(vecUC.at(i-1)->getYear() == 4 && vecUC.at(i)->getYear() == 5)
		{
			cout << "Fourth year Modules:" << endl << endl;
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
		cout << "Invalid year, try again: "<< endl;
		cin.clear();
		cin.ignore(100, '\n');
		cin >> workload;
	}

//	cout << "Enter the number of students: "<< endl;
//	cin >> nS ;
//
//	cout << "Enter their names one by one: "<<endl;
//
//	for(int i = 1; i <= nS; i++)
//	{
//		cout <<"  "<< i << ": ";
//		cin >> nameS;
//		students.push_back(nameS);
//	}
//
//	cout << "Enter the number of teachers: "<< endl;
//	cin >> nT ;
//
//	cout << "Enter their names one by one, starting by the Regent: "<<endl;
//
//	for(int i = 1; i <= nT; i++)
//	{
//		cout << "  "<< i <<": ";
//		cin >> nameT;
//		teachers.push_back(nameT);
//	}

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

void Uc::showInfo() {
    cout << "|\n-----------------------------------------" << endl;
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

//void Uc::addTeacher()
//{
//	string name;
//
//	cout << "Enter the name of the Teacher: "<< endl;
//	cin >> name;
//
//	string newTeacher = name; //temporary while no teacher class is available
//	ucTeacher.push_back(newTeacher);
//}

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
