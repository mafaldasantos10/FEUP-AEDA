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
#include "People.h"

using namespace std;

//PROTOTYPES
class Department;
class Course;
class Uc;
class People;
class Employee;
class Student;
class Teacher;
class Staff;

/**
 * @brief
 * @param bottom
 * @param top
 * @return
 */
int Nav(int bottom, int top);

/**
 * @brief
 * @return
 */
date* readDate();

/** @brief */
extern int current_year;


/** @brief College Class */
class College{
    /** @brief Name of the College */
    string colName;
    /** @brief idk */
    string admin; //For logging in as admin
    /** @brief Vector of pointers to each Department of the College */
    vector<Department*> vecDep;
    /** @brief Vector of Vectors of pointers to each People of the College */
    vector<Student *> students;
    vector<Teacher *> teachers;
    vector<Staff *> staff;
public:
    /**
     * @brief College Constructor
     * @param name Name of the College
     */
    College(string name);
    /**
     * @brief Default College Constructor
     */
    College(){}
    //~College(); //class destructor
    /**
     *
     * @return
     */
    vector<Teacher *> getTeachers();

    vector<Student *> getStudents();

    vector<Staff *> getStaff();
    /**
     *
     * @param teacher
     */
    void addTeacher(Teacher* teacher);

    void addStudent(Student* student);

    void addStaff(Staff* staff);
    /**
     * @brief Gets the name of a given College
     * @return String containing the name of the College
     */
    string getName();
    /**
     * @brief Changes the name of a given College
     * @param name New name of the College
     */
    void setName(string name);
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
     * @brief Gets the vector with the Departments of a given College
     * @return Vector with the pointers to the Departments of a given College
     */
    vector<Department*> getDepartments();
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
    void addCourse();
    /**
	 * @brief Removes a Course
     */
    void removeCourse();
    /**
     * @brief Searches the Department of a given College
     * @param name Name of the Department of a given College
     */
    void searchDepartment(string name);
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
    //~Department();
    /**
     * @brief Shows all the information of a given Department
     */
    void showInfo();
    /**
     * @brief
     * @return
     */
    int editInfo();
    /**
     *
     * @param n
     */
    void Set(int n);
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
    vector<Course*> getCourses();
    /**
     * @brief Adds a new Course to the vector of Courses (vecCourse)
     */
    void addCourse();
    /**
     * @brief Removes a Course from the vector of Courses (vecCourse)
     */
    void removeCourse();
    /**
     * @brief Searches for a Course of a given Department
     * @param name Name of the Course of the Department
     */
    void searchCourse(string name);
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
public:
    /**
     * @brief Course Constructor
     * @param type Type of the Course
     * @param ptName Portuguese Name of the Course
     * @param engName English Name of the Course
     * @param code Code of the Course
     */
    Course(string type, string engName, string ptName, int code);
    //~Course();
    /**
     * @brief Shows all the information of a given Department
     */
    void showInfo();
    /**
     *
     * @return
     */
    int editInfo();
    /**
     *
     * @param n
     */
    void Set(int n);
    /**
	 * @brief Shows the outline of the topics to be covered in an education Course
     */
    void showSyllabus();
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
    vector<Uc*> getUCs();
    /**
     * @brief Adds a new UC to the vector of UCs (vecUC)
     */
    void addUC();
    /**
     * @brief Removes a UC from the vector of UCs (vecUC)
     */
    void removeUC();
    /**
     * @brief Sorts the vector of UCs (vecUC) by year
     */
    void sortUc();
    /**
     * @brief Searches for a Uc of the given Course
     * @param name Name of the Uc of a given Course
     */
    void searchUc(string name);
};

/** @brief Uc Class */
class Uc{
    /** @brief Name of the UC */
    string ucName;
    /** @brief Vector of pointers to each Teacher of the UC */
    vector<Teacher*> ucTeacher; //sendo que o que se encontra na posicao 0 o regente
    /** @brief Vector of pointers to each Student of the UC */
    vector<Student*> ucStudent;
    /** @brief Year on which the UC is taught */
    int ucYear;
    /** @brief ECTS of the UC */
    int ucECTS;
    /** @brief Workload (in hours) of the UC */
    int ucWorkload;
public:
    /**
     * @brief Uc Constructor
     * @param name Name of the UC
     * @param teacher Vector of pointers to each Teacher of the UC
     * @param student Vector of pointers to each Student of the UC
     * @param year Year on which the UC is taught
     * @param ects ECTS of the UC
     * @param workload Workload (in hours) of the UC
     */
    Uc(string name, vector<Teacher*> teacher, vector<Student*> student, int year, int ects, int workload);
    /**
     * @brief Uc Default Constructor
     * @param name Name of the UC
     * @param year Year on which the UC is taught
     * @param ects ECTS of the UC
     * @param workload Workload (in hours) of the UC
     */
    Uc(string name, int year, int ects, int workload);
    //~Uc();
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
    vector<Teacher*> getTeachers();
    /**
     * @brief Gets the vector with the Students of a given UC
     * @return Vector of pointers to each Student of the UC
     */
    vector<Student*> getStudents();
    //void addTeacher();
    /**
     * @brief Removes a Teacher from the vector of Teachers (ucTeachers)
     */
    void removeTeacher();
    //void addStudent();
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


//TEMPLATES//
//////////////////////

/**
 * @brief Template to remove a given Object from a given vector
 * @param vector Vector of the Object to be removed
 * @param name Name that the object needs to hold to be removed
 * @return Holds true if the Object was removed successfully
 */
template <class T>
bool remove(vector<T> &vector, string name)
{
    for(unsigned int i = 0; i <= vector.size(); i++)
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
 * @brief Prints the name of every Object in a given vector of Objects
 * @param vec Vector of the Objects to be printed
 */
template<class T>
void Print_Vec(vector<T*> vec){
    for(unsigned int i = 0; i < vec.size() ; i++){
        cout << i << ":   " << vec.at(i)->getName() << endl;
    }
}

template<class T>
T* SearchVec(vector<T*> vec, string name){
    for(size_t i = 0; i < vec.size(); i++){
        if(vec.at(i)->getName() == name) return vec.at(i);
    }
    throw NoNameFound(name);
}

#endif /*COLLEGE_H_*/
