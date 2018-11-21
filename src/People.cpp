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
    InsertName();

    cout << "\nInsert Address: " << flush;
    InsertAddress();

    cout << "\nInsert Phone Number (9-digit): " << flush;
    InsertPhone();

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

void People::InsertName(){
    getline(cin, name);
    while(!hasNoNumber(name))
    {
        cout << "Invalid name, try again" << endl;
        getline(cin, name);
    }
}

void People::InsertAddress() {
    getline(cin, address);
}

void People::InsertPhone() {
    cin >> phone;
    while(cin.fail() || to_string(phone).size() != 9)
    {
        cout << "Invalid phone number, try again: "<< endl;
        cin.clear();
        cin.ignore(100, '\n');
        cin >> phone;
    }
}

void People::InsertBirthday(){
    birthday = readDate();
}

void People::editInfo(College &college) {
    showInfo();
    cout << "Which parameter do you want to edit?" << endl;
    cout << "0:   NAME" << endl;
    cout << "1:   ADDRESS" << endl;
    cout << "2:   PHONE" << endl;
    cout << "3:   BIRTHDAY" << endl;
}

void People::showInfo() {
    cout << "\n|-----------------------------------------" << endl;
    cout << "|      " << name << endl;
    cout << "| Address: " << address << endl;
    cout << "| Code: " << code << " Phone: " << phone << endl;
    cout << "| Birthday: " << birthday->format << endl;

}

void People::write(ostream &os) {
    os << name << "|" << address << "|" << phone << "|" << code << "|" << birthday->format << "|";
}

//////STUDENT//////

Student::Student(string name, string address, date birthday, unsigned int phone, string cod, string course, map <Uc*, float> subjects)
: People(name, address, birthday, phone, cod){
	course_string = course;
	year = 0;
    student_count++;
}

void Student::ChooseCourse(College &college) {
    if(college.getCourses().size() == 0) throw NoCourses();
    Print_Vec(college.getCourses());
    course = college.getCourses().at(Nav(0,college.getCourses().size()-1));
}

void Student::InsertYear() {
    cin >> year;
    while(cin.fail() || year > 5 || year < 0)
    {
        cout << "Invalid year, try again: "<< endl;
        cin.clear();
        cin.ignore(100, '\n');
        cin >> year;
    }
    cin.clear();
    cin.ignore(100, '\n');
}

