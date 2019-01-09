//============================================================================
// Name        : Proj1.cpp
// Author      : Mafalda Santos, Diogo Silva, Alexandre Carqueja
// Version     :
// Copyright   : AEDA-2018
// Description : College Management
//============================================================================

#include <iostream>
#include "College.h"
#include <sstream>
#include <fstream>
#include <map>

using namespace std;


//VARIABLES
int access = 0; //Global variable to determine type of user
string user_id;
string college_file_name = "!";

////CURRENT YEAR//// (used for ids)
//time_t theTime = time(NULL);
//struct tm *aTime = localtime(&theTime);
//int current_year = aTime->tm_year + 1900; // Year is # years since 1900
int current_year = 2019;  //Visual studio gives off error in above functions, however CLion runs fine, thus they were commented

/// PROTOTYPES ///
date* changeDate(string data);
enum Cat CatEnum(string s);
void studentsCourses(College &c);


///READ FILE
void readFile(College &c, string file)
{
	ifstream fin;
	date* d;

	fin.open(file);
	while (!fin.is_open())
	{
		cerr << "Input file not found, try again!" << endl;
		cin >> file;
		fin.open(file);
	}

	string next; //line from the file

	while (!fin.eof())
	{
		getline(fin, next);

		if (next.length() == 0)
		{
			continue;
		}

		if (next == "COLLEGE:")
		{
			getline(fin, next);

			int i = next.find("|");

			c.setName(next.substr(0, i));
			next.erase(0, i + 1);

			c.setAdmin(next.substr(0, next.length()));
		}

		if (next == "STUDENTS:")
		{
			getline(fin, next);

			while (next.length() != 0)
			{
				Student* s = new Student();

				s->setName(next.substr(0, next.find("|")));
				next.erase(0, next.find("|") + 1);

				s->setAddress(next.substr(0, next.find("|")));
				next.erase(0, next.find("|") + 1);

				s->setPhone(stoi(next.substr(0, next.find("|"))));
				next.erase(0, next.find("|") + 1);

				s->setCode(next.substr(0, next.find("|")));
				next.erase(0, next.find("|") + 1);

				d = changeDate(next.substr(0, next.find("|")));
				s->setDate(d);
				next.erase(0, next.find("|") + 1);

				s->setCourseString(next.substr(0, next.find("|")));
				next.erase(0, next.find("|") + 1);

				s->setYear(stoi(next.substr(0, next.find("|"))));
                next.erase(0, next.find("|") + 1);

                s->setBolsa(stoi(next.substr(0, next.find("|"))));
				next.clear();

				c.getStudents().push_back(s);

                c.Add_To_Queue(s);

				getline(fin, next);
			}
		}

		if (next == "TEACHER:")
		{
			getline(fin, next);

			while (next.length() != 0)
			{
				Teacher* t = new Teacher();

				t->setName(next.substr(0, next.find("|")));
				next.erase(0, next.find("|") + 1);

				t->setAddress(next.substr(0, next.find("|")));
				next.erase(0, next.find("|") + 1);

				t->setPhone(stoi(next.substr(0, next.find("|"))));
				next.erase(0, next.find("|") + 1);

				t->setCode(next.substr(0, next.find("|")));
				next.erase(0, next.find("|") + 1);

				d = changeDate(next.substr(0, next.find("|")));
				t->setDate(d);
				next.erase(0, next.find("|") + 1);

				t->setSalary(stof(next.substr(0, next.find("|"))));
				next.erase(0, next.find("|") + 1);

				t->setNIF(stoi(next.substr(0, next.find("|"))));
				next.erase(0, next.find("|") + 1);

				t->setCategory(CatEnum(next.substr(0, next.find("|"))));
				next.erase(0, next.find("|") + 1);

				t->setWorking(1);
				c.getTeachers().push_back(t);
				c.addEmployeeTable(t);

				getline(fin, next);
			}
		}

		if (next == "STAFF:")
		{
			getline(fin, next);

			while (next.length() != 0)
			{
				Staff* sf = new Staff();

				sf->setName(next.substr(0, next.find("|")));
				next.erase(0, next.find("|") + 1);

				sf->setAddress(next.substr(0, next.find("|")));
				next.erase(0, next.find("|") + 1);

				sf->setPhone(stoi(next.substr(0, next.find("|"))));
				next.erase(0, next.find("|") + 1);

				sf->setCode(next.substr(0, next.find("|")));
				next.erase(0, next.find("|") + 1);

				d = changeDate(next.substr(0, next.find("|")));
				sf->setDate(d);
				next.erase(0, next.find("|") + 1);

				sf->setSalary(stof(next.substr(0, next.find("|"))));
				next.erase(0, next.find("|") + 1);

				sf->setNIF(stoi(next.substr(0, next.find("|"))));
				next.erase(0, next.find("|") + 1);

				sf->setWorkArea(next.substr(0, next.find("|")));
				next.erase(0, next.find("|") + 1);

				sf->setWorking(1);
				c.getStaff().push_back(sf);
				c.addEmployeeTable(sf);

				getline(fin, next);
			}
		}

		if (next == "DEP:")
		{
			getline(fin, next);

			Teacher* dir = new Teacher();
			Department* d = new Department();

			d->setName(next.substr(0, next.find("|")));
			next.erase(0, next.find("|") + 1);

			d->setAddress(next.substr(0, next.find("|")));
			next.erase(0, next.find("|") + 1);

			d->setCode(stoi(next.substr(0, next.find("|"))));
			next.erase(0, next.find("|") + 1);

			d->setPhone(stoi(next.substr(0, next.find("|"))));
			next.erase(0, next.find("|") + 1);

			if ((next.substr(0, next.find("|"))) != "!")
			{
				try
				{
					dir = SearchVec(c.getTeachers(), (next.substr(0, next.find("|"))));
				}
				catch (NoNameFound &e) { cout << "Name not found!"; }

				d->setDirector(dir);
			}

			c.getDepartments().push_back(d);

			getline(fin, next);

			while (next.length() != 0)
			{
				if (next == "COURSE:")
				{
					Teacher* dirc = new Teacher();
					Course* cs = new Course();

					getline(fin, next);

					cs->setPtName(next.substr(0, next.find("|")));
					next.erase(0, next.find("|") + 1);

					cs->setEngName(next.substr(0, next.find("|")));
					next.erase(0, next.find("|") + 1);

					cs->setCode(stoi(next.substr(0, next.find("|"))));
					next.erase(0, next.find("|") + 1);

					cs->setType(next.substr(0, next.find("|")));
					next.erase(0, next.find("|") + 1);

					if ((next.substr(0, next.find("|"))) != "!")
					{
						try {
							dirc = SearchVec(c.getTeachers(), (next.substr(0, next.find("|"))));
						}
						catch (NoNameFound &e) { cout << "No name Found!"; }

						cs->setDirector(dirc);
					}

					d->getCourses().push_back(cs);
					getline(fin, next);


					if (next == "UC:")
					{
						getline(fin, next);
						while (1)
						{
							if (next == "COURSE:" || next.length() == 0)
							{
								break;
							}

							Teacher* regent = new Teacher();
							Uc* uc = new Uc();
							Student* student = new Student();
							Teacher* teacher = new Teacher();

							uc->setName(next.substr(0, next.find("|")));
							next.erase(0, next.find("|") + 1);

							uc->setYear(stoi(next.substr(0, next.find("|"))));
							next.erase(0, next.find("|") + 1);

							uc->setECTS(stoi(next.substr(0, next.find("|"))));
							next.erase(0, next.find("|") + 1);

							uc->setWorkload(stoi(next.substr(0, next.find("|"))));
							next.erase(0, next.find("|") + 1);

							if ((next.substr(0, next.find("|"))) != "!")
							{
								regent = SearchVec(c.getTeachers(), next.substr(0, next.find("|")));
								uc->getTeachers().push_back(regent);
							}
							next.erase(0, next.find("|") + 1);

							while (next.at(0) != '|')
							{
								string name = next.substr(1, next.find(",") - 1);
								student = SearchVec(c.getStudents(), name);
								uc->getStudents().push_back(student);

								for (unsigned int j = 0; j < c.getStudents().size(); j++)
								{
									if (c.getStudents().at(j)->getName() == name)
									{
										float grade = stof(next.substr(next.find(",") + 1, next.find("]")));
										c.getStudents().at(j)->addUCGrade(uc, grade);
                                        c.getStudents().at(j)->Calculate_Average();
                                        c.Rearrange_Queue(c.getStudents().at(j));
										break;
									}
								}

								next.erase(0, next.find("]") + 1);
							}

							next.erase(0, next.find("|") + 1);

							while (next.length() != 1)
							{
								string name = next.substr(1, next.find("]") - 1);
								teacher = SearchVec(c.getTeachers(), name );
								uc->getTeachers().push_back(teacher);

								for (unsigned int j = 0; j < c.getTeachers().size(); j++)
								{
									if (c.getTeachers().at(j)->getName() == name)
									{
										c.getTeachers().at(j)->getSubjects().push_back(uc);
										break;
									}
								}

								next.erase(0, next.find("]") + 1);
							}

							next.clear();

							cs->getUCs().push_back(uc);

							getline(fin, next);
						}
					}
				}
			}
		}

		if (next == "FORMER TEACHER:")
		{
			getline(fin, next);

			while (next.length() != 0)
				{
					Teacher* t = new Teacher();

					t->setName(next.substr(0, next.find("|")));
					next.erase(0, next.find("|") + 1);

					t->setAddress(next.substr(0, next.find("|")));
					next.erase(0, next.find("|") + 1);

					t->setPhone(stoi(next.substr(0, next.find("|"))));
					next.erase(0, next.find("|") + 1);

					t->setCode(next.substr(0, next.find("|")));
					next.erase(0, next.find("|") + 1);

					d = changeDate(next.substr(0, next.find("|")));
					t->setDate(d);
					next.erase(0, next.find("|") + 1);

					t->setSalary(stof(next.substr(0, next.find("|"))));
					next.erase(0, next.find("|") + 1);

					t->setNIF(stoi(next.substr(0, next.find("|"))));
					next.erase(0, next.find("|") + 1);

					t->setCategory(CatEnum(next.substr(0, next.find("|"))));
					next.erase(0, next.find("|") + 1);

					t->setWorking(0);
					c.addEmployeeTable(t);

					getline(fin, next);
				}
		}

		if (next == "FORMER STAFF:")
		{
			getline(fin, next);

			while (next.length() != 0)
				{
					Staff* sf = new Staff();

					sf->setName(next.substr(0, next.find("|")));
					next.erase(0, next.find("|") + 1);

					sf->setAddress(next.substr(0, next.find("|")));
					next.erase(0, next.find("|") + 1);

					sf->setPhone(stoi(next.substr(0, next.find("|"))));
					next.erase(0, next.find("|") + 1);

					sf->setCode(next.substr(0, next.find("|")));
					next.erase(0, next.find("|") + 1);

					d = changeDate(next.substr(0, next.find("|")));
					sf->setDate(d);
					next.erase(0, next.find("|") + 1);

					sf->setSalary(stof(next.substr(0, next.find("|"))));
					next.erase(0, next.find("|") + 1);

					sf->setNIF(stoi(next.substr(0, next.find("|"))));
					next.erase(0, next.find("|") + 1);

					sf->setWorkArea(next.substr(0, next.find("|")));
					next.erase(0, next.find("|") + 1);

					sf->setWorking(0);
					c.addEmployeeTable(sf);

					getline(fin, next);
				}
		}

		studentsCourses(c);
	}

	for (unsigned int i = 0; i < c.getStudents().size(); i++)
	{
		c.addNewStudent(c.getStudents().at(i));
	}

	cout << endl << "--------------" << endl;
	cout << "Load Finished!" << endl;
	cout << "--------------" << endl << endl;
}

