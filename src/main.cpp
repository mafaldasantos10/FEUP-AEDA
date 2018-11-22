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


////CURRENT YEAR//// (used for ids)
time_t theTime = time(NULL);
struct tm *aTime = localtime(&theTime);
int current_year = aTime->tm_year + 1900; // Year is # years since 1900


/// PROTOTYPES ///
date* changeDate(string data);
enum Cat CatEnum(string s);


///READ FILE
void readFile(College &c, string file)
{
	ifstream fin;
	date* d;

	fin.open(file);

	string next; //line from the file

	while(!fin.eof())
	{
		getline(fin, next);

			if(next.length() == 0)
			{
				continue;
			}

			if(next == "COLLEGE:")
			{
				getline(fin, next);

				int i = next.find("|");


				c.setName(next.substr(0, i));
				next.erase(0, i+1);
				c.setAdmin(next.substr(0, next.length()));
			}

			if(next == "STUDENTS:")
			{
				while(next.length() != 0)
				{
					Student* s;

					getline(fin, next);

					s->setName(next.substr(0,  next.find("|")));
					next.erase(0,  next.find("|")+1);

					s->setAddress(next.substr(0,  next.find("|")));
					next.erase(0,  next.find("|")+1);

					s->setPhone(stoi(next.substr(0,  next.find("|"))));
					next.erase(0,  next.find("|")+1);

					s->setCode(next.substr(0,  next.find("|")));
					next.erase(0,  next.find("|")+1);

					d = changeDate(next.substr(0, next.find("|")));
					s->setDate(d);
					next.erase(0,  next.find("|")+1);

					s->setName(next.substr(0,  next.find("|")));
					next.erase(0,  next.find("|")+1);

					s->setYear(stoi(next.substr(0,  next.find("|"))));
					next.erase(0,  next.find("|")+1);

					c.getStudents().push_back(s); //ver se altera o vector mesmo
				}

			}

			if(next == "TEACHER:")
			{
				while(next.length() != 0)
				{
					Teacher* t;

					getline(fin, next);

					t->setName(next.substr(0,  next.find("|")));
					next.erase(0,  next.find("|")+1);

					t->setAddress(next.substr(0,  next.find("|")));
					next.erase(0,  next.find("|")+1);

					t->setPhone(stoi(next.substr(0,  next.find("|"))));
					next.erase(0,  next.find("|")+1);

					t->setCode(next.substr(0,  next.find("|")));
					next.erase(0,  next.find("|")+1);

					d = changeDate(next.substr(0, next.find("|")));
					t->setDate(d);
					next.erase(0,  next.find("|")+1);

					t->setSalary(stof(next.substr(0,  next.find("|"))));
					next.erase(0,  next.find("|")+1);

					t->setNIF(stoi(next.substr(0,  next.find("|"))));
					next.erase(0,  next.find("|")+1);

					t->setCategory(CatEnum(next.substr(0,  next.find("|"))));
					next.erase(0,  next.find("|")+1);

					c.getTeachers().push_back(t);
				}

			}

		  if(next == "STAFF:")
			{
			  	 while(next.length() != 0)
			  	 {
					Staff* sf;

					getline(fin, next);

					sf->setName(next.substr(0,  next.find("|")));
					next.erase(0,  next.find("|")+1);

					sf->setAddress(next.substr(0,  next.find("|")));
					next.erase(0,  next.find("|")+1);

					sf->setPhone(stoi(next.substr(0,  next.find("|"))));
					next.erase(0,  next.find("|")+1);

					sf->setCode(next.substr(0,  next.find("|")));
					next.erase(0,  next.find("|")+1);

					d = changeDate(next.substr(0, next.find("|")));
					sf->setDate(d);
					next.erase(0,  next.find("|")+1);

					sf->setSalary(stof(next.substr(0,  next.find("|"))));
					next.erase(0,  next.find("|")+1);

					sf->setNIF(stoi(next.substr(0,  next.find("|"))));
					next.erase(0,  next.find("|")+1);

					sf->setWorkArea(next.substr(0,  next.find("|")));
					next.erase(0,  next.find("|")+1);

					c.getStaff().push_back(sf);
				}
			}

		  if(next == "DEP:")
		  {
			    Teacher* dir;
			  	getline(fin, next);
		 		Department* d;

		  		d->setName(next.substr(0, next.find("|")));
		  		next.erase(0, next.find("|")+1);

		  		d->setAddress(next.substr(0, next.find("|")));
		  		next.erase(0, next.find("|")+1);

		  		d->setCode(stoi(next.substr(0, next.find("|"))));
		  		next.erase(0, next.find("|")+1);

		  		d->setPhone(stoi(next.substr(0, next.find("|"))));
		  		next.erase(0, next.find("|")+1);

		  		if((next.substr(0, next.find("|"))) == "!")
		  		{
		  			dir = SearchVec( c.getTeachers(),(next.substr(0, next.find("|"))));
		  			d->setDirector(dir);
		  		}

		  		c.getDepartments().push_back(d);

		  		getline(fin, next);

		  		while(next.length() != 0)
		  		{
			  		if(next == "COURSE:")
			  		{
			  			Teacher* dirc;
			  			Course* cs;

			  			getline(fin, next);

			  			cs->setPtName(next.substr(0, next.find("|")));
			  			next.erase(0, next.find("|")+1);

			  			cs->setEngName(next.substr(0, next.find("|")));
			  			next.erase(0, next.find("|")+1);

			  			cs->setCode(stoi(next.substr(0, next.find("|"))));
			  			next.erase(0, next.find("|")+1);

			  			cs->setType(next.substr(0, next.find("|")));
			  			next.erase(0, next.find("|")+1);

			  			if((next.substr(0, next.find("|"))) == "!")
			  			{
			  				dirc = SearchVec( c.getTeachers(), (next.substr(0, next.find("|"))));
			  				cs->setDirector(dirc);
			  			}
			  			d->getCourses().push_back(cs);

			  			getline(fin, next);

			  			if(next == "UC:")
			  			{
			  				while(1)
			  				{
			  					Teacher* regent;
			  					Uc* uc;

			  					getline(fin, next);

			  					if(next == "COURSE:")
			  						break;

			  					uc->setName(next.substr(0,  next.find("|")));
			  					next.erase(0,  next.find("|")+1);

			  					uc->setYear(stoi(next.substr(0,  next.find("|"))));
			  					next.erase(0,  next.find("|")+1);

			  					uc->setECTS(stoi(next.substr(0,  next.find("|"))));
			  					next.erase(0,  next.find("|")+1);

			  					uc->setWorkload(stoi(next.substr(0,  next.find("|"))));
			  					next.erase(0,  next.find("|")+1);

			  					if((next.substr(0, next.find("|"))) == "!")
			  					{
			  						regent = SearchVec( c.getTeachers(),(next.substr(0, next.find("|"))));
			  						uc->getTeachers().push_back(regent);
			  					}

			  					c.getUCs().push_back(uc);
			  				}
			  			}

			  			c.getCourses().push_back(cs);
			  		}
		  		}
		}
	}
}


