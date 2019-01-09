/*
 * People.h
 *
 *  Created on: Oct 17, 2018
 *
 */

#ifndef PEOPLE_H_
#define PEOPLE_H_

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <time.h>

//////////////////////
/** @brief Type of access */
extern int access;

using namespace std;
//////////////////////

//////PROTOTYPES//////
class College;
class Course;
class Uc;
class EmployeePtr;


int Nav(int bottom, int top);
/**
 * @brief Checks if the string inputed has a number when it is not supposed to
 * @param s String to be analyzed
 * @return Holds true if the string is correct
 */
bool hasNoNumber(std::string s);
/** @brief Category of the teacher*/
enum Cat {Default, Aux, Reg, CourseDir, DepDir};
/**
 * @brief Gets the current string
 * @param cat Enum to be used
 * @return Returns the string corresponding to the enum
 */
string CatString(Cat &cat);

//////////////////////
/**
 * @brief formated date string for better use
 */
struct date {
	unsigned int day, month, year;
    string format;
    date(unsigned int d, unsigned int m, unsigned int y){
        day = d;
        month = m;
        year = y;
        format = to_string(day) + "/" + to_string(month) + "/" + to_string(year);
    }

    bool operator< (date bd){ //newest date is smallest
        if(year != bd.year) return (year > bd.year);
        else if(month != bd.month) return (month > bd.month);
        else return (day > bd.day);
    }
};
//////////////////////


/**@brief People class */
class People {
	/**@brief name and address of the Person*/
	string name, address;
	/**@brief phone number of the Person*/
	unsigned int phone;
	/**@brief code of the Person*/
    string code;
    /**@brief birthday of the Person*/
	date* birthday;
public:
	/**
	 * @brief People constructor
	 * @param name name of the Person
	 * @param address address of the Person
	 * @param birthday birthday of the Person
	 * @param phone phone of the Person
	 * @param cod code of the Person
	 */
	People(string name, string address, date& birthday, unsigned int phone,string cod);
	//People(string name, string address, unsigned int phone,string cod);
	/**
	 * @brief Default People constructor
	 */
    People() = default;
    /**
     * @brief People destructor
     */
    ~People(){delete birthday;}
	/**
	* @brief Virtual function to add a Person to college
	* @param college College to which the person will be added
	*/
    virtual void addPerson(College &college);
	/**
	 * @brief Virtual function that will be used for particular informations of its derivatives
	 */
    virtual int Special_Info() = 0;
    /**
     * @brief Shows all the information of a given Person
     */
    virtual void showInfo();
    /**
     * @brief Allows the user to modify the information of a given Person
     * @return
     */
    virtual void editInfo(College &college); //Returns number of parameters
    /**
     * @brief Changes the name of the given Person
     * @param newName New name of a given Person
     */
    void setName(string newName);
    /**
     * @brief Gets the name of the Person
     * @return String containing the name of the Person
     */
    string getName() const;
    /**
     * @brief Gets the address of a given Person
     * @return String containing the address of the Person
     */
    string getAddress();
    /**
     * @brief Changes the address of a given Person
     * @param newAddress New address of the Person
     */
    void setAddress(string newAddress);
    /**
     * @brief Gets the phone number of a given Person
     * @return Integer containing the phone number of the Person
     */
    int getPhone();
    /**
     * @brief Changes the phone number of a given Person
     * @param newPhone New phone of the Person
     */
    void setPhone(int newPhone);
    /**
     * @brief Gets the code of a given Person
     * @return String Containing the code of the Person
     */
    string getCode();
    /**
     * @brief Changes the code of a given Person
     * @param newCod New code of the Person
     */
    virtual void setCode(string newCod);
    /**
     * @brief Gets the birthday of a given Person
     * @return Struct containing the birthday of the person
     */
    date* getDate() const;
	/**
	* @brief Virtual function to write info on os
	* @param os
	*/
    virtual void write(ostream& os);
	/**
	* @brief Sets birthday to given date
	* @param d1 Given date
	*/
    void setDate(date* d1){ birthday = d1;}
	/**
	* @brief Inserts name from user input
	*/
    void InsertName();
	/**
	* @brief Address name from user input
	*/
    void InsertAddress();
	/**
	* @brief Phone Number name from user input
	*/
    void InsertPhone();
	/**
	* @brief Inserts Birthday from user input
	*/
    void InsertBirthday();
};


