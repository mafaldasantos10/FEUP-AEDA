/*
 * People.cpp
 *
 *  Created on: Oct 17, 2018
 *
 */

#include "People.h"
#include "College.h"
#include <map>
#include <math.h>

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
/*People::People(string name, string address,unsigned int phone, string cod) {
	this->name = name;
	this->address = address;
	this->phone = phone;
	this->code = cod;
}*/

void People::addPerson(College &college) {
    cout << "Insert Name: " << flush;
    InsertName();

    cout << "\nInsert Address: " << flush;
    InsertAddress();

    cout << "\nInsert Phone Number (9-digit): " << flush;
    InsertPhone();

    birthday = readDate(); //Tests if date is written correctly
}

string People::getName() const {
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
	code = newCod;
}

date* People::getDate() const
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
    cin.clear();
    cin.ignore(100, '\n');
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

Student::Student(string name, string address, date birthday, unsigned int phone, string cod, string course)
: People(name, address, birthday, phone, cod){
	course_string = course;
	year = 0;
    student_count++;
}

/*Student::Student(string name, string address, unsigned int phone, string cod, string course) : People(name, address, phone, cod)
{
	course_string = course;
	year = 0;
    student_count++;
}*/
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

void Student::addPerson(College &college) 
{
    People::addPerson(college);
    string uc_name;
    
    //float grade;
    string code = "0" + to_string(current_year) + to_string(Student::student_count);  //student id is assigned
    setCode(code);

    cout << "\nChoose Student's Course:" << endl;
    ChooseCourse(college);

    cout << "\nInsert Student's Year: " << flush;
    InsertYear();
	InsertUC();
    Calculate_Average();
    bolsa = 0;
	student_count++;
	college.addNewStudent(this);
}

void Student::setCode(string newCod){
    string number = newCod.substr(5);
    if(stoi(number) > student_count) {
        student_count = stoi(number);
        student_count++;
    }
    People::setCode(newCod);
}

void Student::InsertUC()
{
	//Uc* uc = nullptr;
	bool end = false;
	string uc_name;
	float grade;

	while (1) {
        Uc* uc = new Uc();
		while (1) {
			cout << "\nInsert Student's UC(? - list/ ! - done): " << flush;
			getline(cin, uc_name);
			if (uc_name == "!") {
				end = true;
				break;
			}
			else if (uc_name == "?") Print_Vec(course->getUCs());
			else {
				try {
					uc = (SearchVec(course->getUCs(), uc_name));
				}
				catch (NoNameFound &err) {
					cout << err.errorMessage() << " " << "Try again:" << endl;
					continue;
				}
				if (subjects.find(uc) != subjects.end()) {
					cout << "Student already enrolled in this course, try again: " << endl;
					continue;
				}
				break;
			}
		}
		if (end) break;

		cout << "\nInsert Student's UC grade(-1 if not-evaluated): " << flush;
		cin >> grade;
		while (cin.fail() || grade > 20 || (grade < 0 && grade != -1))
		{
			cout << "Invalid grade, try again: " << endl;
			cin.clear();
			cin.ignore(100, '\n');
			cin >> grade;
		}
		cin.clear();
		cin.ignore(100, '\n');
		addUCGrade(uc, grade);
		uc->addStudent(this);
	}
}

void Student::editInfo(College &college) {
	int n;
	if (access == 2) n = 6;
	else n = 4;
	while (1) {
		People::editInfo(college);
		if (access == 2) cout << "4:   COURSE" << endl;
		if (access == 2) cout << "5:   YEAR" << endl;
		cout << n << ":   PREVIOUS" << endl;
		int i = Nav(0, n);
		switch (i) {
		case 0:
			cout << "Insert new Name: " << flush;
			InsertName();
			college.setNameBST(getCode(), getName());
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
			setDate(readDate());
			break;
		default:
			break;
		}
		if (i == n) return;
		else if (i == 4) {
			cout << "Choose new Course: " << endl;
			try {
				ChooseCourse(college);
			}
			catch (NoCourses &err) {
				cout << "There are no courses available!" << endl;
				continue;
			}
			college.setCourse(getCode(), getCourse());
		}
		else if (i == 5) {
			cout << "Insert new Student Year: " << flush;
			InsertYear();
		}
	}
}

void Student::Calculate_Average(){
    unsigned int total = 0, number = 0;
    for(auto it = subjects.begin(); it != subjects.end(); it++)
    {
        if(it->second >= 0)
        {
            total += it->second;
            number++;
        }
    }
    if(number == 0) return;
    average = round(total/number);
}

void Student::Add_Funds(unsigned int value){
    bolsa += value;
}