////GENERAL FUNCTIONS//// (used thoughout project, mostly for input verification)
int Nav(int bottom, int top){ //tests for valid input keys and returns the inputted char
    int key;
    cin >> key;
    while(cin.fail() || key < bottom || key > top){ //Problem with cin getting corrupted if several characters are introduced
        cin.clear();
        cin.ignore(100,'\n');
        cout << "Invalid Input!" << endl;
        cin >> key;
    }
    cin.clear();
    cin.ignore(100,'\n');
    return key;
}

date* changeDate(string data)
{
    unsigned int day, month, year;
    char c = '/';

    stringstream ss(data);
    ss >> day >> c >> month >> c >> year;
    if(day < 0 || day > 31
               || month < 0 || month > 12
               || year < 1900 || year > 2018) {
        cout << "\nInvalid date!" << endl;
        return nullptr;
    }

    date *d = new date(day, month, year);
      return d;
}

date* readDate(){
    date* d;
    string data;
    cin.clear();
    cin.ignore(100,'\n');
    while(1){
        cout << "\nInsert Birthday(dd/mm/yyyy): " << flush;
        getline(cin,data);
        d = changeDate(data);
        if(d != nullptr) break;
    }
return d;
}

enum Cat CatEnum(string s){
    if(s == "Auxiliar Professor") return Aux;
    else if( s == "Regent") return Reg;
    else if(s ==  "Department Director") return DepDir;
    else if(s == "Course Director") return CourseDir;
    else return Default;
}