void studentsCourses(College &c)
{

	for (unsigned int i = 0; i < c.getStudents().size(); i++)
	{
		for (unsigned int j = 0; j < c.getCourses().size(); j++)
		{
			if (c.getStudents().at(i)->getCourseString() == c.getCourses().at(j)->getName())
			{
				c.getStudents().at(i)->setCourse(c.getCourses().at(j));
			}
		}
	}
}


////GENERAL FUNCTIONS//// (used throughout project, mostly for input verification)
int Nav(int bottom, int top) { //tests for valid input keys and returns the inputed char
	int key;
	cin >> key;
	while (cin.fail() || key < bottom || key > top) { //Problem with cin getting corrupted if several characters are introduced
		cin.clear();
		cin.ignore(100, '\n');
		cout << "Invalid Input!" << endl;
		cin >> key;
	}
	cin.clear();
	cin.ignore(100, '\n');
	return key;
}

date* changeDate(string data)
{
	unsigned int day, month, year;
	char c = '/';

	stringstream ss(data);
	ss >> day >> c >> month >> c >> year;
	if (day < 0 || day > 31
		|| month < 0 || month > 12
		|| year < 1900 || year > 2018) {
		cout << "\nInvalid date!" << endl;
		return nullptr;
	}

	date *d = new date(day, month, year);
	return d;
}