void Student::addPerson(College &college) {
    People::addPerson(college);
    string uc_name;
    Uc* uc;
    float grade;
    string code = "0" + to_string(current_year) + to_string(Student::student_count);  //student id is assigned
    setCode(code);

    cout << "\nChoose Student's Course:" << endl;  //Needs exception in case there are no Courses Created
    ChooseCourse(college);

    cout << "\nInsert Student's Year: " << flush;
    InsertYear();

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
                catch(NoNameFound &err){
                    cout << err.errorMessage() << " " << "Try again:" << endl;
                    continue;
                }
                if(subjects.find(uc) != subjects.end()){
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

void Student::editInfo(College &college){
    while(1){
        People::editInfo(college);
        cout << "4:   COURSE" << endl;
        cout << "5:   YEAR" << endl;
        cout << "6:   PREVIOUS" << endl;
        switch(Nav(0,6)){
            case 0:
                cout << "Insert new Name: " << flush;
                InsertName();
                break;
            case 1:
                cout << "Insert new Address: " << flush;
                InsertAddress();
                break;
            case 2:
                cout << "Insert new Phone Number: " << flush;
                InsertPhone();
                break;
            case 3:
                InsertBirthday();
                break;
            case 4:
                cout << "Choose new Course: " << endl;
                try{
                    ChooseCourse(college);
                }
                catch(NoCourses &err){
                    cout << "There are no courses available!" << endl;
                    continue;
                }
                break;
            case 5:
                cout << "Insert new Student Year: " << flush;
                InsertYear();
                break;
            case 6:
                return;
        }
    }
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

void Student::write(ostream &os) {
    People::write(os);
    os << course->getName() << "|" << year << "|[";
    for(auto it = subjects.begin(); it != subjects.end(); it++){
        os << "(" << it->first->getName() << "," << it->second << ")";
    }
    os << "]|" << endl;
}

//////EMPLOYEE//////

Employee::Employee(string name, string address, date birthday, unsigned int phone, string cod, float salary, unsigned int nif)
: People(name, address, birthday, phone, cod){
	this->salary = salary;
	this->nif = nif;
}

void Employee::addPerson(College &college){
    cout << "\nInsert Employee's Salary: " << flush;
    InsertSalary();
    cout << "\nInsert Employee's NIF: " << flush;
    InsertNif();
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

void Employee::write(ostream& os){
    os << to_string(salary) << "|" << to_string(nif) << "|";
}

void Employee::editInfo(College &college){
    cout << "4:   PHONE" << endl;
    cout << "5:   BIRTHDAY" << endl;
}

void Employee::InsertSalary() {
    cin >> salary;
    while(cin.fail()){
        cout << "Invalid Salary! Try again: " << flush;
        cin.clear();
        cin.ignore(1000,'\n');
        cin >> salary;
    }
    cin.clear();
    cin.ignore(1000,'\n');
}

void Employee::InsertNif() {
    cin >> nif;
    while(cin.fail() || to_string(nif).length() != 9){
        cout << "Invalid Nif(needs 9 digits)! Try again: " << flush;
        cin.clear();
        cin.ignore(1000,'\n');
        cin >> nif;
    }
    cin.clear();
    cin.ignore(1000,'\n');
}

//////TEACHER//////

Teacher::Teacher(string name, string address, date birthday, unsigned int phone, string cod, float salary, unsigned int nif, Cat category, vector<Uc *> subjects)
: Employee(name, address, birthday, phone, cod, salary, nif){
	this->category = category;
	this->subjects = subjects;
}

Teacher::~Teacher()
{
    for(size_t i = 0; i < subjects.size(); i++){
        remove(subjects.at(i)->getTeachers(),getName());
    }
}

bool Teacher::InsertTeacherUc(College &college) {
    string uc_name;
    Uc* uc;
    cout << "\nInsert Teacher's Ucs(? - list/ ! - done): " << flush;
    getline(cin, uc_name);
    if(uc_name == "!") return true;
    else if(uc_name == "?") {
        Print_Vec(college.getUCs());
    }
    else {
        try{
            uc = (SearchVec(college.getUCs(),uc_name));
        }
        catch(NoNameFound &err){
            cout << err.errorMessage() << " " << "Try again:" << endl;
            return false;
        }
        subjects.push_back(uc);
    }
    return false;
}

void Teacher::RemoveTeacherUc(int n){
    if(!remove(subjects.at(n)->getTeachers(),getName())){
        cout << "Couldn't Remove Teacher from Uc's Teacher list" << endl;
        return;
    }
    if(!remove(subjects,subjects.at(n)->getName())) cout << "Couldn't Remove Uc from Teacher's list" << endl;
    else cout << "Uc successfully removed!" << endl;
}

void Teacher::ChooseTeacherUCs(College &college){
    while(1){
        Uc* uc;
        string uc_name;
        cout << "\nChoose Teacher's Uc: " << endl;
        Print_Vec(subjects);
        int n = subjects.size();
        cout << n << ":   ADD UC" << endl;
        cout << ++n << ":   PREVIOUS" << endl;
        int i = Nav(0,n);
        if(i == n) return;
        else if(i == n-1) while(!InsertTeacherUc(college));
        else{
            string answer;
            cout << "Are you sure you want to Remove this Uc from Teacher?(Y - yes/N - no)" << endl;
            cin >> answer;
            while(cin.fail() || (answer != "Y" && answer != "N")){
                cout << "Invalid answer, try again: " << flush;
                cin >> answer;
                cin.clear();
                cin.ignore(100,'\n');
            }
            cin.clear();
            cin.ignore(100,'\n');
            if(answer == "Y"){
                RemoveTeacherUc(n);
            }
            else continue;
        }
    }
}

void Teacher::editInfo(College &college) {
    while(1) {
        People::editInfo(college);
        Employee::editInfo(college);
        cout << "6:   SUBJECTS" << endl;
        cout << "7:   PREVIOUS" << endl;
        switch (Nav(0, 7)) {
            case 0:
                cout << "Insert new Name: " << flush;
                InsertName();
                break;
            case 1:
                cout << "Insert new Address: " << flush;
                InsertAddress();
                break;
            case 2:
                cout << "Insert new Phone Number: " << flush;
                InsertPhone();
                break;
            case 3:
                InsertBirthday();
                break;
            case 4:
                cout << "Insert new salary: " << flush;
                InsertSalary();
            case 5:
                cout << "Insert new NIF: " << flush;
                InsertNif();
            case 6:
                ChooseTeacherUCs(college);
                break;
            case 7:
                return;
        }
    }
}

void Teacher::addPerson(College &college){
    People::addPerson(college);
    Employee::addPerson(college);
    string code = "1" + to_string(current_year) + to_string(Teacher::teacher_count);  //teacher id is assigned
    setCode(code);
    while(!InsertTeacherUc(college));
    if(!subjects.empty()) category = Aux;
    college.addTeacher(this);
}

enum Cat Teacher::getCategory()
{
	return category;
}

void Teacher::setCategory(Cat &cat)
{
    category = cat;
}

vector<Uc*> Teacher::getSubjects()
{
	return subjects;
}

void Teacher::addSubject(Uc* uc)
{
	subjects.push_back(uc);
}

void Teacher::UpdateCat(Cat cat){
    if(cat > category) category = cat;
}

void Teacher::showInfo()
{
	People::showInfo();
	cout << "| Category: " << category << endl;
	cout << "|-----------------------------------------" << endl;
}

void Teacher::write(ostream &os) {
    People::write(os);
    Employee::write(os);
    os << category << "|" << endl;
}

//////STAFF//////

Staff::Staff(string name, string address, date birthday, unsigned int phone, string cod, float salary, unsigned int nif, string work_area)
: Employee(name, address, birthday, phone, cod, salary, nif){
	this->work_area = work_area;
}

void Staff::addPerson(College &college){
    People::addPerson(college);
    Employee::addPerson(college);
    string code = "2" + to_string(current_year) + to_string(Staff::staff_count);  //staff id is assigned
    setCode(code);
    cout << "\nInsert Staff member's working area: " << flush;
    getline(cin,work_area);
    college.addStaff(this);
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

void Staff::write(ostream& os){
    People::write(os);
    Employee::write(os);
    os << work_area << "|" << endl;
}

void Staff::InsertWorkArea(){
    getline(cin,work_area);
    while(!hasNoNumber(work_area)){
        cout << "Invalid Work Area" << endl;
        getline(cin,work_area);
    }
}

void Staff::editInfo(College &college){
    while(1) {
        People::editInfo(college);
        Employee::editInfo(college);
        cout << "6:   WORK AREA" << endl;
        cout << "7:   PREVIOUS" << endl;
        switch (Nav(0, 7)) {
            case 0:
                cout << "Insert new Name: " << flush;
                InsertName();
                break;
            case 1:
                cout << "Insert new Address: " << flush;
                InsertAddress();
                break;
            case 2:
                cout << "Insert new Phone Number: " << flush;
                InsertPhone();
                break;
            case 3:
                InsertBirthday();
                break;
            case 4:
                cout << "Insert new salary: " << flush;
                InsertSalary();
            case 5:
                cout << "Insert new NIF: " << flush;
                InsertNif();
            case 6:
                cout << "Insert new WorkArea: " << flush;
                InsertWorkArea();
                break;
            case 7:
                return;
        }
    }
}

////FRIEND FUNCTIONS////

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

string CatString(Cat &cat){
    switch(cat){
        case Aux:
            return "Auxiliar Professor";
        case Reg:
            return "Regent";
        case DepDir:
            return "Deoartment Director";
        case CourseDir:
            return "Course Director";
        default:
            return "!Unassigned!";
    }
}

ostream& operator<< (ostream& os, Cat &cat){
    os << CatString(cat);
    return os;
}
