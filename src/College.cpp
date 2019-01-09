	/*
 * College.cpp
 *
 *  Created on: 15/10/2018
 */

#include "College.h"

using namespace std;


//INPUT VALIDATION//
/**
 * @brief Checks if the string inputed has a number when it is not supposed to
 * @param s String to be analyzed
 * @return Holds true if the string is correct
 */
bool hasNoNumber(string s)
{
    return(s.find_first_of("0123456789") == string::npos);
}


//COLLEGE//
//////////////////////
College::College(string name) : studentsTree(Student_Ptr(nullptr))
{
	colName = name;
}


College::College(): studentsTree(Student_Ptr(nullptr)) {}

string College::getName() const
{
	return colName;
}

College::~College()
{
	dest_remove(teachers);
	dest_remove(staff);
	dest_remove(vecDep);
}

void College::Add_To_Queue(Student* st)
{
    students_queue.push(st);
}

void College::Rearrange_Queue(Student* st)
{
    vector<Student*> tmp;
    for(size_t i = 0; i < students_queue.size(); i++)
    {
        tmp.push_back(students_queue.top());
        if(students_queue.top() == st)
        {
            students_queue.pop();
            break;
        }
        else students_queue.pop();
    }

    for(size_t i = 0; i < tmp.size(); i++)
    {
        students_queue.push(tmp[i]);
    }
}

void College::Remove_From_Queue(Student* st){
    vector<Student*> tmp;
    for(size_t i = 0; i < students_queue.size(); i++)
    {
        if(students_queue.top() == st)
        {
            students_queue.pop();
            break;
        }
        else{
            tmp.push_back(students_queue.top());
            students_queue.pop();
        }
    }

    for(size_t i = 0; i < tmp.size(); i++)
    {
        students_queue.push(tmp[i]);
    }
}

vector<EmployeePtr> College::getEmployees() const
{
	vector<EmployeePtr> ptrs;
	HashTabEmployeetPtr::const_iterator it1 = this->employeeTable.begin();
	HashTabEmployeetPtr::const_iterator it2 = this->employeeTable.end();

	for(; it1 != it2; it1++)
	{
		ptrs.push_back(*it1);
	}

	return ptrs;
}


void College::addEmployeeTable(Teacher* teacher)
{
	employeeTable.insert(teacher);
}

void College::addEmployeeTable(Staff* staff)
{
	employeeTable.insert(staff);
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

vector<Department*>& College::getDepartments()
{
    return vecDep;
}

vector<Teacher *>& College::getTeachers()
{
    return teachers;
}

vector<Student *>& College::getStudents()
{
    return readst;
}

vector<Staff *>& College::getStaff()
{
    return staff;
}

void College::addTeacher(Teacher *teacher)
{
	addEmployeeTable(teacher);
    teachers.push_back(teacher);
}

void College::addStaff(Staff *staff)
{
	addEmployeeTable(staff);
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
        vec.insert(vec.end(), course_ucs.begin(), course_ucs.end());
		//vec.push_back(cr.at(i)->getUCs());
    }
    return vec;
}


Student* College::Get_Top_Student(){
    if(students_queue.empty()){
        cout << "\n!THERE ARE NO STUDENTS!" << endl;
        return nullptr;
    }
    return students_queue.top();
}

void College::removeTeacher(Teacher* teacher){

   for(unsigned int i = 0; i<teachers.size(); i++)
   {
	   if(teachers.at(i) == teacher)
	   {
		   for (unsigned int j = 0; j < getEmployees().size(); j++)
		   {
			   if (getEmployees().at(j).getCode() == teacher->getCode())
				   getEmployees().at(j).setWorkingState(false);
		   }

		   deleteTeachers(teacher->getName());
		   
		   teachers.erase(teachers.begin() + i);
	   }
   }
}

void College::deleteTeachers(string name)
{
	for (unsigned int i = 0; i < getCourses().size(); i++)
	{
		if (getCourses().at(i)->getDirector() != nullptr)
		{
			if (getCourses().at(i)->getDirector()->getName() == name)
			{
				getCourses().at(i)->setDirector(nullptr);
			}
		}

		for (unsigned int j = 0; j < getCourses().at(i)->getUCs().size(); j++)
		{
			remove(getCourses().at(i)->getUCs().at(j)->getTeachers(), name);
		}
	}

	for (unsigned int i = 0; i < getDepartments().size(); i++)
	{
		if (getDepartments().at(i)->getDirector() != nullptr)
		{
			if (getDepartments().at(i)->getDirector()->getName() == name)
			{
				getDepartments().at(i)->setDirector(nullptr);
			}
		}
	}
}