date* readDate() {
	date* d;
	string data;
	while (1) {
		cout << "\nInsert Birthday(dd/mm/yyyy): " << flush;
		getline(cin, data);
		d = changeDate(data);
		if (d != nullptr) break;
	}

	return d;
}

enum Cat CatEnum(string s) {
	if (s == "Auxiliar Professor") return Aux;
	else if (s == "Regent") return Reg;
	else if (s == "Department Director") return DepDir;
	else if (s == "Course Director") return CourseDir;
	else return Default;
}

//////////////////////

int Main_Menu() {
	cout << "----------------------" << endl;
	cout << "|      MAIN MENU     |" << endl;
	cout << "----------------------" << endl;
	cout << "0:   CREATE COLLEGE" << endl;
	cout << "1:   LOAD COLLEGE" << endl;
	cout << "2:   EXIT" << endl;
	return Nav(0, 2);
}

//////////////////////

void New_College(College &college) {
    college_file_name = "!";
	string college_name, admin;
	cout << "Insert your College Name: " << flush;
	getline(cin, college_name);
	while (!hasNoNumber(college_name)) {
		cout << "Invalid college name! Try another: " << endl;
		getline(cin, college_name);
	}
	cout << endl << "Insert your Admin Code: " << flush;
	getline(cin, admin);
	college.setName(college_name);
	college.setAdmin(admin);
	cout << "\n\n\n" << endl;
}

//////////////////////

template<class T>
T* Search_Menu(vector<T*> vec) {
	string name;
	T* t;
	while (1) {
		cout << "Insert the name you want to search for(! to cancel): " << flush;
		getline(cin, name);
		if (name == "!") return nullptr;
		try {
			t = SearchVec(vec, name);
		}
		catch (NoNameFound &err) {
			cout << err.errorMessage() << endl;
			continue;
		}
		break;
	}
	return t;
}

Student* SearchStudent(College &c) {
	string name;
	Student* st;
	while (1) {
		cout << "Insert the name you want to search for(! to cancel): " << flush;
		getline(cin, name);
		if (name == "!") return nullptr;
		try {
			st = c.SearchBST(name);
		}
		catch (NoNameFound &err) {
			cout << err.errorMessage() << endl;
			continue;
		}
		break;
	}
	return st;
}
void List_Teachers(vector<Teacher*> teachers, College &college);
void ListStudentsBST(College &college);
void List_Students(vector<Student*> students, College &college);


void Uc_Menu(Uc &uc, College &college) {
	int n;
	if (access == 2) n = 3;
	else n = 2;
	while (1) {
		uc.showInfo();
		cout << "0:   LIST UCs STUDENTS" << endl;
		cout << "1:   LIST UCs TEACHERS" << endl;
		if (access == 2) cout << "2:   EDIT INFO" << endl;
		cout << n << ":   PREVIOUS" << endl;
		int i = (Nav(0, n));
		if (i == n) return;
		else if (i == 0) List_Students(uc.getStudents(),college);
		else if (i == 1) List_Teachers(uc.getTeachers(), college);
		else if (i == 2) uc.editInfo(college);
	}
}

//////////////////////

void Course_Ucs_Menu(Course &course, College &college) {
	course.showInfo();
	int x = course.showSyllabus();
	cout << "\n" << x << ":   PREVIOUS" << endl;
	int i = Nav(0, x);
	if (i == x) return;
	else Uc_Menu(*course.getUCs().at(i), college);
}

//////////////////////

