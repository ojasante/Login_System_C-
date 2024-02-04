#pragma once
#ifndef MODULE_H
#define MODULE_H

#include "user.h"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

class Module
{
public:
	//std::string module_index;
	std::string module_id;
	std::string module_name;
	std::string teacher_id;
	std::string student_id;
	std::string student_grade;
	std::string status;

	//STUDENT & TEACHER
	int viewModuleStudent();
	int printStudentInfo(std::string teacher_id);

	//TEACHER & STAFF
	int viewModuleTeacher();
	int modifyModuleTeacher(int index_num);
	int displayModuleInfo();

	//STAFF
	int addModuleStaff();
	int modifyModuleStaff();
	int deleteModuleStaff();
	int releaseModuleStaff();

};

#endif