//////////////////////

int Main_Menu(){
    cout << "----------------------" << endl;
    cout << "|      MAIN MENU     |" << endl;
    cout << "----------------------" << endl;
    cout << "0:   CREATE COLLEGE" << endl;
    cout << "1:   LOAD COLLEGE" << endl;
    cout << "2:   EXIT" << endl;
    return Nav(0,2);
}

//////////////////////

void New_College(College &college){
    string college_name, admin;
    cout << "Insert your College Name: " << flush;
    getline(cin, college_name); //////////INPUT VALIDATION MISSING!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!(s� para ter a certeza q v�m)
    cout << endl << "Insert your Admin Code: " << flush;
    getline(cin, admin);
    college.setName(college_name);
    college.setAdmin(admin);
    cout << "\n\n\n" << endl;
}

//////////////////////

template<class T>
T* Search_Menu(vector<T*> vec){
    string name;
    T* t;
    while(1){
        cout << "Insert the name you want to search for(! to cancel): " << flush;
        getline(cin,name);
        if(name == "!") return nullptr;
        try{
            t = SearchVec(vec,name);
        }
        catch(NoNameFound &err){
            cout << err.errorMessage() << endl;
            continue;
        }
        break;
    }
    return t;
}

//////////////////////

void Course_Menu(Course& course, College &college){
    while(1){
        course.showInfo();
        cout << "0:   EDIT INFO" << endl;
        cout << "1:   SHOW COURSE PROGRAM" << endl;
        cout << "2:   ADD UC" << endl;
        cout << "3:   REMOVE UC" << endl;
        cout << "4:   SEARCH UC" << endl;
        cout << "5:   PREVIOUS MENU" << endl;
        Uc* ptr;
        switch(Nav(0,5)){
            case 0:
                course.editInfo(college);
                break;
            case 1:
                course.showSyllabus();
                break;
            case 2:
                course.addUC(college);
                break;
            case 3:
                try{
                    course.removeUC();
                }
                catch(NoNameFound &err){
                    cout << err.errorMessage() << endl;
                    continue;
                }
                break;
            case 4:
                ptr = Search_Menu(course.getUCs());
                if(ptr != nullptr) ;//Uc_Menu(*ptr);
                else continue;
            case 5:
                return;
        }
    }
}

//////////////////////

template<class T>
void Courses_Menu(T &obj, College &college){ //Can be either college or Department
    while(1){
        obj.showInfo();
        Print_Vec(obj.getCourses());
        size_t n = obj.getCourses().size();
        cout << n << ":   ADD COURSE" << endl;
        cout << ++n << ":   REMOVE COURSE" << endl;
        cout << ++n << ":   SEARCH COURSE" << endl;
        cout << ++n << ":   PREVIOUS MENU" << endl;
        int i = Nav(0,n);
        if(i == n) return;
        else if(i == n-1){
            Course* ptr;
            try{
                ptr = Search_Menu(obj.getCourses());
            }
            catch(NoNameFound &err){
                cout << err.errorMessage() << endl;
                continue;
            }
            if(ptr != nullptr) Course_Menu(*ptr, college);
            else continue;
        }
        else if(i == n-2){
            Course* ptr;
            try{
                ptr = Search_Menu(obj.getCourses());
            }
            catch(NoNameFound &err){
                cout << err.errorMessage() << endl;
                continue;
            }
            if(ptr != nullptr) {
                delete ptr;
                cout << "Course Removed!" << endl;
            }
            else continue;
        }
        else if(i == n-3) obj.addCourse(college);
        else Course_Menu(*(obj.getCourses().at(i)),college);
    }
}

//////////////////////