void Course_Menu(Course& course, College &college) {
	int n;
	while (1) {
		course.showInfo();
		if (access == 2) n = 5;
		else n = 2;
		cout << "0:   SHOW COURSE PROGRAM" << endl;
		cout << "1:   SEARCH UC" << endl;
		if (access == 2) cout << "2:   EDIT INFO" << endl;
		if (access == 2) cout << "3:   ADD UC" << endl;
		if (access == 2) cout << "4:   REMOVE UC" << endl;
		cout << n << ":   PREVIOUS MENU" << endl;
		Uc* ptr;
		int i = (Nav(0, n));
		if (i == n) return;
		else if (i == 0) Course_Ucs_Menu(course, college);
		else if (i == 1) {
			ptr = Search_Menu(course.getUCs());
			if (ptr != nullptr) Uc_Menu(*ptr, college);
			else continue;
		}
		else if (i == 2 && access == 2) {
			course.editInfo(college);
		}
		else if (i == 3 && access == 2) {
			course.addUC(college);
		}
		else if (i == 4 && access == 2) {
			try {
				course.removeUC();
			}
			catch (NoNameFound &err) {
				cout << err.errorMessage() << endl;
				continue;
			}
		}
	}
}

//////////////////////

template<class T>
void Courses_Menu(T &obj, College &college) { //Can be either college or Department
	while (1) {
		obj.showInfo();
		Print_Vec(obj.getCourses());
		size_t n = obj.getCourses().size();
		if (access != 2) n--;
		if (access == 2) cout << n << ":   ADD COURSE" << endl;
		if (access == 2) cout << ++n << ":   REMOVE COURSE" << endl;
		cout << ++n << ":   SEARCH COURSE" << endl;
		cout << ++n << ":   PREVIOUS MENU" << endl;
		unsigned int i = Nav(0, n);
		if (i == n) return;
		else if (i == n - 1) {
			Course* ptr;
			try {
				ptr = Search_Menu(obj.getCourses());
			}
			catch (NoNameFound &err) {
				cout << err.errorMessage() << endl;
				continue;
			}
			if (ptr != nullptr) Course_Menu(*ptr, college);
			else continue;
		}
		else if (i == n - 2 && access == 2) {
			Course* ptr;
			try {
				ptr = Search_Menu(obj.getCourses());
			}
			catch (NoNameFound &err) {
				cout << err.errorMessage() << endl;
				continue;
			}
			if (ptr != nullptr) {
				delete ptr;
				cout << "Course Removed!" << endl;
			}
			else continue;
		}
		else if (i == n - 3 && access == 2) obj.addCourse(college);
		else Course_Menu(*(obj.getCourses().at(i)), college);
	}
}

//////////////////////

void Dep_Menu(Department& department, College &college) {
	int n;
	if (access == 2) n = 2;
	else n = 1;
	while (1) {
		department.showInfo();
		cout << "0:   DEPARTMENT COURSES" << endl;
		if (access == 2) cout << "1:   EDIT INFO" << endl;
		cout << n << ":   PREVIOUS MENU" << endl;
		int i = Nav(0, n);
		if (i == n) return;
		switch (i) {
		case 0:
			Courses_Menu(department, college);
			break;
		case 1:
			department.editInfo(college);
			break;
		case 2:
			return;
		}
	}
}

//////////////////////

void Departments_Menu(College &college) {
	int n;
	while (1) {
		n = college.getDepartments().size();
		college.showInfo();
		Print_Vec(college.getDepartments());
		if (access != 2) n--;
		if (access == 2) cout << n << ":   ADD DEPARTMENT" << endl;
		if (access == 2) cout << ++n << ":   REMOVE DEPARTMENT" << endl;
		cout << ++n << ":   SEARCH DEPARTMENT" << endl;
		cout << ++n << ":   PREVIOUS MENU" << endl;
		int i = Nav(0, n);
		if (i == n) { //Previous
			return;
		}
		else if (i == (n - 3) && access == 2) { //Add department
			college.addDepartment();
		}
		else if (i == (n - 2) && access == 2) { //Remove department
			try {
				college.removeDepartment();
			}
			catch (NoCodeFound &err) {
				cout << err.errorMessage() << endl;
				continue;
			}
		}
		else if (i == (n - 1)) { //Search Department by name
			auto ptr = Search_Menu(college.getDepartments());
			if (ptr != nullptr) Dep_Menu(*ptr, college);
		}
		else { //Enter department
			Dep_Menu(*college.getDepartments().at(i), college);
		}
	}
}

//////////////////////

void Grades_Menu(People &person, College &college) {
	Student *st = dynamic_cast<Student*>(&person);
	while (1) {
		st->showAllGrades();
		int n = st->getGrades()->size();
        cout << endl;
		if (access != 2) n--;
        if (access == 2) cout << n << ":   CHANGE UC GRADE" << endl;
		if (access == 2) cout << ++n << ":   ADD UC" << endl;
		if (access == 2) cout << ++n << ":   REMOVE UC" << endl;
		cout << ++n << ":   PREVIOUS" << endl;
		int i = Nav(0, n);
		if (i == n) return;
		else if (i == n - 1 && access == 2) {
			string uc_name;
			cout << "Insert the Uc you would like to remove: " << flush;
			do {
				cout << "Insert the Uc you would like to remove(! - cancel): " << flush;
				getline(cin, uc_name);
				if (uc_name == "!") break;
			} while (!st->removeFromMap(uc_name));
            st->Calculate_Average();
            college.Rearrange_Queue(st);
		}
		else if (i == n - 2 && access == 2)
        {
            st->InsertUC();
            st->Calculate_Average();
            college.Rearrange_Queue(st);
        }
        else if (i == n - 3 && access == 2) {
            while(1){
                cout << "\nInsert number of UC whose grade you want to change( " << st->getGrades()->size() << " - cancel): " << flush;
                int i = Nav(0,st->getGrades()->size());
                if(i == st->getGrades()->size()) break;
                else{
                    double grade;
                    cout << "\nInsert Student's UC grade(-1 if not-evaluated): " << flush;
                    cin >> grade;
                    while (cin.fail() || grade > 20 || (grade < 0 && grade != -1))
                    {
                        cout << "\nInvalid grade, try again: " << endl;
                        cin.clear();
                        cin.ignore(100, '\n');
                        cin >> grade;
                    }
                    cin.clear();
                    cin.ignore(100, '\n');
                    auto it = st->getGrades()->begin();
                    advance(it,i);
                    if(!st->changeGrade(it->first,grade)) cout << "\n Unexpected Error! grade not changed..." << endl;
                }
            }
            st->Calculate_Average();
            college.Rearrange_Queue(st);
        }
		else {
			auto it = st->getGrades()->begin();
			advance(it, i);
			Uc_Menu(*it->first, college);
		}
	}
}

