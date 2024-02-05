#pragma once
#ifndef USER_H 
#define USER_H 

#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include <algorithm>

//Global variables that can be accessed in user.cpp and main.cpp
extern int user_index;
extern std::string user_name;
extern std::string user_category;
extern std::string user_id;
extern int last_line_number;
extern int user_line_number;
extern bool loggedIn;
extern bool acceptable;
extern int module_line_number;
extern int choice;
extern std::string user_input;
extern int module_index;
extern bool enrolled;

class User
{
public:
	std::string user_password;
	std::string user_phone;
	std::string user_address;

	//ALL
	void clear();
	int login(std::string, std::string); 
	int modifyInfo(int);
	char identifyStatus(std::string);
	int displayUserInfo();

	//STAFF
	int modifyUserStaff();
	int addUserStaff();
	int deleteUserStaff();
};

#endif