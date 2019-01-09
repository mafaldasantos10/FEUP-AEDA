/*
 * College.h
 *
 *  Created on: 15/10/2018
 */

#ifndef COLLEGE_H_
#define COLLEGE_H_

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_set>
#include <queue>
#include "BST.h"
#include "People.h"


using namespace std;


//////PROTOTYPES//////
class Department;
class Course;
class Uc;
class People;
class Employee;
class Student;
class Teacher;
class Staff;
//////////////////////

/** @brief Hash Function for the placement of an Employee on the hash table */
struct EmployeePtrHash
{
	/** @brief Hash Function for the placement of an Employee on the hash table */
	int operator() (const EmployeePtr& employee) const
	{
		int v = 0;

		for (unsigned int i = 0; i < employee.getCode().size(); i++)
		{
			v = 37 * v + employee.getCode().at(i);
		}

		return v;
	}

	/** @brief Equality Function */
	bool operator() (const EmployeePtr& employee1, const EmployeePtr& employee2) const
	{
		return employee1.getCode() == employee2.getCode();
	}
};

/** @brief Hash Table */
typedef unordered_set<EmployeePtr, EmployeePtrHash, EmployeePtrHash> HashTabEmployeetPtr;

/** @brief Compare_St_Queue class */
class Compare_St_Queue
{
public:
	/**
	 * @brief Compares to students to be placed on the priority queue
	 * @param st1 Student 1
	 * @param st2 Student 2
	 * @return Return true if it should be placed in a lower position
	 */
    bool operator() (Student* st1, Student* st2)
    {
        return (*st1).Queue_Compare(*st2);
    }
};

/** @brief Student_Ptr class, with pointers to Student*/
class Student_Ptr
{
	/** @brief Pointer to Student*/
    Student* student_ptr;
public:
    /**
     * @brief Student_Ptr constructor
     * @param st Pointer to a Student
     */
    Student_Ptr(Student* st) : student_ptr(st) {}
    /**
     * @brief Organizes the BST
     * @param student To be added to the BST
     * @return Return true if it should be placed in a lower position
     */
    bool operator<(const Student_Ptr & student) const
    {
        if (student_ptr->getCourseName() == student.student_ptr->getCourseName()) {
            return (student_ptr->getName() < student.student_ptr->getName());
        }
        else return   (student_ptr->getCourseName() < student.student_ptr->getCourseName());
    }
	/**
	 * @brief Gets the private member Student*
	 * @return Private member Student*
	 */
    Student* getST() const { return student_ptr; }
};


/**
 * @brief Tests for valid input keys and returns the inputed char
 * @param bottom Last option of the menu
 * @param top First option of the menu
 * @return Returns the option
 */
int Nav(int bottom, int top);

/**
 * @brief Reads the given date in the format dd/mm/yy
 * @return Returns a date Object
 */
date* readDate();

/** @brief Current Year */
extern int current_year;


/** @brief College Class */
class College{
    /** @brief Name of the College */
    string colName;
    /** @brief To log in as an Admin */
    string admin;
    /** @brief Vector of pointers to each Department of the College */
    vector<Department*> vecDep;
    /** @brief Vector of Vectors of pointers to each Student of the College */
    vector<Student *> readst;
    /** @brief Vector of Vectors of pointers to each Teacher of the College */
    vector<Teacher *> teachers;
    /** @brief Vector of Vectors of pointers to each Staff of the College */
    vector<Staff *> staff;
    HashTabEmployeetPtr employeeTable;
    BST<Student_Ptr> studentsTree;
    /** @brief Priority_Queue that holds the students in order of eligibility for a scholarship */
    priority_queue<Student *, std::vector<Student *>, Compare_St_Queue> students_queue;
public:
    /**
     * @brief College Constructor
     * @param name Name of the College
     */
    College(string name);
    /**
     * @brief Default College Constructor
     */
    College();
    /**
     * @brief College destructor
     */
    ~College();
    /**
     * @brief Gets Teacher vector by reference
     * @return Returns the vector of Teachers by reference
     */

	//Hash Table
    /**
     * @brief Gets the vector of EmployeePtr from the HashTable
     * @return Vector of EmployeePtr
     */
	vector<EmployeePtr> getEmployees() const;
	/**
	 * @brief Adds a Teacher to the Hash Table
	 * @param teacher Teacher to be added
	 */
	void addEmployeeTable(Teacher* teacher);
	/**
	 * @brief Adds a Staff to the Hash Table
	 * @param staff Staff to be added
	 */
	void addEmployeeTable(Staff* staff);