//////////////////////

template<class T>
void Person_Menu(T &person, College &college) {
	int n = -1, i;
	while (1) {
		person.showInfo();
		if ((access == 1 && user_id == person.getCode()) || access == 2) {
			n = person.Special_Info();
			cout << n << ":   EDIT INFO" << endl;
		}
		cout << ++n << ":   PREVIOUS MENU" << endl;
		i = Nav(0, n);
		if (i == n) return;
		else if (i == n - 1) person.editInfo(college);
		else if (i == n - 2) Grades_Menu(person, college);
	}
}

//////////////////////

void Remove_Person(College &college) {
	int i;
	while (1) {
		cout << "\nWhat Type of person would you like to remove?" << endl;
		cout << "0:   STUDENT" << endl;
		cout << "1:   TEACHER" << endl;
		cout << "2:   STAFF" << endl;
		cout << "3:   CANCEL" << endl;
		i = Nav(0, 3);
		if (i == 3) return;
		else if (i == 0) {
			auto ptr = SearchStudent(college);
			if (ptr != nullptr) college.removeStudentBST(ptr);
		}
		else if (i == 1) {
			auto ptr = Search_Menu(college.getTeachers());
			if (ptr != nullptr) college.removeTeacher(ptr);
		}
		else if (i == 2) {
			auto ptr = Search_Menu(college.getStaff());
			if (ptr != nullptr) college.removeStaff(ptr);
		}
	}
}

//////////////////////

void List_Staff(College &college) {
	int s, i;
	while (1) {
		s = college.getStaff().size();
		Print_Vec(college.getStaff());
		cout << s << ":   SEARCH STAFF" << endl;
		cout << ++s << ":   PREVIOUS MENU" << endl;
		i = Nav(0, s);
		if (i == s) return;
		else if (i == s - 1) {
			auto ptr = Search_Menu(college.getStaff());
			if (ptr != nullptr) Person_Menu(*ptr, college);
		}
		else Person_Menu(*(college.getStaff().at(i)), college);
	}
}

//////////////////////

void List_Teachers(vector<Teacher*> teachers, College &college) {
	int s, i;
	while (1) {
		s = teachers.size();
		Print_Vec(teachers);
		cout << s << ":   SEARCH TEACHER" << endl;
		cout << ++s << ":   PREVIOUS MENU" << endl;
		i = Nav(0, s);
		if (i == s) return;
		else if (i == s - 1) {
			auto ptr = Search_Menu(teachers);
			if (ptr != nullptr) Person_Menu(*ptr, college);
		}
		else if (access != 0) Person_Menu(*teachers.at(i), college);
		else cout << "You don't have permission to access Profiles as a guest!" << endl;
	}
}


//////////////////////
void List_Students(vector<Student*> students, College &college) {
	int s, i;
	while (1) {
		s = students.size();
		Print_Vec(students);
		cout << s << ":   SEARCH STUDENT" << endl;
		cout << ++s << ":   PREVIOUS MENU" << endl;
		i = Nav(0, s);
		if (i == s) return;
		else if (i == s - 1) {
			auto ptr = Search_Menu(students);
			if (ptr != nullptr) Person_Menu(*ptr, college);
		}
		else if (access != 0) Person_Menu(*students.at(i), college);
		else cout << "You don't have permission to access Profiles as a guest!" << endl;
	}
}
void ListStudentsBST(College &college) {
	int s, i;
	while (1) {
		s = college.sizeBST();
		//Print_Vec(students);
		college.showStudents();
		cout << s << ":   SEARCH STUDENT" << endl;
		cout << ++s << ":   PREVIOUS MENU" << endl;
		i = Nav(0, s);
		if (i == s) return;
		else if (i == s - 1) {
			auto ptr = SearchStudent(college);
			if (ptr != nullptr) Person_Menu(*ptr, college);
		}
		else if (access != 0) Person_Menu(*college.BSTtoVEC().at(i), college);
		else cout << "You don't have permission to access Profiles as a guest!" << endl;
	}
}

//////////////////////

void Add_Person(College &college) {
	int i;
	while (1) {
		cout << "What Type of person would you like to add?" << endl;
		cout << "0:   STUDENT" << endl;
		cout << "1:   TEACHER" << endl;
		cout << "2:   STAFF" << endl;
		cout << "3:   CANCEL" << endl;
		i = Nav(0, 3);

		if (i == 3) return;
		else if (i == 0) {
			Student *st = new Student();
			try {
				st->addPerson(college);
			}
			catch (NoCourses &err) {
				cout << err.errorMessage() << " Please Create a Course before enrolling a student!" << endl;
			}
		}
		else if (i == 1) {
			Teacher *tch = new Teacher();
			tch->addPerson(college);
		}
		else if (i == 2) {
			Staff *stf = new Staff();
			stf->addPerson(college);
		}
	}
}

//////////////////////