void Dep_Menu(Department& department, College &college){
    while(1){
        department.showInfo();
        cout << "0:   DEPARTMENT COURSES" << endl;
        cout << "1:   EDIT INFO" << endl;
        cout << "2:   PREVIOUS MENU" << endl;
        switch(Nav(0,3)){
            case 0:
                Courses_Menu(department,college);
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

void Departments_Menu(College &college){
    int n;
    while(1) {
        n = college.getDepartments().size();
        college.showInfo();
        Print_Vec(college.getDepartments());
        cout << n << ":   ADD DEPARTMENT" << endl;
        cout << ++n << ":   REMOVE DEPARTMENT" << endl;
        cout << ++n << ":   SEARCH DEPARTMENT" << endl;
        cout << ++n << ":   PREVIOUS MENU" << endl;
        int i = Nav(0, n);
        if (i == n) { //Previous
            return;
        } else if (i == (n - 3)) { //Add department
            college.addDepartment();
        } else if (i == (n - 2)) { //Remove department
            try {
                college.removeDepartment();
            }
            catch(NoCodeFound &err){
                cout << err.errorMessage() << endl;
                continue;
            }
        } else if (i == (n - 1)) { //Search Department by name
            auto ptr = Search_Menu(college.getDepartments());
            if(ptr != nullptr) Dep_Menu(*ptr,college);
        } else { //Enter department
            Dep_Menu(*college.getDepartments().at(i),college);
        }
    }
}

//////////////////////

void Grades_Menu(People &person){
    Student *st = dynamic_cast<Student*>(&person);
    st->showAllGrades();
}

//////////////////////

template<class T>
void Person_Menu(T &person,College &college){
    int n = -1, i;
    while(1){
        person.showInfo();
        if((access == 1 && user_id == person.getCode()) || access == 2){
            n = person.Special_Info();
            cout << n << ":   EDIT INFO" << endl;
        }
        cout << ++n << ":   PREVIOUS MENU" << endl;
        i = Nav(0,n);
        if(i == n) return;
        else if( i == n-1) person.editInfo(college);
        else if(i == n-2) Grades_Menu(person);
    }
}

//////////////////////

void Remove_Person(College &college){
    int i;
    while(1) {
        cout << "\nWhat Type of person would you like to remove?" << endl;
        cout << "0:   STUDENT" << endl;
        cout << "1:   TEACHER" << endl;
        cout << "2:   STAFF" << endl;
        cout << "3:   CANCEL" << endl;
        i = Nav(0,3);
        if(i == 3) return;
        else if(i == 0){
            auto ptr = Search_Menu(college.getStudents());
            if(ptr != nullptr) college.removeStudent(ptr);
        }
        else if(i == 1) {
            auto ptr = Search_Menu(college.getTeachers());
            if(ptr != nullptr) college.removeTeacher(ptr);
        }
        else if(i == 2){
            auto ptr = Search_Menu(college.getStaff());
            if(ptr != nullptr) college.removeStaff(ptr);
        }
    }
}

//////////////////////

void List_Staff(College &college){
    int s, i;
    while(1){
        s = college.getStaff().size();
        Print_Vec(college.getStaff());
        cout << s << ":   SEARCH STAFF" << endl;
        cout << ++s << ":   PREVIOUS MENU" << endl;
        i = Nav(0,s);
        if(i == s) return;
        else if(i == s-1){
            auto ptr = Search_Menu(college.getStaff());
            if(ptr != nullptr) Person_Menu(*ptr,college);
        }
        else Person_Menu(*(college.getStaff().at(i)),college);
    }
}

//////////////////////

void List_Teachers(College &college){
    int s, i;
    while(1){
        s = college.getTeachers().size();
        Print_Vec(college.getTeachers());
        cout << s << ":   SEARCH TEACHER" << endl;
        cout << ++s << ":   PREVIOUS MENU" << endl;
        i = Nav(0,s);
        if(i == s) return;
        else if(i == s-1){
            auto ptr = Search_Menu(college.getTeachers());
            if(ptr != nullptr) Person_Menu(*ptr,college);
        }
        else Person_Menu(*(college.getTeachers().at(i)),college);
    }
}

//////////////////////

void List_Students(College &college){
    int s, i;
    while(1){
        s = college.getStudents().size();
        Print_Vec(college.getStudents());
        cout << s << ":   SEARCH STUDENT" << endl;
        cout << ++s << ":   PREVIOUS MENU" << endl;
        i = Nav(0,s);
        if(i == s) return;
        else if(i == s-1){
            auto ptr = Search_Menu(college.getStudents());
            if(ptr != nullptr) Person_Menu(*ptr,college);
        }
        else Person_Menu(*(college.getStudents().at(i)),college);
    }
}

//////////////////////

void Add_Person(College &college){
    int i;
    while(1) {
        cout << "What Type of person would you like to add?" << endl;
        cout << "0:   STUDENT" << endl;
        cout << "1:   TEACHER" << endl;
        cout << "2:   STAFF" << endl;
        cout << "3:   CANCEL" << endl;
        i = Nav(0, 3);

        if (i == 3) return;
        else if (i == 0) {
            Student *st = new Student();
            try{
                st->addPerson(college);
            }
            catch(NoCourses &err){
                cout << err.errorMessage() << " Please Create a Course before enrolling a student!" << endl;
            }
        } else if (i == 1) {
            Teacher *tch = new Teacher();
            tch->addPerson(college);
        } else if (i == 2) {
            Staff *stf = new Staff();
            stf->addPerson(college);
        }
    }
}

//////////////////////

void People_Menu(College &college){
    while(1) {
        college.showInfo();
        cout << "0:   LIST ALL STUDENTS" << endl;
        cout << "1:   LIST ALL TEACHERS" << endl;
        cout << "2:   LIST ALL STAFF" << endl;
        cout << "3:   ADD PERSON" << endl;
        cout << "4:   REMOVE PERSON" << endl;
        cout << "5:   PREVIOUS MENU" << endl;
        switch (Nav(0, 5)) {
            case 0:
                List_Students(college);
                break;
            case 1:
                List_Teachers(college);
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
            case 5:
                return;
        }
    }
}

//////////////////////

void Member_Menu(College &college){ //Can only read
    while(1){
        college.showInfo();
        cout << "0:   DEPARTMENTS" << endl;
        cout << "1:   COURSES" << endl;
        cout << "2:   PEOPLE" << endl;
        cout << "3:   PROFILE" << endl;
        cout << "4:   EXIT COLLEGE" << endl;
        switch(Nav(0,4)){
            case 0:
                Departments_Menu(college);
                break;
            case 1:
                Courses_Menu(college,college);
                break;
            case 2:
                People_Menu(college);
                break;
            case 3:
                //Use Search_Person(id) to show personal info
                break;
            case 4:
                //Destroy College and go back to main menu
                return;
        }
    }
}

//////////////////////

void Vis_Menu(College &college){ //Can only see info
    while(1){
        college.showInfo();
        cout << "0:   DEPARTMENTS" << endl;
        cout << "1:   COURSES" << endl;
        cout << "2:   EXIT COLLEGE" << endl;
        switch(Nav(0,2)){
            case 0:
                Departments_Menu(college);
                break;
            case 1:
                Courses_Menu(college,college);
                break;
            case 2:
                //Destroy College and go back to main menu
                return;
        }
    }
}

//////////////////////

string Choose_Colleges(){
    ifstream file;
    int x = -1,i = 0, input;
    string file_name = "college0.txt";
    string college_name;
    vector<string> colleges;
    while(i != 30){
        file.open(file_name);
        if(file.is_open()){
            getline(file, college_name);
            getline(file, college_name);
            cout << ++x << ":   " << college_name.substr(0, college_name.find("|"));
            colleges.push_back(file_name);
            file.close();
        }
        i++;
        file_name = "college" + to_string(i) + ".txt";
    }
    cout << ++x << ":   PREVIOUS MENU" << endl;
    input = Nav(0,x);
    if(input == x) return "BACK";
    else return colleges.at(x);
}

//////////////////////

void Save_College(College &college){
    string file_name = "college0.txt";
    ifstream file;
    int i = 0;
    while(i != 30){
        file.open(file_name);
        if(file.is_open()){
            i++;
            file_name = "college" + to_string(i) + ".txt";
            file.close();
        }
        else break;
    }
    ofstream save_file (file_name);
    //------COLLEGE INFO------
    save_file << "COLLEGE:" << endl;
    save_file << college << endl;
    //------STUDENTS INFO------
    save_file << "STUDENTS:" << endl;
    for(size_t i = 0; i < college.getStudents().size(); i++){
        save_file << *college.getStudents().at(i);
    }
    save_file << endl;
    //------TEACHERS INFO------
    save_file << "TEACHER:" << endl;
    for(size_t i = 0; i < college.getTeachers().size(); i++){
        save_file << *college.getTeachers().at(i);
    }
    save_file << endl;
    //------STAFF INFO------
    save_file << "STAFF:" << endl;
    for(size_t i = 0; i < college.getStaff().size(); i++){
        save_file << *college.getStaff().at(i);
    }
    save_file << endl;
    //------ DEP/COURSE/UC INFO------
    for(size_t i = 0; i < college.getDepartments().size(); i++){
        save_file << "DEP:" << endl;
        save_file << *college.getDepartments().at(i);
        save_file << endl;
    }
    save_file.close();
}

//////////////////////

bool Exit_College(College &college){
    college.showInfo();
    cout << "0:   SAVE AND EXIT" << endl;
    cout << "1:   EXIT WITHOUT SAVING" << endl;
    cout << "2:   CANCEL" << endl;
    switch(Nav(0,2)){
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

void Admin_Menu(College &college){
    while(1){
        college.showInfo();
        cout << "0:   DEPARTMENTS" << endl;
        cout << "1:   COURSES" << endl;
        cout << "2:   PEOPLE" << endl;
        cout << "3:   EXIT COLLEGE" << endl;
        switch(Nav(0,3)){
            case 0:
                Departments_Menu(college);
                break;
            case 1:
                Courses_Menu(college,college);
                break;
            case 2:
                People_Menu(college);
                break;
            case 3:
                if(Exit_College(college)) return;
                else break;
        }
    }
}

//////////////////////

bool Admin_LogIn(College& college) {
    string code;
    while (1) {
        cout << "\nEnter Admin code(! - cancel): " << flush;
        getline(cin,code);
        if(code == "!") return false;
        else if(code == college.getAdmin()) return true;
        else cout << "Wrong code, Try again!" << endl;
    }
}

//////////////////////

bool Member_LogIn(College& college){
    while(1){
        string name, code, type;
        cout << "\nDo you want to log in as a Teacher or Student?(! to cancel/ S - Student/ T - Teacher): " << endl;
        getline(cin,type);
        if(type == "!") return false;
        else if(type != "S" && type != "T"){
            cout << "Invalid Input! Try again!" << endl;
            continue;
        }
        cout << "\nInsert your name(! to cancel): " << flush;
        getline(cin,name);
        if(name == "!") continue;
        else if(type == "T"){
            Teacher* t;
            try{
                t = SearchVec(college.getTeachers(), name);
            }
            catch(NoNameFound &err){
                cout << err.errorMessage() << " Try again!" << endl;
                continue;
            }
            while(1){
                cout << "\nInsert your code(! to cancel): " << flush;
                getline(cin,code);
                if(code == "!") break;
                else if(code == t->getCode()){
                    user_id = code;
                    return true;
                }
                else cout << "\nWrong Code! Try again!" << endl;
            }
        }
        else if(type == "S"){
            Student* s;
            try{
                s = SearchVec(college.getStudents(), name);
            }
            catch(NoNameFound &err){
                cout << err.errorMessage() << " Try again!" << endl;
                continue;
            }
            while(1){
                cout << "\nInsert your code(! to cancel): " << flush;
                getline(cin,code);
                if(code == "!") break;
                else if(code == s->getCode()){
                    user_id = code;
                    return true;
                }
                else cout << "\nWrong Code! Try again!" << endl;
            }
        }
    }
}

//////////////////////

int Log_In(College& college){
    int i;
    while(1){
        cout << "0:   CONTINUE AS VISITOR" << endl;
        cout << "1:   LOG IN AS MEMBER" << endl;
        cout << "2:   LOG IN AS ADMIN" << endl;
        cout << "3:   PREVIOUS MENU" << endl;
        i = Nav(0,3);
        switch(i){
            case 0:
                break;
            case 1:
                if(!Member_LogIn(college)) continue;
                break;
            case 2:
                if(!Admin_LogIn(college)) continue;
                break;
            case 3:
                break;
        }
        return i;
    }
}

//////////////////////

int main() {
    while(1){
        College college;
        string file;
        switch(Main_Menu()){
            case 0:
                New_College(college);
                access = 2;
                break;
            case 1:
                file = Choose_Colleges();
                if(file == "BACK") {
                    access = 3;
                    break;
                }
                readFile(college,file);
                access = Log_In(college);
                break;
            case 2:
                return 0;
            default:
                return -1;
        }
        switch(access){
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