    //Priority Queue
    /**
     * @brief Adds a student pointer to the Scholarship priority_queue
     * @param st student pointer to add
     */
    void Add_To_Queue(Student* st);
    /**
     * @brief Used to rearrange the queue whenever there is a change in a student
     * @param st student who has changed
     */
    void Rearrange_Queue(Student* st);
    /**
     * @brief Removes a student from the queue
     * @param st student to remove
     */
    void Remove_From_Queue(Student* st);
    /**
     * @brief Get the student at the top of the priority queue
     * @return Returns top student
     */
    Student* Get_Top_Student();

    /**
     * @return returns teachers vector
     */
    vector<Teacher *>& getTeachers();
	/**
	* @brief Removes Teacher from College
	* @param teacher Pointer to teacher
	*/
    void removeTeacher(Teacher* teacher);
    /**
     * @brief Deletes a teacher from Departments, Course and Ucs
     * @param name Name of the Teacher
     */
	void deleteTeachers(string name);
	/**
	 * @brief Gets a vector of pointers to a Student from the students read from the text file
     * @return Returns the vector of pointers to a Student from the students read from the text file by reference
     */
    vector<Student *>& getStudents();
	/**
	* @brief Gets Staff vector by reference
	* @return Returns the vector of Staff by reference
	*/
    vector<Staff *>& getStaff();
	/**
	* @brief Removes Staff from College
	* @param staff Pointer to Staff
	*/
    void removeStaff(Staff* staff);
    /**
     * @brief Adds teacher to College
     * @param teacher Pointer to Teacher
     */
    void addTeacher(Teacher* teacher);
	/**
	* @brief Adds staff to College
	* @param staff Pointer to Staff
	*/
    void addStaff(Staff* staff);
    /**
     * @brief Gets the name of a given College
     * @return String containing the name of the College
     */
    string getName() const;
    /**
     * @brief Changes the name of a given College
     * @param name New name of the College
     */
    void setName(string name);
    /**
     * @brief Gets the admin of a given College
     * @return String containing the admin of the College
     */
    string getAdmin();
    /**
     * @brief Changes the administrator of a given College
     * @param admin New name of the administrator
     */
    void setAdmin(string admin);
    /**
     * @brief Shows all the information of a given College
     */
    void showInfo();
    /**
     * @brief Gets the vector with the Courses of a given College
     * @return Vector with the pointers to the Courses of a given College
     */
    vector<Course*> getCourses();
    /**
     * @brief Gets the vector with the UCs of a given College
     * @return Vector with the pointers to the UCs of a given College
     */
    vector<Uc*> getUCs();
    /**
     * @brief Gets the vector with the Departments of a given College
     * @return Vector with the pointers to the Departments of a given College
     */
    vector<Department*>& getDepartments();
    /**
     * @brief Adds a new Department to the vector of Departments (vecDep)
     */
    void addDepartment();
    /**
     * @brief Removes a Department from the vector of Departments (vecDep)
     */
    void removeDepartment();
    /**
     * @brief Adds a new Course
     */
    void addCourse(College &college);
    /**
	 * @brief Removes a Course
     */
    void removeCourse();
    /**
     * @brief Searches the Department of a given College
     * @param name Name of the Department of a given College
     */
    void searchDepartment(string name);
	/**
	* @brief Prints College info
	* @param os
	* @param college College to be used
	*/
    friend ostream& operator<< (ostream& os, const College &college);
    /**
     * @brief Gets the BST of Students
     * @return BST
     */
    BST<Student_Ptr> getStudentsTree();
    /**
     * @brief Shows all the Students in the College
     */
    void showStudents();
    /**
     * @brief Returns how many students the college has
     * @return size of the BST
     */
	int sizeBST();
	/**
	 * @brief Adds a new Student to the BST
	 * @param st1 Student to be added
	 */
    void addNewStudent(Student* st1);
    /**
     * @brief Removes a Student from the BST
     * @param st1 Pointer for the Student to be removed
     */
    void removeStudentBST(Student* st1);
    /**
     * @brief Searches a Student in the BST
     * @param name Name of the student
     * @return Pointer to a Student with Name name
     */
    Student* SearchBST(string name);
    /**
     * @brief  Changes the name of the Student
     * @param cod Code of the student that will be edited
     * @param name New name of the Student
     */
    void setNameBST(string cod, string name);
    /**
     * @brief Changes the course of the Student
     * @param cod Code of the student that will be edited
     * @param cs New Student's Course
     */
    void setCourse(string cod, Course* cs);
    /**
     * @brief Transforms the BST in a vector
     * @return A vector with pointers for Students
     */
	vector<Student*> BSTtoVEC();
};