void People_Menu(College &college) {
	int n;
	if (access == 2) n = 5;
	else n = 3;
	while (1) {
		college.showInfo();
		cout << "0:   LIST ALL STUDENTS" << endl;
		cout << "1:   LIST ALL TEACHERS" << endl;
		cout << "2:   LIST ALL STAFF" << endl;
		if (access == 2) cout << "3:   ADD PERSON" << endl;
		if (access == 2) cout << "4:   REMOVE PERSON" << endl;
		cout << n << ":   PREVIOUS MENU" << endl;
		int i = Nav(0, 5);
		if (i == n) return;
		switch (i) {
		case 0:
			ListStudentsBST(college);
			break;
		case 1:
			List_Teachers(college.getTeachers(), college);
			break;
		case 2:
			List_Staff(college);
			break;
		case 3:
			Add_Person(college);
			break;
		case 4:
			Remove_Person(college);
			break;
		}
	}
}

//////////////////////

void Member_Menu(College &college) { //Can only read
	while (1) {
		college.showInfo();
		cout << "0:   DEPARTMENTS" << endl;
		cout << "1:   COURSES" << endl;
		cout << "2:   PEOPLE" << endl;
		cout << "3:   PROFILE" << endl;
		cout << "4:   EXIT COLLEGE" << endl;
		switch (Nav(0, 4)) {
		case 0:
			Departments_Menu(college);
			break;
		case 1:
			Courses_Menu(college, college);
			break;
		case 2:
			People_Menu(college);
			break;
		case 3:
			if (user_id.at(0) == '0') {
				Student* st = SearchID(college.BSTtoVEC(), user_id);
				Person_Menu(*st, college);
			}
			else if (user_id.at(0) == '1') {
				Teacher* tch = SearchID(college.getTeachers(), user_id);
				Person_Menu(*tch, college);
			}
			else if (user_id.at(0) == '2') {
				Staff* stf = SearchID(college.getStaff(), user_id);
				Person_Menu(*stf, college);
			}
			break;
		case 4:
			return;
		}
	}
}

//////////////////////

void Vis_Menu(College &college) { //Can only see info
	while (1) {
		college.showInfo();
		cout << "0:   DEPARTMENTS" << endl;
		cout << "1:   COURSES" << endl;
		cout << "2:   EXIT COLLEGE" << endl;
		switch (Nav(0, 2)) {
		case 0:
			Departments_Menu(college);
			break;
		case 1:
			Courses_Menu(college, college);
			break;
		case 2:
			return;
		}
	}
}

//////////////////////

string Choose_Colleges() {
	ifstream file;
	int x = -1, i = 0, input;
	string file_name = "college0.txt";
	string college_name;
	vector<string> colleges;
	while (i != 30) {
		file.open(file_name);
		if (file.is_open()) {
			getline(file, college_name);
			getline(file, college_name);
			cout << ++x << ":   " << college_name.substr(0, college_name.find("|")) << endl;
			file.close();
			colleges.push_back(file_name);
		}
		i++;
		file_name = "college" + to_string(i) + ".txt";
	}
	cout << ++x << ":   PREVIOUS MENU" << endl;
	input = Nav(0, x);
	if (input == x) return "BACK";
	else{
        college_file_name = colleges.at(input);
        return colleges.at(input);
    }
}

//////////////////////

void Save_College(College &college) {
	string file_name = "college0.txt";
	ifstream file;
	int i = 0;
	while (i != 30) {
		file.open(file_name);
		if (file.is_open()) {
			i++;
			file_name = "college" + to_string(i) + ".txt";
			file.close();
		}
		else break;
	}
    if(college_file_name != "!") file_name = college_file_name;
	ofstream save_file(file_name);
	//------COLLEGE INFO------
	save_file << "COLLEGE:" << endl;
	save_file << college << endl;
	//------STUDENTS INFO------
	save_file << "STUDENTS:" << endl;
	for (unsigned int i = 0; i < college.BSTtoVEC().size(); i++) {
		save_file << *college.BSTtoVEC().at(i);
	}
	save_file << endl;
	//------TEACHERS INFO------
	save_file << "TEACHER:" << endl;
	for (unsigned int i = 0; i < college.getTeachers().size(); i++) {
		save_file << *college.getTeachers().at(i);
	}
	save_file << endl;
	//------STAFF INFO------
	save_file << "STAFF:" << endl;
	for (unsigned int i = 0; i < college.getStaff().size(); i++) {
		save_file << *college.getStaff().at(i);
	}
	save_file << endl;
	//------DEP/COURSE/UC INFO------
	for (unsigned int i = 0; i < college.getDepartments().size(); i++) {
		save_file << "DEP:" << endl;
		save_file << *college.getDepartments().at(i);
		save_file << endl;
	}
	//------FORMER TEACHER------
	save_file << "FORMER TEACHER:" << endl;
	for (unsigned int j = 0; j < college.getEmployees().size(); j++)
	{
		if (!college.getEmployees().at(j).getWorkingState() &&
			college.getEmployees().at(j).getCode().at(0) == '1')
		{
			save_file << *(college.getEmployees().at(j).getTeacher());
		}
	}
	save_file << endl;
	//------FORMER STAFF------
	save_file << "FORMER STAFF:" << endl;
	for (unsigned int j = 0; j < college.getEmployees().size(); j++)
	{
		if (!college.getEmployees().at(j).getWorkingState() &&
			college.getEmployees().at(j).getCode().at(0) == '2')
		{
			save_file << *(college.getEmployees().at(j).getStaff());
		}
	}
	
	save_file.close();
}

//////////////////////

bool Exit_College(College &college) {
	college.showInfo();
	cout << "0:   SAVE AND EXIT" << endl;
	cout << "1:   EXIT WITHOUT SAVING" << endl;
	cout << "2:   CANCEL" << endl;
	switch (Nav(0, 2)) {
	case 0:
		Save_College(college);
		return true;
	case 1:
		return true;
	case 2:
		return false;
	default: return false;
	}
}