void Student::Pay_Semester(unsigned int value){
    if((int) (bolsa - value) > 0) bolsa -= value;
    else bolsa = 0;
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

string Student::getCourseName() const
{
	return course->getEngName();
}

void Student::showInfo(){
    People::showInfo();
    string average_grade;
    if(subjects.empty()) average_grade = "!None Available!";
    else average_grade = to_string(average);
	cout << "| Course: " << getCourseName() << endl;
    cout << "| Year: " << year << endl;
    cout << "| Average: " << average_grade << endl;
    cout << "| Scholarship: " << bolsa << endl;
	cout << "|-----------------------------------------" << endl;
}

void Student::addUCGrade(Uc* uc, float grade)
{
	subjects.insert(pair <Uc*, float> (uc, grade));
}

bool Student::removeFromMap(string name)
{
	Uc* uc = nullptr;

	for (unsigned int i = 0; i < course->getUCs().size(); i++)
	{
		if (course->getUCs().at(i)->getName() == name)
		{
			uc = course->getUCs().at(i);
			break;
		}
	}

	if (auto it = subjects.find(uc) != subjects.end())
	{
		subjects.erase(uc);
		return true;
	}
	else cout << "UC with name -" << name << "- was not found!" << endl;

	return false;
}

bool Student::changeGrade(Uc* uc, float grade)
{
    auto it = subjects.find(uc);
	if (it != subjects.end())
	{
		it->second = grade;
        return true;
	}
    else return false;
}

void Student::showUCGrade(string name)
{
	Uc* uc;

	for (unsigned int i = 0; i < course->getUCs().size(); i++)
	{
		if (course->getUCs().at(i)->getName() == name)
		{
			uc = course->getUCs().at(i);
			break;
		}
	}

	cout << "  MODULE\t\tGRADE\n";
	string s;
	int i = 0;
	for (auto it = subjects.find(uc); it != subjects.end(); it++)
	{
		if (it->second == -1) s = "NO GRADE!";
		else s = to_string(it->second);
		cout << i << ":   " << it->first->getName() << "\t" << s << endl;
		i++;
	}
}

void Student::showAllGrades()
{
    showInfo();
	cout << "\tMODULE\t\tGRADE\n";
	string s;
	int i = 0;
	for (auto it = subjects.begin(); it != subjects.end(); it++)
	{
		if (it->second == -1) s = "!NO GRADE!";
		else s = to_string(it->second);
		cout << i << ":   " << it->first->getName() << "\t\t" << s << endl;
		i++;
	}
}

void Student::write(ostream &os) {
    People::write(os);
    os << course->getName() << "|" << year << "|" << bolsa << "|" << endl;
}

bool Student::Queue_Compare(const Student & st){
    if(bolsa != st.bolsa) return (bolsa > st.bolsa);
    else if(average != st.average) return (average < st.average);
    else if(year != st.year) return (year < st.year);
    else return (getDate() > st.getDate());
}

Student::~Student() {
    for(auto it = subjects.begin(); it != subjects.end(); it++)
    {
        remove(it->first->getStudents(), getName());
    }
}

//////EMPLOYEE//////

Employee::Employee(string name, string address, date birthday, unsigned int phone, string cod, float salary, unsigned int nif, bool working)
: People(name, address, birthday, phone, cod){
	this->salary = salary;
	this->nif = nif;
	this->working = working;
}

void Employee::addPerson(College &college){
	setWorking(true);
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

bool Employee::getWorking()
{
	return working;
}

void Employee::setWorking(bool working)
{
	this->working = working;
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

Teacher::Teacher(string name, string address, date birthday, unsigned int phone, string cod, float salary, unsigned int nif, bool working, Cat category, vector<Uc *> subjects)
: Employee(name, address, birthday, phone, cod, salary, nif, working){
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
        uc->addTeacher(this);
    }
    return false;
}

void Teacher::RemoveTeacherUc(int n){
    if(!remove(subjects.at(n)->getTeachers(),getName())){
        cout << "Couldn't Remove Teacher from Uc's Teacher list" << endl;
        return;
    }
    if(!remove(subjects,subjects.at(n)->getName())) cout << "Couldn't Remove UC from Teacher's list" << endl;
    else cout << "UC successfully removed!" << endl;
}

void Teacher::ChooseTeacherUCs(College &college){
    while(1){
        //Uc* uc = new Uc;
        string uc_name;
		cout << "\nChoose Teacher's UC (click on them to remove): " << endl;
        Print_Vec(subjects);
        int n = subjects.size();
        cout << n << ":   ADD UC" << endl;
        cout << ++n << ":   PREVIOUS" << endl;
        int i = Nav(0,n);
        if(i == n) return;
        else if(i == n-1) while(!InsertTeacherUc(college));
        else{
            string answer;
            cout << "Are you sure you want to Remove this UC from Teacher?(Y - yes/N - no)" << endl;
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
                RemoveTeacherUc(i);
            }
            else continue;
        }
    }
}

void Teacher::editInfo(College &college) {
	int n;
	if (access == 2) n = 7;
	else n = 5;
	while (1) {
		People::editInfo(college);
		if (access == 2) Employee::editInfo(college);
		cout << (n - 1) << ":   SUBJECTS" << endl;
		cout << n << ":   PREVIOUS" << endl;
		int i = Nav(0, n);
		switch (i) {
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
		default:
			break;
		}
		if (access == 2) {
			switch (i) {
			case 4:
				cout << "Insert new salary: " << flush;
				InsertSalary();
				break;
			case 5:
				cout << "Insert new NIF: " << flush;
				InsertNif();
				break;
			case 6:
				ChooseTeacherUCs(college);
				break;
			case 7:
				return;
			}
		}
		else {
			switch (i) {
			case 4:
				Print_Vec(subjects);
				break;
			case 5:
				return;
			}
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
    else category = Default;
    teacher_count++;
    college.addTeacher(this);
}

enum Cat Teacher::getCategory()
{
	return category;
}

void Teacher::setCategory(Cat cat)
{
    category = cat;
}

vector<Uc*>& Teacher::getSubjects()
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
    string s = CatString(category);
	cout << "| Category: " << s << endl;
	cout << "|-----------------------------------------" << endl;
}

void Teacher::write(ostream &os) {
    People::write(os);
    Employee::write(os);
    os << category << "|" << endl;
}

void Teacher::setCode(string newCod){
    string number = newCod.substr(5);
    if(stoi(number) > teacher_count){
        teacher_count = stoi(number);
        teacher_count++;
    }
    People::setCode(newCod);
}

//////STAFF//////

Staff::Staff(string name, string address, date birthday, unsigned int phone, string cod, float salary, unsigned int nif, bool working, string work_area)
: Employee(name, address, birthday, phone, cod, salary, nif, working){
	this->work_area = work_area;
}

void Staff::addPerson(College &college){
    People::addPerson(college);
    Employee::addPerson(college);
    string code = "2" + to_string(current_year) + to_string(Staff::staff_count);  //staff id is assigned
    setCode(code);
    cout << "\nInsert Staff member's working area: " << flush;
    getline(cin,work_area);
    staff_count++;
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

void Staff::editInfo(College &college) {
	int n;
	if (access == 2) n = 7;
	else n = 4;
	while (1) {
		People::editInfo(college);
		if (access == 2) Employee::editInfo(college);
		if (access == 2) cout << "6:   WORK AREA" << endl;
		cout << n << ":   PREVIOUS" << endl;
		int i = Nav(0, n);
		if (i == n) return;
		switch (i) {
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
			break;
		case 5:
			cout << "Insert new NIF: " << flush;
			InsertNif();
			break;
		case 6:
			cout << "Insert new WorkArea: " << flush;
			InsertWorkArea();
			break;
		}
	}
}

void Staff::setCode(string newCod) {
    string number = newCod.substr(5);
    if(stoi(number) > staff_count){
        staff_count = stoi(number);
        staff_count++;
    }
    People::setCode(newCod);
}


/**
 * Class EmployeePtr
 */

EmployeePtr::EmployeePtr(Teacher* teacher_table)
{
	this->teacher_table = teacher_table;
	type = 0;
}

EmployeePtr::EmployeePtr(Staff* staff_table)
{
	this->staff_table = staff_table;
	type = 1;
}

Teacher* EmployeePtr::getTeacher()
{
	return this->teacher_table;
}

Staff* EmployeePtr::getStaff()
{
	return this->staff_table;
}

string EmployeePtr::getCode() const
{
	if (!this->type)
		return this->teacher_table->getCode();
	else
		return this->staff_table->getCode();
}

string EmployeePtr::getName() const
{
	if (!this->type)
		return this->teacher_table->getName();
	else
		return this->staff_table->getName();
}

bool EmployeePtr::getWorkingState() const
{
	if (!this->type)
		return this->teacher_table->getWorking();
	else
		return this->staff_table->getWorking();
}

void EmployeePtr::setWorkingState(bool working)
{
	if (!this->type)
		this->teacher_table->setWorking(working);
	else
		this->staff_table->setWorking(working);
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
            return "Auxiliary Professor";
        case Reg:
            return "Regent";
        case DepDir:
            return "Department Director";
        case CourseDir:
            return "Course Director";
        default:
            return "!Unassigned!";
    }
}