/** @brief Department Class */
class Department {
    /** @brief Name of the Department */
    string depName;
    /** @brief Address of the Department */
    string depAddress;
    /** @brief Code of the Department */
    int depCode;
    /** @brief Phone of the Department */
    int depPhone;
    /** @brief Pointer to the Teacher responsible for the Department */
    Teacher* depDirector;
    /** @brief Vector of pointers to each Course of the Department */
    vector<Course*> vecCourse;
public:
    /**
     * @brief Department Constructor
     * @param name Name of the Department
     * @param code Code of the Department
     * @param address Address of the Department
     * @param phone Phone of the Department
     * @param director Director of the Department
     */
    Department(string name, int code, string address, int phone, Teacher* director);
    /**
     * @brief Default Department Constructor
     * @param name Name of the Department
     * @param code Code of the Department
     * @param address Address of the Department
     * @param phone Phone of the Department
     */
    Department(string name, int code, string address, int phone);
    /**
     * @brief Department Default constructor
     */
    Department() = default;
    /**
     * @brief Department destructor
     */
    ~Department();
    /**
     * @brief Shows all the information of a given Department
     */
    void showInfo();
    /**
     * @brief Opens a Menu to edit class info
     * @param college
     */
    void editInfo(College& college);
    /**
     * @brief Gets the name of a given Department
     * @return String containing the name of the Department
     */
    string getName();
    /**
     * @brief Changes the name of a given Department
     * @param name New name of the Department
     */
    void setName(string name);
    /**
     * @brief Gets the address of a given Department
     * @return String containing the address of the Department
     */
    string getAddress();
    /**
     * @brief Changes the address of a given Department
     * @param address New address of the Department
     */
    void setAddress(string address);
    /**
     * @brief Gets the director of a given Department
     * @return Pointer to the Teacher responsible for a Department
     */
    Teacher* getDirector();
    /**
     * @brief Changes the Teacher responsible for a Department
     * @param director Pointer to the new Teacher responsible for a Department
     */
    void setDirector(Teacher* director);
    /**
     * @brief Gets the code of a given Department
     * @return Integer containing code of the Department
     */
    int getCode();
    /**
     * @brief Changes the code of a given Department
     * @param code New code of the Department
     */
    void setCode(int code);
    /**
     * @brief Gets the phone of a given Department
     * @return Integer containing the phone of the Department
     */
    int getPhone();
    /**
     * @brief Changes the phone of a given Department
     * @param phone New phone of the Department
     */
    void setPhone(int phone);
    /**
     * @brief Gets the vector with the Courses of a given College
     * @return Vector with the pointers to the Courses of a given College
     */
    vector<Course*>& getCourses();
    /**
     * @brief Adds a new Course to the vector of Courses (vecCourse)
     */
    void addCourse(College &college);
    /**
     * @brief Removes a Course from the vector of Courses (vecCourse)
     */
    void removeCourse();
    /**
     * @brief Searches for a Course of a given Department
     * @param name Name of the Course of the Department
     */
    void searchCourse(string name);
	/**
	* @brief Prints Department info
	* @param os
	* @param dep Department Department to be used
	*/
    friend ostream& operator<< (ostream& os, const Department &dep);
};

/** @brief Course Class */
class Course{
    /** @brief Type of the Course */
    string csType;
    /** @brief Portuguese Name of the Course */
    string csPtName;
    /** @brief English Name of the Course */
    string csEngName;
    /** @brief Code of the Course */
    int csCode;
    /** @brief Vector of pointers to each UC of the Course */
    vector<Uc*> vecUC;
    /** @brief Pointer to courseDirector */
    Teacher* courseDirector;
public:
    /**
     * @brief Course Constructor
     * @param type Type of the Course
     * @param engName English Name of the Course
     * @param ptName Portuguese Name of the Course
     * @param code Code of the Course
     * @param director Director of the Course
     */
    Course(string type, string engName, string ptName, int code, Teacher *director);
    /**
     * @brief Default Course Constructor
     */
    Course() = default;
    /**
     * @brief Course destructor
     */
    ~Course();
    /**
     * @brief Shows all the information of a given Department
     */
    void showInfo();
    /**
	 * @brief Shows the outline of the topics to be covered in an education Course
     */
    unsigned int showSyllabus();
    /**
     * @brief Gets the type of a given Course
     * @return String containing the type of the Course
     */
    string getType();
    /**
     * @brief Changes the type of a given Course
     * @param type New type of the Course
     */
    void setType(string type);

	Teacher* getDirector() { return courseDirector;}