//////////////////////


int my_search_vec(vector<EmployeePtr> vec, string name) {
	for (size_t i = 0; i < vec.size(); i++) {
		if (vec.at(i).getName() == name) 
			return i;
	}
	throw NoNameFound(name);
}

pair<int, int> my_search(vector<EmployeePtr> vec) {
	string name;
	pair<int, int> i (-1,-1);
	while (1) {
		cout << "Insert the name you want to search for(! to cancel): " << flush;
		getline(cin, name);
		if (name == "!") return i;
		try {
			i.first = my_search_vec(vec, name);
			i.second = vec.at(i.first).getCode().at(0);
		}
		catch (NoNameFound &err) {
			cout << err.errorMessage() << endl;
			continue;
		}
		break;
	}
	return i;
}

void List_Current_Employees(College &college)
{
	int s = 0, i;
	vector<EmployeePtr> temp;

	cout << college.getEmployees().size() << endl;

	while (1)
	{
		for (unsigned int j = 0; j < college.getEmployees().size(); j++)
		{
			if (college.getEmployees().at(j).getWorkingState())
			{
				cout << s << ":   " << college.getEmployees().at(j).getName() << endl;
				s++;
				temp.push_back(college.getEmployees().at(j));
			}
		}

		cout << s << ":   SEARCH STAFF" << endl;
		cout << ++s << ":   PREVIOUS MENU" << endl;

		i = Nav(0, s);
		if (i == s) return;

		else if (i == s - 1)
		{
			pair<int, int> j = my_search(temp);
			if (j.first != -1)
			{
				if (j.second == '2')
					Person_Menu(*(temp.at(j.first).getStaff()), college);
				else
					Person_Menu(*(temp.at(j.first).getTeacher()), college);
			}
		}
		else
		{
			if (temp.at(i).getCode().at(0) == '2')
				Person_Menu(*(temp.at(i).getStaff()), college);
			else
				Person_Menu(*(temp.at(i).getTeacher()), college);
		}

		s = 0; /* not sure why i have to reset this*/
	}
}

void List_Former_Employees(College &college)
{
	int s = 0, i, salary;
	vector<EmployeePtr> temp;

	while (1)
	{
		for (unsigned int j = 0; j < college.getEmployees().size(); j++)
		{
			if (!college.getEmployees().at(j).getWorkingState())
			{
				cout << s << ":   " << college.getEmployees().at(j).getName() << endl;
				s++;
				temp.push_back(college.getEmployees().at(j));
			}
		}

		cout << s << ":   SEARCH EMPLOYEES" << endl;
		cout << ++s << ":   HIRE EMPLOYEE" << endl;
		cout << ++s << ":   PREVIOUS MENU" << endl;

		i = Nav(0, s);
		if (i == s) return;

		else if (i == s - 2)
		{
			pair<int, int> j = my_search(temp);
			if (j.first != -1)
			{
				if (j.second == '2')
					Person_Menu(*(temp.at(j.first).getStaff()), college);
				else
					Person_Menu(*(temp.at(j.first).getTeacher()), college);
			}
		}

		else if (i == s - 1)
		{
			pair<int, int> j = my_search(temp);
			if (j.first != -1)
			{
				if (j.second == '2')
				{
					Staff* sf = temp.at(j.first).getStaff();
					sf->setWorking(true);
					college.addStaff(sf);

					cout << endl << "-" << sf->getName() << "- used to earn" << " -" << sf->getSalary() << "- Euros!" << endl;
					cout << "If you wish to change it, insert a new salary (0 - keep salary): " << flush;

					cin >> salary;

					while(cin.fail())
					{
						cout << "Invalid number, try again: " << endl;
						cin.clear();
						cin.ignore(100, '\n');
						cin >> salary;
					}

					if (salary != 0)
						sf->setSalary(salary);

					cout << endl << "-" << sf->getName() << "- hired successfully with a salary of" << " -" << sf->getSalary() << "- Euros!" << endl << endl;
				}
				else
				{
					Teacher* t = temp.at(j.first).getTeacher();
					t->setWorking(true);
					college.addTeacher(temp.at(j.first).getTeacher());

					cout << endl << "-" << t->getName() << "- used to earn" << " -" << t->getSalary() << "- Euros!" << endl;
					cout << "If you wish to change it, insert a new salary (0 - keep salary): " << flush;

					cin >> salary;

					while(cin.fail())
					{
						cout << "Invalid number, try again: " << endl;
						cin.clear();
						cin.ignore(100, '\n');
						cin >> salary;
					}

					if (salary != 0)
						t->setSalary(salary);

					cout << endl << "-" << t->getName() << "- hired successfully with a salary of" << " -" << t->getSalary() << "- Euros!" << endl << endl;
				}
			}
		}

		else
		{
			if (temp.at(i).getCode().at(0) == '2')
				Person_Menu(*(temp.at(i).getStaff()), college);
			else
				Person_Menu(*(temp.at(i).getTeacher()), college);
		}

		s = 0;
	}
}


//////////////////////

void Hash_Table_Menu(College &college){
    while(1){
        cout << "0:   CURRENT EMPLOYEES" << endl;
		cout << "1:   FORMER EMPLOYEES" << endl;
		cout << "2:   PREVIOUS MENU" << endl;
        switch(Nav(0,2)){
            case 0:
				List_Current_Employees(college);
				break;
			case 1:
				List_Former_Employees(college);
				break;
            case 2:
				return;
        }
    }
}

//////////////////////