void College::removeStaff(Staff* staffx){

	for(unsigned int i=0; i<staff.size(); i++)
	{
		for (unsigned int j = 0; j < getEmployees().size(); j++)
		{
			if (getEmployees().at(j).getCode() == staffx->getCode())
				getEmployees().at(j).setWorkingState(false);
		}

		if(staff.at(i) == staffx)
		{
		   //delete staff.at(i);
		   staff.erase(staff.begin() + i);
		}
	}
}

void College::addDepartment()
{
	string name, address, directorName;
	int code, phone;
	bool differentX = true;

	cout << "Enter the name of the Department: "<< endl;

	do{
        getline(cin, name);

        while(!hasNoNumber(name))
        {
            cout << "Invalid name, try again: "<< endl;
            getline(cin, name);
        }

        for(unsigned int i = 0; i < vecDep.size(); i++)
        {
            if(vecDep.at(i)->getName() == name)
            {
                cout << "The name you entered is already associated to Department '" << vecDep.at(i)->getName() << "'!" << endl;
                cout << "Enter a new one: " << endl;
                differentX = false;
                break;
            }
            else
            {
                differentX = true;
            }
        }
	} while (!differentX);

	cout << "Enter the address of the Department: "<< endl;
	getline(cin, address);

	Teacher* director = new Teacher ();

    while(1){
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

	cout << "Enter the code of the Department(4 digits): "<< endl;

	do{
			cin >> code;

			while(cin.fail() || to_string(code).length() != 4)
			{
				cout << "Invalid code number, try again: " << endl;
				cin.clear();
				cin.ignore(100, '\n');
				cin >> code;
			}

			for(unsigned int i = 0; i < vecDep.size(); i++)
			{
				if(vecDep.at(i)->getCode() == code)
				{
					cout << "The code you entered is already associated to Department " << "'" << vecDep.at(i)->getName() << "'!" << endl;
					cout << "Enter a new one: " << endl;
					differentX = false;
					break;
				}
				else
				{
					differentX = true;
				}
			}
        if(vecDep.empty()) differentX = true;
	} while (!differentX);

	cout << "Enter the phone of the Department (9-digit): "<< endl;

	do{
			cin >> phone;

			while(cin.fail() || to_string(phone).size() != 9)
			{
				cout << "Invalid phone number, try again: " << endl;
				cin.clear();
				cin.ignore(100, '\n');
				cin >> phone;
			}

			for(unsigned int i = 0; i < vecDep.size(); i++)
			{
				if(vecDep.at(i)->getPhone() == phone)
				{
					cout << "The phone number you entered is already associated to Department " << "'" << vecDep.at(i)->getName() << "'!" << endl;
					cout << "Enter a new one: " << endl;
					differentX = false;
					break;
				}
				else
				{
					differentX = true;
				}
			}
        if(vecDep.empty()) differentX = true;
	} while (!differentX);

	Department* dp = new Department ();

	if (directorName != "!")
	{
        dp = new Department(name, code, address, phone, director);
        director->UpdateCat(DepDir);
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

void College::addCourse(College &college){
    cout << "In Which Department do you want to add a course?" << endl;
    Print_Vec(vecDep);
    cout << vecDep.size() << ":   PREVIOUS MENU" << endl;
    unsigned int i = Nav(0,vecDep.size());
    if(i == vecDep.size()) return;
    else vecDep.at(i)->addCourse(*this);
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

BST<Student_Ptr> College::getStudentsTree() {
	return this->studentsTree;
}

void College::showStudents()
{
	BSTItrIn<Student_Ptr> it(studentsTree);
	int i = 0;
	while (!it.isAtEnd())
	{
		cout << i << ":   " << it.retrieve().getST()->getName() << endl;
		i++;
		it.advance();
	}
}

int College::sizeBST()
{
	BSTItrIn<Student_Ptr> it(studentsTree);
	int i = 0;
	while (!it.isAtEnd())
	{
		i++;
		it.advance();
	}
	return i;
}

void College::addNewStudent(Student* st1)
{
    Student_Ptr st(st1);
	studentsTree.insert(st);
    Add_To_Queue(st1);
}

void College::removeStudentBST(Student* st1)
{
	BSTItrIn<Student_Ptr> it(studentsTree);

	while (!it.isAtEnd())
	{
		if (st1->getCode() == it.retrieve().getST()->getCode())
		{
			studentsTree.remove(it.retrieve());
            Remove_From_Queue(st1);
            delete st1;
			return;
		}
		it.advance();
	}

	throw NoCodeFound(stoi(st1->getCode()));
}


Student* College::SearchBST(string name)
{
	BSTItrIn<Student_Ptr> it(studentsTree);
	while (!it.isAtEnd())
	{
		if (name == it.retrieve().getST()->getName())
		{

			return it.retrieve().getST();
		}
		it.advance();
	}
	throw NoNameFound(name);
}

void College::setNameBST(string cod, string name)
{
	BSTItrIn<Student_Ptr> it(studentsTree);
	Student* s1;
	while (!it.isAtEnd())
	{
		if (cod == it.retrieve().getST()->getCode())
		{
			s1 = it.retrieve().getST();
			studentsTree.remove(it.retrieve());
			s1->setName(name);
			studentsTree.insert(s1);
			break;
		}
		it.advance();
	}
}

void College::setCourse(string cod, Course* cs)
{

	BSTItrIn<Student_Ptr> it(studentsTree);
	Student* s1;
	while (!it.isAtEnd())
	{
		if (cod == it.retrieve().getST()->getCode())
		{
			s1 = it.retrieve().getST();
			studentsTree.remove(it.retrieve());
			s1->setCourse(cs);
			studentsTree.insert(s1);
			break;
		}
		it.advance();
	}
}

vector<Student*> College::BSTtoVEC()
{
	vector<Student*> vec;

	BSTItrIn<Student_Ptr> it(studentsTree);
	while (!it.isAtEnd())
	{
		vec.push_back(it.retrieve().getST());
		it.advance();
	}

	return vec;
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

void Department::editInfo(College &college){
    while (1) {
        showInfo();
        cout << "Which parameter do you want to edit?" << endl;
        cout << "0:   NAME" << endl;
        cout << "1:   ADDRESS" << endl;
        cout << "2:   CODE" << endl;
        cout << "3:   PHONE" << endl;
        cout << "4:   DIRECTOR" << endl;
        cout << "5:   PREVIOUS" << endl;
        string s;
		Teacher* director = new Teacher();
        int i;
        switch (Nav(0,5)) {
            case 0:
                cout << "Insert new name: " << flush;
                getline(cin,s);
                while (!hasNoNumber(s)) {
                    cout << "Invalid name, try again" << endl;
                    getline(cin,s);
                }
                setName(s);
                break;
            case 1:
                cout << "Insert new address: " << flush;
                getline(cin,s);
                setAddress(s);
                break;
            case 2:
                cout << "Insert new code(4 digits): " << flush;
                cin >> i;
                while (cin.fail() || to_string(i).length() != 4) {
                    cout << "Invalid code, try again: " << endl;
                    cin.clear();
                    cin.ignore(100, '\n');
                    cin >> i;
                }
                cin.clear();
                cin.ignore(100, '\n');
                depCode = i;
                break;
            case 3:
                cout << "Insert new phone number: " << flush;
                cin >> i;
                while (cin.fail() || to_string(i).size() != 9) {
                    cout << "Invalid phone number, try again: " << endl;
                    cin.clear();
                    cin.ignore(100, '\n');
                    cin >> i;
                }
                cin.clear();
                cin.ignore(100, '\n');
                setPhone(i);
                break;
            case 4:
                while(1){
                    cout << "Enter the name of the director of the Department (! - cancel/? for list): "<< endl;
                    getline(cin, s);
                    if(s == "!") break;
                    else if(s == "?") Print_Vec(college.getTeachers());
                    else{
                        try{
                            director = SearchVec(college.getTeachers(),s);
                        }
                        catch(NoNameFound &err){
                            cout << err.errorMessage() << endl;
                            cout << "Invalid name, try again: "<< flush;
                            continue;
                        }
                        break;
                    }
                }
                depDirector = director;
				depDirector->UpdateCat(DepDir);
                break;
            case 5:
                return;
        }
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
vector<Course*>& Department::getCourses()
{
	return vecCourse;
}

void Department::addCourse(College& college)
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

	cout << "Enter the code of the course(4 digits): "<< endl;
	cin >> code;
	while(cin.fail() || to_string(code).length() != 4)
	{
	     cout << "Invalid code, try again: " << endl;
	     cin.clear();
	     cin.ignore(100, '\n');
	     cin >> code;
	}
    cin.clear();
    cin.ignore(100, '\n');

    string directorName;
    Teacher *director = nullptr;
    while(1){
        cout << "Enter the name of the Course Director (! to skip/ ? for list): "<< endl;
        getline(cin, directorName);
        if (directorName == "!") break;
        else if(directorName == "?") Print_Vec(college.getTeachers());
        else{
            try{
                director = SearchVec(college.getTeachers(),directorName);
            }
            catch(NoNameFound &err){
                cout << err.errorMessage() << endl;
                cout << "Invalid name, try again: "<< flush;
                continue;
            }
            break;
        }
    }

	Course* newCourse = new Course(type, engName, ptName, code, director);
    if(director != nullptr) director->UpdateCat(CourseDir);
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
    string dir;
    if(dep.depDirector == nullptr) dir = "!";
    else dir = dep.depDirector->getName();
    os << dep.depName << "|" << dep.depAddress << "|" << dep.depCode << "|" << dep.depPhone << "|" << dir << "|" << endl;
    for(size_t i = 0; i < dep.vecCourse.size(); i++){
        os << "COURSE:" << endl;
        os << *dep.vecCourse.at(i);
    }
    return os;
}

//COURSE//
//////////////////////
Course::Course(string type, string engName, string ptName, int code, Teacher *director)
{
	csCode = code;
	csType = type;
	csEngName = engName;
	csPtName = ptName;
    courseDirector = director;
}

Course::~Course()
{
	dest_remove(vecUC);
}
void Course::showInfo() {
    string dir_name;
    if(courseDirector == nullptr) dir_name = "!Unassigned!";
    else dir_name = courseDirector->getName();
    cout << "\n|-----------------------------------------" << endl;
    cout << "| Name: " << csEngName << endl;
    cout << "| Nome: " << csPtName << endl;
    cout << "| Type: " << csType << "  Code: " << csCode << endl;
    cout << "| Director: " << dir_name << endl;
    cout << "|-----------------------------------------" << endl;
}

void Course::editInfo(College& college){
    while(1) {
        showInfo();
        cout << "Which parameter do you want to edit?" << endl;
        cout << "0:   Pt_NAME" << endl;
        cout << "1:   Eng_NAME" << endl;
        cout << "2:   TYPE" << endl;
        cout << "3:   CODE" << endl;
        cout << "4:   DIRECTOR" << endl;
        cout << "5:   PREVIOUS MENU" << endl;
        string s;
        int i;
        Teacher *director = nullptr;
        switch (Nav(0, 5)) {
            case 0:
                cout << "\nInsert New Pt_name: " << flush;
                getline(cin, s);
                while (!hasNoNumber(s)) {
                    cout << "Invalid name, try again: " << endl;
                    getline(cin, s);
                }
                setPtName(s);
                break;
            case 1:
                cout << "Insert new Eng_Name: " << endl;
                getline(cin, s);
                while (!hasNoNumber(s)) {
                    cout << "Invalid name, try again: " << endl;
                    getline(cin, s);
                }
                csEngName = s;
                break;
            case 2:
                cout << "What type of course is it? (MI,M,L) " << endl;
                cin >> s;
                while (!hasNoNumber(s) || (s != "MI" && s != "M" && s != "L")) {
                    cout << "Invalid type, try again" << endl;
                    cin >> s;
                }
                csType = s;
                break;
            case 3:
                cout << "Enter new Course code: "<< endl;
                cin >> i;
                while(cin.fail())
                {
                    cout << "Invalid code, try again: " << endl;
                    cin.clear();
                    cin.ignore(100, '\n');
                    cin >> i;
                }
                cin.clear();
                cin.ignore(100, '\n');
                csCode = i;
                break;
            case 4:
                while(1){
                    cout << "Enter the name of the new Course Director (! - cancel/? for list): "<< endl;
                    getline(cin, s);
                    if(s == "!") break;
                    else if(s == "?") Print_Vec(college.getTeachers());
                    else{
                        try{
                            director = SearchVec(college.getTeachers(),s);
                        }
                        catch(NoNameFound &err){
                            cout << err.errorMessage() << endl;
                            cout << "Invalid name, try again: "<< flush;
                            continue;
                        }
                        break;
                    }
                }
                courseDirector = director;
				courseDirector->UpdateCat(CourseDir);
                break;
            case 5:
                return;
        }
    }
}

unsigned int Course::showSyllabus()
{
    if(vecUC.empty()) return 0;
	sortUc();
    bool first= false, second = false, third = false, fourth = false , fifth = false;
    for(unsigned int i = 0; i < vecUC.size(); i++){
        if(!first && vecUC.at(i)->getYear() == 1)
        {
            cout << "\nFirst year Modules: " << endl << endl;
            first = true;
        }
        else if(!second && vecUC.at(i)->getYear() == 2)
        {
            cout << "\nSecond year Modules: " << endl << endl;
            second = true;
        }
        else if(!third && vecUC.at(i)->getYear() == 3)
        {
            cout << "\nThird year Modules: " << endl << endl;
            third = true;
        }
        else if(!fourth && vecUC.at(i)->getYear() == 4)
        {
            cout << "\nFourth year Modules: " << endl << endl;
            fourth = true;
        }
        else if(!fifth && vecUC.at(i)->getYear() == 5)
        {
            cout << "\nFifth year Modules: " << endl << endl;
            fifth = true;
        }
        cout << i << ":   " << vecUC.at(i)->getName() << endl;
    }
    return vecUC.size();
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

vector<Uc*>& Course::getUCs()
{
	return vecUC;
}

void Course::addUC(College &college)
{
	string name, nameT, nameS;
	int year, ects, workload;// nS, nT;
	vector<string> teachers, students;

	cout << "Enter the name of the Curricular Unit: "<< endl;
	getline(cin,name);
	while(!hasNoNumber(name))
	{
		cout << "Invalid name, try again:" << endl;
		getline(cin,name);
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
    cin.clear();
    cin.ignore(100, '\n');

	cout << "How many ETCS does it have? "<< endl;
	cin >> ects;
	while(cin.fail() || ects > 10 || ects < 0)
	{
		cout << "Invalid number of etcs, try again: "<< endl;
		cin.clear();
		cin.ignore(100, '\n');
		cin >> ects;
	}
    cin.clear();
    cin.ignore(100, '\n');

	cout << "How many hours of workload? "<< endl;
	cin >> workload;
	while(cin.fail() || workload > 10 || workload < 0)
	{
		cout << "Invalid number of hours, try again: "<< endl;
		cin.clear();
		cin.ignore(100, '\n');
		cin >> workload;
	}
    cin.clear();
    cin.ignore(100, '\n');

    string directorName;
    Teacher *director = nullptr;
    while(1){
        cout << "Enter the name of the Uc Regent (! to skip/ ? for list): "<< endl;
        getline(cin, directorName);
        if (directorName == "!") break;
        else if(directorName == "?") Print_Vec(college.getTeachers());
        else{
            try{
                director = SearchVec(college.getTeachers(),directorName);
            }
            catch(NoNameFound &err){
                cout << err.errorMessage() << endl;
                cout << "Invalid name, try again: "<< flush;
                continue;
            }
            break;
        }
    }

	Uc* newUC = new Uc(name, year, ects, workload, director);
    if(director != nullptr) director->UpdateCat(Reg);
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

	for(unsigned int i = 0; i < vecUC.size(); i++)
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
    string dir;
    if(course.courseDirector == nullptr) dir = "!";
    else dir = course.courseDirector->getName();
    os << course.csPtName << "|" << course.csEngName << "|" << course.csCode << "|" << course.csType << "|" << dir << "|" << endl;
    for(size_t i = 0; i < course.vecUC.size(); i++){
        if(i == 0) os << "UC:" << endl;
        os << *course.vecUC.at(i);
    }
    return os;
}


//UC//
//////////////////////
Uc::Uc(string name, vector<Teacher*> teacher, vector<Student*> student, int year, int ects, int workload, Teacher* director)
{
	ucECTS = ects;
	ucName = name;
	ucStudent = student;
	ucTeacher = teacher;
	ucWorkload = workload;
	ucYear = year;
    Regent = director;
}

Uc::Uc(string name, int year, int ects, int workload, Teacher *director)
{
	ucECTS = ects;
	ucName = name;
	ucWorkload = workload;
	ucYear = year;
    Regent = director;
}

Uc::~Uc()
{}

void Uc::showInfo() {
    string regent;
    if(Regent == nullptr) regent = "!Unassigned!";
    else regent = Regent->getName();
    cout << "\n|-----------------------------------------" << endl;
    cout << "| Name: " << ucName << endl;
    cout << "| Year: " << ucYear << endl;
    cout << "| ECTS: " << ucECTS << endl;
    cout << "| Workload: " << ucWorkload << endl;
    cout << "| Regent: " << regent << endl;
    cout << "|-----------------------------------------" << endl;
}

void Uc::editInfo(College &college){
    while(1){
        showInfo();
        cout << "0:   NAME" << endl;
        cout << "1:   YEAR" << endl;
        cout << "2:   ECTS" << endl;
        cout << "3:   WORKLOAD" << endl;
        cout << "4:   REGENT" << endl;
        cout << "5:   PREVIOUS" << endl;
        string directorName;
        switch(Nav(0,5)){
            case 0:
                cout << "Insert new Curricular Unit's name: "<< flush;
                getline(cin,ucName);
                while(!hasNoNumber(ucName))
                {
                    cout << "Invalid name, try again:" << endl;
                    getline(cin,ucName);
                }
                break;
            case 1:
                cout << "Insert new Uc year: " << flush;
                cin >> ucYear;
                while(cin.fail() || ucYear > 5 || ucYear < 1)
                {
                    cout << "Invalid year, try again: "<< endl;
                    cin.clear();
                    cin.ignore(100, '\n');
                    cin >> ucYear;
                }
                cin.clear();
                cin.ignore(100, '\n');
                break;
            case 2:
                cout << "Insert new Uc ECTs: " << flush;
                cin >> ucECTS;
                while(cin.fail() || ucECTS > 10 || ucECTS < 0)
                {
                    cout << "Invalid number of etcs, try again: "<< endl;
                    cin.clear();
                    cin.ignore(100, '\n');
                    cin >> ucECTS;
                }
                cin.clear();
                cin.ignore(100, '\n');
                break;
            case 3:
                cout << "Insert new Uc workload: " << flush;
                cin >> ucWorkload;
                while(cin.fail() || ucWorkload > 10 || ucWorkload < 0)
                {
                    cout << "Invalid number of hours, try again: "<< endl;
                    cin.clear();
                    cin.ignore(100, '\n');
                    cin >> ucWorkload;
                }
                cin.clear();
                cin.ignore(100, '\n');
                break;
            case 4:
                while(1){
                    cout << "Enter the name of the Uc Regent (! to skip/ ? for list): "<< endl;
                    getline(cin, directorName);
                    if (directorName == "!") break;
                    else if(directorName == "?") Print_Vec(college.getTeachers());
                    else{
                        try{
                            Regent = SearchVec(college.getTeachers(),directorName);
                        }
                        catch(NoNameFound &err){
                            cout << err.errorMessage() << endl;
                            cout << "Invalid name, try again: "<< flush;
                            continue;
                        }
						Regent->UpdateCat(Reg);
                        break;
                    }
                }
                break;
            case 5:
                return;
        }
    }
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

vector<Teacher*>& Uc::getTeachers()
{
	return ucTeacher;
}

vector<Student*>& Uc::getStudents()
{
	return ucStudent;
}

void Uc::addStudent(Student* student){
    ucStudent.push_back(student);
}

void Uc::addTeacher(Teacher* teacher){
    ucTeacher.push_back(teacher);
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

    //Teacher* t = SearchVec(ucTeacher, name);

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

ostream& operator<< (ostream& os, Uc &uc){
    string reg;
    if(uc.Regent == nullptr) reg = "!";
    else reg = uc.Regent->getName();
    os << uc.ucName << "|" << uc.ucYear << "|" << uc.ucECTS << "|" << uc.ucWorkload << "|" << reg << "|";
    Uc* pointer = &uc;
    for(size_t i = 0; i < uc.ucStudent.size(); i++){
        map <Uc*, float> subjects = *uc.ucStudent.at(i)->getGrades();
        os << "[" << uc.ucStudent.at(i)->getName() << "," << subjects[pointer] << "]";
    }
    os << "|";
    for(size_t i = 0; i < uc.ucTeacher.size(); i++){
        os << "[" << uc.ucTeacher.at(i)->getName() << "]";
    }
    os << "|" << endl;
    return os;
}
