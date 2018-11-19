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

//////PROTOTYPES//////
class College;
class Course;
class Uc;
int Nav(int bottom, int top);
bool hasNoNumber(std::string s);
//////////////////////

using namespace std;

//////////////////////

struct date {  //formated date string for better use
	unsigned int day, month, year;
    string format;
    date(unsigned int d, unsigned int m, unsigned int y){
        day = d;
        month = m;
        year = y;
        format = to_string(day) + "/" + to_string(month) + "/" + to_string(year);
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

    People() = default;

    ~People(){delete birthday;}

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
    virtual int editInfo(); //Returns number of parameters
    /**
     * @brief
     * @param n
     */
    virtual void Set(int n);
    /**
     * @brief Changes the name of the given Person
     * @param newName New name of a given Person
     */
    void setName(string newName);
    /**
     * @brief Gets the name of the Person
     * @return String containing the name of the Person
     */
    string getName();
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
    void setCode(string newCod);
    /**
     * @brief Gets the birthday of a given Person
     * @return Struct containing the birthday of the person
     */
    date* getDate();

    /**
     * @brief Virtual class destructor
     */
	//virtual ~People();
    virtual void write(ostream& os);
};
/**@brief Student class,  inherits the public function from the class People*/
class Student : public People{
    string course_string; //Used when reading file to store info of inexistent course
	/** @brief Pointer to the current Course the Student is in*/
	Course* course;
	/**@brief College year the given Student is in*/
	int year;  //year enrolled in
	/** @brief Map that hold the Ucs and its grades of a given Student */
	map <Uc*, float> subjects; //In this map the Key is the subject and the float value corresponds to the grade of the student on that particular subject;
public:
	/**
	 * @brief Student Constructor
	 * @param name Name of the Student
	 * @param address Address of the Student
	 * @param birthday Date of birthday of the Student
	 * @param phone Phone Number of the Student
	 * @param cod Code of the Student
	 * @param course Course the Student is in
	 * @param subjects Subjects the Student is taking
	 */
	Student(string name, string address, date birthday, unsigned int phone, string cod, string course, map <Uc*, float> subjects);

    Student() = default;

    ~Student(){delete course;}

    void addPerson(College &college);

	/**
	 * @brief
	 * @return
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
	 * @brief Gets the grades and Ucs of a given Student
	 * @return Map containing the grades and Ucs of the Student
	 */
    map <Uc*, float>* getGrades();
    /**
     * @brief Gets the name of the Course the Student is in
     * @return String with the name of the course
     */
	string getCourseName();
	/**
	 * @brief Adds to the map a new Uc and the Students grade in it
	 * @param name Name of the Uc
	 * @param grade Grade of the Student in the Uc
	 */
	void addUCGrade(Uc* uc, float grade);
	/**
	 * @brief Removes from the map a Uc and the grade the Student had
	 * @param name Name of the Uc
	 */
	void removeFromMap(string name);
	/**
	 * @brief Changes the grade of a Uc in the map
	 * @param name Name of the Uc with the new grade
	 * @param grade New grade for the Uc
	 */
	void changeGrade(string name, int grade);
	/**
	 * Shows a Uc and its grade
	 * @param name Name of the Uc meant to show
	 */
	void showUCGrade(string name);
	/**
	 * @brief Shows the map with the Ucs and grades of a given Student
	 */
	void showAllGrades();
	/**
	 * @brief
	 */
    static int student_count;

    friend ostream& operator<< (ostream& os, Student &student);

    void write(ostream& os);
};


/**@brief Employee class, inherits the public functions of the Class People*/
class Employee : public People{
	/**@brief Salary of a given Employee*/
	float salary;
	/**Nif of a given Employee*/
	unsigned int nif;
public:
	/**
	 * @brief constructor of Employee
	 * @param name Name of the Employee
	 * @param address Address of the Employee
	 * @param birthday Birthday of the Employee
	 * @param phone Phone number of the Employee
	 * @param cod Code of the Employee
	 * @param salary Salary of the Employee
	 * @param nif Nif of a Employee
	 */
	Employee(string name, string address, date birthday, unsigned int phone, string cod, float salary, unsigned int nif);

    Employee() = default;

    void addPerson(College &college);

	/**
	 * @brief
	 * @return
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
	 * @brief Gets the Nif of a given Employee
	 * @return Unsigned int containing the Nif of the given Employee
	 */
	unsigned int getNIF();
	/**
	 * @brief Changes the Nif of a given Employee
	 * @param nif New nif of a given Employee
	 */
	void setNIF(unsigned int nif);

    void write(ostream& os);
};

enum Cat { Aux, Reg, CourseDir, DepDir};

/**@brief Teacher Class, inherits all the public functions from Employee*/
class Teacher : public Employee{
	/** @brief Category of the teacher*/
    enum Cat category;
	/**@brief vector with the Ucs taught by the Teacher */
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
	 * @param nif Nif of the teacher
	 * @param category Category of the Teacher
	 * @param subjects Subjects taught by the Teacher
	 */
	Teacher(string name, string address, date birthday, unsigned int phone, string cod, float salary, unsigned int nif, Cat category, vector <Uc *> subjects);

    Teacher() = default;

    ~Teacher();

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
	 * @param category New category of the Teacher
	 */
	void setCategory(Cat &cat);
	/**
	 * @brief Gets the Ucs that are taught by the given Teacher
	 * @return Vector with the Ucs taught by the Teacher
	 */
	vector<Uc*> getSubjects();
	/**
	 * @brief Adds a subject to the vector of subjects taught by the Teacher
	 * @param uc New subject taught by the Teacher
	 */
	void addSubject(Uc* uc); //for now it just adds a given UC

	/**
	 * @brief
	 */
    static int teacher_count;

    friend ostream& operator<< (ostream& os, Teacher &teacher);

    void write(ostream& os);

    void UpdateCat(Cat cat);

    friend string CatString(Cat &cat);

    friend ostream& operator<< (ostream& os, Cat &cat);
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
	 * @param nif Nif of the Staff member
	 * @param work_area Work area of the Staff member
	 */
	Staff(string name, string adress, date birthday, unsigned int phone, string cod, float salary, unsigned int nif, string work_area);

    Staff() = default;

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
	 * @brief
	 */
    static int staff_count;

    friend ostream& operator<< (ostream& os, Staff &staff);

    void write(ostream& os);
};

#endif /* PEOPLE_H_ */