    /**
     * @brief Gets the Portuguese name of a given Course
     * @return String containing the Portuguese name of the Course
     */
    string getName();
    /**
     * @brief Changes the Portuguese name of a given Course
     * @param ptName New Portuguese name of the Course
     */
    void setPtName(string ptName);
    /**
     * @brief Gets the English name of a given Course
     * @return String containing the English name of the Course
     */
    string getEngName();
    /**
     * @brief Changes the English name of a given Course
     * @param engName New English name of the Course
     */
    void setEngName(string engName);
    /**
     * @brief Gets the code of a given Course
     * @return Integer containing the code of the Course
     */
    int getCode();
    /**
     * @brief Changes the code of a given Course
     * @param code New code of the Course
     */
    void setCode(int code);
    /**
     * @brief Gets the vector with the UCs of a given Course
     * @return Vector of pointers to each UC of the Course
     */
    vector<Uc*>& getUCs();
    /**
     * @brief Adds a new UC to the vector of UCs (vecUC)
     */
    void addUC(College &college);
    /**
     * @brief Removes a UC from the vector of UCs (vecUC)
     */
    void removeUC();
    /**
     * @brief Sorts the vector of UCs (vecUC) by year
     */
    void sortUc();
    /**
     * @brief Searches for a UC of the given Course
     * @param name Name of the UC of a given Course
     */
    void searchUc(string name);
    /**
	* @brief Opens a Menu to edit class info
	* @param college
     */
    void editInfo(College &college);
	/**
	* @brief Changes course director to new teacher
	* @param dir Pointer to teacher
	*/
    void setDirector(Teacher* dir){courseDirector = dir;}
	/**
	* @brief Prints course info
	* @param os
	* @param course Course to be used
	*/
    friend ostream& operator<< (ostream& os, const Course &course);
};

/** @brief Uc Class */
class Uc{
    /** @brief Name of the UC */
    string ucName;
    /** @brief Vector of pointers to each Teacher of the UC */
    vector<Teacher*> ucTeacher;
    /** @brief Vector of pointers to each Student of the UC */
    vector<Student*> ucStudent;
    /** @brief Year on which the UC is taught */
    int ucYear;
    /** @brief ECTS of the UC */
    int ucECTS;
    /** @brief Workload (in hours) of the UC */
    int ucWorkload;
    /** @brief Pointer to UC's Regent */
    Teacher* Regent;
public:
    /**
     * @brief UC Constructor
     * @param name Name of the UC
     * @param teacher Vector of pointers to each Teacher of the UC
     * @param student Vector of pointers to each Student of the UC
     * @param year Year on which the UC is taught
     * @param ects ECTS of the UC
     * @param workload Workload (in hours) of the UC
     * @param director Director of the UC
     */
    Uc(string name, vector<Teacher*> teacher, vector<Student*> student, int year, int ects, int workload, Teacher* director);
    /**
     * @brief UC Another UC constructor
     * @param name Name of the UC
     * @param ects ECTS of the UC
     * @param year Year on which the UC is taught
     * @param workload Workload (in hours) of the UC
     * @param director Director of the UC
     */
    Uc(string name, int year, int ects, int workload, Teacher* director);
    /**
     * @brief UC destructor
     */
    ~Uc();
    /**
     * @brief UC Default Constructor
     */
    Uc() = default;
    /**
     * @brief Shows all the information of a given UC
     */
    void showInfo();
    /**
     * @brief Lists the names of all the Students of a given UC
     */
    void showStudents();
    /**
     * @brief Lists the name of all the Teachers of a given UC
     */
    void showTeachers();
    /**
     * @brief Gets the name of a given UC
     * @return String containing the name of the UC
     */
    string getName();
    /**
     * @brief Changes the name of a given UC
     * @param name New name of the UC
     */
    void setName(string name);
    /**
     * @brief Gets the year of a given UC
     * @return Integer containing the year of the UC
     */
    int getYear();
    /**
     * @brief Changes the year of a given UC
     * @param year New year of the UC
     */
    void setYear(int year);
    /**
     * @brief Gets the ECTS of a given UC
     * @return Integer containing the ECTS of the UC
     */
    int getECTS();
    /**
     * @brief Changes the ECTS of a given UC
     * @param ects New ECTS of the UC
     */
    void setECTS(int ects);
    /**
     * @brief Gets the workload of a given UC
     * @return Integer containing the workload of the UC
     */
    int getWorkload();
    /**
     * @brief Changes the workload of a given UC
     * @param workload New workload of the UC
     */
    void setWorkload(int workload);
    /**
     * @brief Gets the vector with the Teachers of a given UC
     * @return Vector of pointers to each Teacher of the UC
     */
    vector<Teacher*>& getTeachers();
    /**
     * @brief Gets the vector with the Students of a given UC
     * @return Vector of pointers to each Student of the UC
     */
    vector<Student*>& getStudents();
    //void addTeacher();
    /**
     * @brief Removes a Teacher from the vector of Teachers (ucTeachers)
     */
    void removeTeacher();
    /**
     * @brief Removes a Students from the vector of Students (ucStudents)
     */
    void removeStudent();
    /**
     * @brief Compares ECTS and Workload of 2 UCs
     * @param uc2 The UC to compare
     * @return Holds true if UC1 < UC2
     */
    bool operator<(Uc uc2);
    /**
     * @brief Prints info
     * @param os
     * @param uc UC to be used
     * @return
     */
    friend ostream& operator<< (ostream& os, Uc &uc);
	/**
	* @brief Opens a Menu to edit class info
	* @param college College info to be edited
	*/
    void editInfo(College &college);
	/**
	* @brief Adds Student to UC
	* @param student Student to be added
	*/
    void addStudent(Student* student);
	/**
	* @brief Adds Teacher to UC
	* @param teacher Teacher to be added
	*/
    void addTeacher(Teacher* teacher);
};