void Give_Scholarship(College &college){
    cout << "How many scholarships do you want to give out? (0 - cancel)" << endl;
    unsigned int number = 0;
    do{
        cin >> number;
        cin.ignore(100,'\n');
        cin.clear();
    } while(number < 0);
    if(number == 0) return;
    else cout << "How much money will each Scholarship be worth?" << endl;
    unsigned int value = 0;
    do{
        cin >> value;
        cin.ignore(100,'\n');
        cin.clear();
    } while(value < 0);
    Student* st;
    for(size_t i = 0; i < number; i++){
        st = college.Get_Top_Student();
        st->Add_Funds(value);
        college.Rearrange_Queue(st);
    }
}

//////////////////////

void Collect_Payment(College &college){
    cout << "How much will be charged? (0 - cancel)" << endl;
    unsigned int value = 0;
    do{
        cin >> value;
        cin.ignore(100,'\n');
        cin.clear();
    } while(value < 0);
    if(value == 0) return;
    for(unsigned int i = 0; i < college.getStudents().size(); i++){
        college.getStudents()[i]->Pay_Semester(value);
        college.Rearrange_Queue(college.getStudents()[i]);
    }
}

void Queue_Menu(College &college){
    Student* st;
    while(1){
        college.showInfo();
        cout << "0:   GET TOP STUDENT" << endl;
        cout << "1:   GIVE SCHOLARSHIP" << endl;
        cout << "2:   COLLECT SEMESTER PAYMENT" << endl;
        cout << "3:   PREVIOUS MENU" << endl;
        switch(Nav(0,3)){
            case 0:
                st = college.Get_Top_Student();
                if(st != nullptr) Person_Menu(*st,college);
                break;
            case 1:
                Give_Scholarship(college);
                break;
            case 2:
                Collect_Payment(college);
                break;
            case 3:
                return;
        }
    }
}

//////////////////////

void Admin_Menu(College &college) {
	while (1) {
		college.showInfo();
		cout << "0:   DEPARTMENTS" << endl;
		cout << "1:   COURSES" << endl;
		cout << "2:   PEOPLE" << endl;
        cout << "3:   EMPLOYEES" << endl;
        cout << "4:   SCHOLARSHIPS" << endl;
		cout << "5:   EXIT COLLEGE" << endl;
		switch (Nav(0, 6)) {
		case 0:
			Departments_Menu(college);
			break;
		case 1:
			Courses_Menu(college, college);
			break;
		case 2:
			People_Menu(college);
			break;
		case 5:
			if (Exit_College(college)) return;
			else break;
        case 3:
            Hash_Table_Menu(college);
            break;
        case 4:
            Queue_Menu(college);
            break;
		}
	}
}

//////////////////////

bool Admin_LogIn(College& college) {
	string code;
	while (1) {
		cout << "\nEnter Admin code(! - cancel): " << flush;
		getline(cin, code);
		if (code == "!") return false;
		else if (code == college.getAdmin()) return true;
		else cout << "Wrong code, Try again!" << endl;
	}
}

//////////////////////

bool Member_LogIn(College& college) {
	while (1) {
		string name, code, type;
		cout << "\nDo you want to log in as a Teacher or Student?(! to cancel/ S - Student/ T - Teacher): " << endl;
		getline(cin, type);
		if (type == "!") return false;
		else if (type != "S" && type != "T") {
			cout << "Invalid Input! Try again!" << endl;
			continue;
		}
		cout << "\nInsert your name(! to cancel): " << flush;
		getline(cin, name);
		if (name == "!") continue;
		else if (type == "T") {
			Teacher* t;
			try {
				t = SearchVec(college.getTeachers(), name);
			}
			catch (NoNameFound &err) {
				cout << err.errorMessage() << " Try again!" << endl;
				continue;
			}
			while (1) {
				cout << "\nInsert your code(! to cancel): " << flush;
				getline(cin, code);
				if (code == "!") break;
				else if (code == t->getCode()) {
					user_id = code;
					return true;
				}
				else cout << "\nWrong Code! Try again!" << endl;
			}
		}
		else if (type == "S") {
			Student* s;
			try {
				s = SearchVec(college.BSTtoVEC(), name);
			}
			catch (NoNameFound &err) {
				cout << err.errorMessage() << " Try again!" << endl;
				continue;
			}
			while (1) {
				cout << "\nInsert your code(! to cancel): " << flush;
				getline(cin, code);
				if (code == "!") break;
				else if (code == s->getCode()) {
					user_id = code;
					return true;
				}
				else cout << "\nWrong Code! Try again!" << endl;
			}
		}
	}
}

//////////////////////

int Log_In(College& college) {
	int i;
	while (1) {
		cout << "0:   CONTINUE AS VISITOR" << endl;
		cout << "1:   LOG IN AS MEMBER" << endl;
		cout << "2:   LOG IN AS ADMIN" << endl;
		cout << "3:   PREVIOUS MENU" << endl;
		i = Nav(0, 3);
		switch (i) {
		case 0:
			break;
		case 1:
			if (!Member_LogIn(college)) continue;
			break;
		case 2:
			if (!Admin_LogIn(college)) continue;
			break;
		case 3:
			break;
		}
		return i;
	}
}

//////////////////////

int main() {
	while (1) {
		College college;
		string file;
		switch (Main_Menu()) {
		case 0:
			New_College(college);
			access = 2;
			break;
		case 1:
			file = Choose_Colleges();
			if (file == "BACK") {
				access = 3;
				break;
			}
			readFile(college, file);
			access = Log_In(college);
			break;
		case 2:
			return 0;
		default:
			return -1;
		}
		switch (access) {
		case 0:
			Vis_Menu(college);
			break;
		case 1:
			Member_Menu(college);
			break;
		case 2:
			Admin_Menu(college);
			break;
		case 3:
			break;
		default:
			return -1;
		}
	}
}