/**@brief Student class,  inherits the public function from the class People*/
class Student : public People{
    string course_string; //Used when reading file to store info of inexistent course
	/** @brief Pointer to the current Course the Student is in*/
	Course* course;
	/**@brief College year the given Student is in*/
	int year;  //year enrolled in
	/** @brief Map that hold the UCs and its grades of a given Student */
	map <Uc*, float> subjects; //In this map the Key is the subject and the float value corresponds to the grade of the student on that particular subject;
    /**@brief Money student has been attributed */
    unsigned int bolsa;
    /**@brief Final Student's grade */
    unsigned int average;
public:
	/**
	 * @brief Student Constructor
	 * @param name Name of the Student
	 * @param address Address of the Student
	 * @param birthday Date of birthday of the Student
	 * @param phone Phone Number of the Student
	 * @param cod Code of the Student
	 * @param course Course the Student is in
	 */
	Student(string name, string address, date birthday, unsigned int phone, string cod, string course);
    /**
	 * @brief counter used to know how many students have been created
	 */
    static int student_count;
	/**
	 * @brief Default Student constructor
	 */
    Student() = default;
	/**
	 * @brief People destructor
	 */
    ~Student();
	/**
	* @brief Adds Student to college
	* @param college
	*/
    void addPerson(College &college);
	/**
	* @brief prints a menu entry on screen
	* @return special info access menu number
	*/
    int Special_Info();
    /**
     * @brief Shows all the information of a given Student
     */
    void showInfo();
    /**
     * @brief Gets the course a given Student is taking
     * @return A Object of type Course
     */
	Course* getCourse();
	/**
	 * @brief Gets the grades and UCs of a given Student
	 * @return Map containing the grades and UCs of the Student
	 */
    map <Uc*, float>* getGrades();
    /**
     * @brief Gets the name of the Course the Student is in
     * @return String with the name of the course
     */
	string getCourseName() const;
	/**
	 * @brief Changes the Course
	 * @param cs Course to change to
	 */
	void setCourse(Course* cs) { course = cs; }
	/**
	 * @brief Adds to the map a new UC and the Students grade in it
	 * @param uc Grade to be added to the UC
	 * @param grade Grade of the Student in the UC
	 */
	void addUCGrade(Uc* uc, float grade);
	/**
	 * @brief Removes from the map a UC and the grade the Student had
	 * @param name Name of the UC
	 * @return Returns whether it could remove or not
	 */
	bool removeFromMap(string name);
	/**
	 * @brief Changes the grade of a UC in the map
	 * @param uc UC whose grade is going to be changed
	 * @param grade New grade for the UC
	 */
	bool changeGrade(Uc* uc, float grade);
	/**
	 * @brief Shows a UC and its grade
	 * @param name Name of the UC meant to show
	 */
	void showUCGrade(string name);
	/**
	 * @brief Shows the map with the UCs and grades of a given Student
	 */
	void showAllGrades();
	/**
	* @brief Edits Student info menu
	*/
    void editInfo(College &college);
    /**
     * @brief Prints student info on os
     * @param os
     * @param student
     * @return
     */
    friend ostream& operator<< (ostream& os, Student &student);
	/**
	* @brief Writes student info to os
	* @param os
	*/
    void write(ostream& os);
	/**
	* @brief Menu to choose course from college courses
	* @param college
	*/
    void ChooseCourse(College &college);
	/**
	* @brief sets student year to newYear
	* @param newYear
	*/
    void setYear(int newYear){ year = newYear; }
	/**
	* @brief Returns student year
	*/
    int getYear(){return year; }
	/**
	* @brief Sets course string to string parameter(used when reading files)
	* @param name Name of course
	*/
    void setCourseString(string name){course_string = name;}
	/**
	* @brief returns course_string
	*/
    string getCourseString() {return course_string;}
	/**
	* @brief Inserts year from user input
	*/
    void InsertYear();
	/**
	* @brief Inserts UC from user input
	*/
	void InsertUC();
    /**
     * @brief This function is used to compare students in the priority_queue
     * @param st Other student
     * @return true if student is less than the other
     */
    bool Queue_Compare(const Student & st);
    /**
     * @brief This function calculates de average grade of each student
     */
    void Calculate_Average();
    /**
     * @brief This function adds a value to the students scholarship
     * @param value calue to add
     */
    void Add_Funds(unsigned int value);
    /**
     * @brief This function takes money from the students scholarship
     * @param value how much money will be taken
     */
    void Pay_Semester(unsigned int value);
    /**
     * @brief Updates student count
     * @param newCod count to be updated
     */
    void setCode(string newCod);
    /**
     * @brief used to create student when reading from file
     * @param value value of students scholarship
     */
    void setBolsa(unsigned int value) { bolsa = value; };
};


