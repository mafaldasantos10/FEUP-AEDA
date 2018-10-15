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

using namespace std;


class College{
	//string name;
	vector<Departments> Dep;
public:
	College();
	//int numVeiculos() const;
};

class Departments: public College {
   string name;
public:
   Department(string name);
};


#endif /*COLLEGE_H_*/