//EXCEPTIONS//
//////////////////////

/** @brief Exception for non-existing codes */
class NoCodeFound{
    /** @brief Code that caused the Exception */
    int code;
public:
    /**
     * @brief Constructor of NoNameFound
     * @param code Code that caused the Exception
     */
    NoCodeFound(int code){
        this->code = code;
    }
    //~NoCodeFound() {}
    /**
     * @brief Error Message
     * @return String containing the code that caused the Exception
     */
    string errorMessage(){
        return "The code you indicated -" + to_string(code) + "- was not found!";
    };
};

/** @brief Exception for non-existing names */
class NoNameFound{
    /** @brief Name that caused the Exception */
    string name;
public:
    /**
     * @brief Constructor of NoNameFound
     * @param name Name that caused the Exception
     */
    NoNameFound(string name){
        this->name = name;
    }
    /**
     * @brief Error Message
     * @return String containing the name that caused the Exception
     */
    //~NoNameFound() {}
    string errorMessage(){
        return "The name you indicated -" + name + "- was not found!";
    };
};

/** @brief Exception for non-existing courses */
class NoCourses{
public:
	/**
	 * @brief Default constructor
	 */
    NoCourses() = default;
    /**
     * @brief Error Message
     * @return String containing the course that caused the Exception
     */
    string errorMessage(){
        return "There are no Courses created in this College!";
    }
};


//TEMPLATES//
//////////////////////

/**
 * @brief Template to remove a given Object from a given vector
 * @param vector Vector of the Object to be removed
 * @param name Name that the object needs to hold to be removed
 * @return Holds true if the Object was removed successfully
 */
template <class T>
bool remove(vector<T*> &vector, string name)
{
    for(unsigned int i = 0; i < vector.size(); i++)
    {
        if(vector.at(i)->getName() == name)
        {
            vector.erase(vector.begin() + i);
            return true;
        }
    }

    return false;
}

/**
 * @brief Template to all Objects from a vector
 * @param vector Vector of the Objects to be removed
 */
template <class T>
void dest_remove(vector<T*> &vector)
{
    for(unsigned int i = 0; i < vector.size(); i++)
    {
        delete vector.at(i);
    }
}

/**
 * @brief Prints the name of every Object in a given vector of Objects
 * @param vec Vector of the Objects to be printed
 */
template<class T>
void Print_Vec(vector<T*> vec){
    for(unsigned int i = 0; i < vec.size() ; i++){
        cout << i << ":   " << vec.at(i)->getName() << endl;
    }
}

/**
 * @brief Template to search a given Object from a given vector
 * @param vec Vector of the Object to be searched
 * @param name Name that the object needs to hold to be found
 * @return throws exception if not found
 */
template<class T>
T* SearchVec(vector<T*> vec, string name){
    for(size_t i = 0; i < vec.size(); i++){
        if(vec.at(i)->getName() == name) return vec.at(i);
    }
    throw NoNameFound(name);
}

/**
 * @brief Template to search a given Object from a given vector
 * @param vec Vector of the Object to be searched
 * @param id ID that the object needs to hold to be found
 * @return throws exception if not found
 */
template<class T>
T* SearchID(vector<T*> vec, string id) {
	for (size_t i = 0; i < vec.size(); i++) {
		if (vec.at(i)->getCode() == id) return vec.at(i);
	}
	throw NoCodeFound(stoi(id));
}

#endif /*COLLEGE_H_*/