/**@brief Employee class, inherits the public functions of the Class People*/
class Employee : public People{
	/**@brief Salary of a given Employee*/
	float salary;
	/** @brief NIF of a given Employee*/
	unsigned int nif;
	bool working;
public:
	/**
	 * @brief constructor of Employee
	 * @param name Name of the Employee
	 * @param address Address of the Employee
	 * @param birthday Birthday of the Employee
	 * @param phone Phone number of the Employee
	 * @param cod Code of the Employee
	 * @param salary Salary of the Employee
	 * @param nif NIF of a Employee
	 * @param working Employment status of the Employee
	 */
	Employee(string name, string address, date birthday, unsigned int phone, string cod, float salary, unsigned int nif, bool working);
	/**
	 * @brief Employee default constructor
	 */
    Employee() = default;
    /**
     * @brief Friend class of employee
     */
    friend class EmployeePtr;
	/**
	* @brief  adds employee to college
	* @param college
	*/
    void addPerson(College &college);
	/**
	* @brief Prints special info on screen
	* @return returns index to access menu
	*/
	int Special_Info();
	/**
	 * @brief Gets the Salary of the given Employee
	 * @return Float containing the salary of the Employee
	 */
	float getSalary();
	/**
	 * @brief Changes the salary of the given Employee
	 * @param salary New salary of the Employee
	 */
	void setSalary(float salary);
	/**
	 * @brief Gets the NIF of a given Employee
	 * @return Unsigned int containing the NIF of the given Employee
	 */
	unsigned int getNIF();
	/**
	 * @brief Changes the NIF of a given Employee
	 * @param nif New NIF of a given Employee
	 */
	void setNIF(unsigned int nif);
	/**
	 * @brief Gets the Working state of the Employee
	 * @return Working state of the Employee
	 */
	bool getWorking();
	/**
	 * @brief Changes the Working state of the Employee
	 * @param working New Working state of the Employee
	 */
	void setWorking(bool working);
	/**
	* @brief writes employee info to os
	* @param os
	*/
    void write(ostream& os);
	/**
	* @brief open edit info menu for employee
	*/
    void editInfo(College &college);
	/**
	* @brief Inserts salary from user input
	*/
    void InsertSalary();
	/**
	* @brief Inserts NIF from user input
	*/
    void InsertNif();
};


/**@brief Teacher Class, inherits all the public functions from Employee*/
class Teacher : public Employee{
	/** @brief Category of the teacher*/
    enum Cat category;
	/**@brief vector with the UCs taught by the Teacher */
	vector <Uc*> subjects;  //subjects taught by the teacher
public:
	/**
	 * @brief constructor of Teacher
	 * @param name Name of the Teacher
	 * @param address Address of the Teacher
	 * @param birthday Birthday of the Teacher
	 * @param phone Phone number of the Teacher
	 * @param cod Code of the Teacher
	 * @param salary Salary of the Teacher
	 * @param nif NIF of the teacher
	 * @param category Category of the Teacher
	 * @param subjects Subjects taught by the Teacher
	 * @param working Employment status of the Teacher
	 */
	Teacher(string name, string address, date birthday, unsigned int phone, string cod, float salary, unsigned int nif, bool working, Cat category, vector <Uc *> subjects);
	 /**
	  * @brief Teacher default constructor
	  */
    Teacher() = default;
    /**
     * @brief Teacher destructor
     */
    ~Teacher();
    /**
     * @brief Friend class of EmployeePtr
     */
	friend class EmployeePtr;
	/**
	* @brief Adds Person to college
	* @param college
	*/
    void addPerson(College &college);
	/**
	 * @brief shows all information of a given Teacher
	 */
    void showInfo();
    /**
     * Gets the Category of a given Teacher
     * @return String containing the category of the Teacher
     */
	enum Cat getCategory();
	/**
	 * @brief Changes the category of a given Teacher
	 * @param cat New category of the Teacher
	 */
	void setCategory(Cat cat);
	/**
	 * @brief Gets the UCs that are taught by the given Teacher
	 * @return Vector with the UCs taught by the Teacher
	 */
	vector<Uc*>& getSubjects();
	/**
	 * @brief Adds a subject to the vector of subjects taught by the Teacher
	 * @param uc New subject taught by the Teacher
	 */
	void addSubject(Uc* uc); //for now it just adds a given UC
	/**
	 * @brief counts teachers created
	 */
    static int teacher_count;
	/**
	* @brief Prints teacher info on os
	* @param os
	* @param teacher
	*/
    friend ostream& operator<< (ostream& os, Teacher &teacher);
	/**
	* @brief Writes teacher info to os
	* @param os
	*/
    void write(ostream& os);
	/**
	* @brief Updates teacher category
	* @param cat Category enumerator
	*/
    void UpdateCat(Cat cat);
	/**
	* @brief Enters edit info menu for teacher
	* @param college
	*/
    void editInfo(College &college);
	/**
	* @brief Menu for choosing teacher's UCs
	* @param college
	*/
    void ChooseTeacherUCs(College &college);
	/**
	* @brief Inserts UC from user input
	*/
    bool InsertTeacherUc(College &college);
	/**
	* @brief Removes UC from teacher UC vector
	* @param n Position of UC in vector
	*/
    void RemoveTeacherUc(int n);
    /**
     * @brief Updates teacher count
     * @param newCod count to be updated
     */
    void setCode(string newCod);
};


/**@brief Staff class, inherits all the public functions from class Employee*/
class Staff : public Employee{
	/** @brief Work area of a given Staff member*/
	string work_area;
public:
	/**
	 * @brief constructor of Staff
	 * @param name name of the Staff member
	 * @param adress Address of the Staff member
	 * @param birthday Birthday of the Staff member
	 * @param phone Phone number of the Staff member
	 * @param cod Code of the Staff member
	 * @param salary Salary of the Staff member
	 * @param nif NIF of the Staff member
	 * @param work_area Work area of the Staff member
	 * @param working Employment status of the Staff member
	 */
	Staff(string name, string adress, date birthday, unsigned int phone, string cod, float salary, unsigned int nif, bool working, string work_area);
	/**
	 * @brief Staff default constructor
	 */
    Staff() = default;
    /**
     * @brief Friend class of EmployeePtr
     */
    friend class EmployeePtr;
	/**
	* @brief Adds person to college
	* @param college
	*/
    void addPerson(College &college);
	/**
	 * @brief shows all the informations of a given Staff member
	 */
    void showInfo();
    /**
     * @brief Gets the work area of a given Staff member
     * @return String with the work area of the Staff member
     */
	string getWorkArea();
	/**
	 * @brief Changes the work area of a given Staff member
	 * @param work_area New Work area of the Staff member
	 */
	void setWorkArea(string work_area);
	/**
	 * @brief Counts number of staff members
	 */
    static int staff_count;
    /**
     * @brief Prints staff info on os
     * @param os
     * @param staff
     * @return
     */
    friend ostream& operator<< (ostream& os, Staff &staff);
	/**
	* @brief Writes staff info on os
	* @param os
	*/
    void write(ostream& os);
	/**
	* @brief Edits Staff info in menu
	*/
    void editInfo(College &college);
	/**
	* @brief Inserts work area from user input
	*/
    void InsertWorkArea();
    /**
     * @brief Updates staff count
     * @param newCod count to be updated
     */
    void setCode(string newCod);
};

/** @brief EmployeePtr class, with pointers to Staff and Teacher*/
class EmployeePtr
{
	/** @brief Pointer to a Staff member*/
	Staff* staff_table;
	/** @brief Pointer to a Teacher*/
	Teacher* teacher_table;
	/** @brief 0 for teacher, 1 for staff member*/
	int type; /* 0 for teacher, 1 for staff */
public:
	/**
	 * @brief Teacher* Constructor
	 * @param teacher_table Pointer to a Teacher
	 */
	EmployeePtr(Teacher* teacher_table);
	/**
	 * @brief Staff* Constructor
	 * @param staff_table Pointer to a Staff
	 */
	EmployeePtr(Staff* staff_table);
	/**
	 * @brief Gets the private member Teacher*
	 * @return Private member Teacher*
	 */
	Teacher* getTeacher();
	/**
	 * @brief Gets the private member Staff*
	 * @return Private member Staff*
	 */
	Staff* getStaff();
	/**
	 * @brief Gets the Code of the Employee
	 * @return Code of the Employee
	 */
	string getCode() const;
	/**
	 * @brief  Gets the Name of the Employee
	 * @return Name of the Employee
	 */
	string getName() const;
	/**
	 * @brief Gets the Working state of the Employee
	 * @return Working state of the Employee
	 */
	bool getWorkingState() const;
	/**
	 * @brief Changes the Working state of the Employee
	 * @param working New Working state of the Employee
	 */
	void setWorkingState(bool working);
};

#endif /* PEOPLE_H_ */
