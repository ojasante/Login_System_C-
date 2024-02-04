#include "module.h"

int module_index;
int module_line_number;
std::string user_input;
bool acceptable;
int last_line_number;
bool enrolled;

User user;

int Module::viewModuleStudent()
{
	std::fstream newfile;
 	newfile.open("module.txt", std::ios::in);

 	if (newfile.fail()) {
 		std::cout << "Error opening file." << "\n";
 		return 1; //tells terminal there is an error
 	}

	//alternative: add input_id as a variable in the function to search in replace of user_id
	user.clear();
	std::string mystring;
	std::cout << "=========================== MODULE INFORMATION ===========================" << "\n\n";
	while (std::getline(newfile, mystring)) {
		module_line_number++;
		std::istringstream mystream(mystring);
		mystream >> module_id >> module_name >> teacher_id >> student_id >> student_grade >> status;

		if (student_id == user_id) {
			enrolled = true;
			std::cout << "Your Module: " << module_name << " (" << module_id << ")\n";

			if (status == "Released") {
				std::cout << "Your Grade: " << student_grade << "\n\n";
			}
			else {
				std::cout << "Your " << module_id << " module grade has not been released.\n\n";
			}
		}
	}

	if (!enrolled) {
		std::cout << "You are not enrolled in a module!\n\n";
	}

	std::cout << "==========================================================================" << "\n\n";
	module_line_number = 0; //reset for other functions to work

	return 0;
}

int Module::viewModuleTeacher()
{
	std::fstream newfile;
 	newfile.open("module.txt", std::ios::in);

 	if (newfile.fail()) {
 		std::cout << "Error opening file." << "\n";
 		return 1; //tells terminal there is an error
 	}

 	user.clear();
	bool enrolled;
	std::string mystring;
	while (std::getline(newfile, mystring)) {
		module_line_number++;
		std::istringstream mystream(mystring);
		mystream >> module_id >> module_name >> teacher_id >> student_id >> student_grade >> status;

		if (teacher_id == user_id) {
			enrolled = true;
			std::cout << "=========================== MODULE INFORMATION ===========================" << "\n\n";
			std::cout << "Your Module: " << module_name << " (" << module_id << ")\n\n";
			newfile.close();
			std::cout << "==========================================================================" << "\n\n";

			printStudentInfo(teacher_id);
			break;
		}
		else {
			enrolled = false;
		}
	}

	module_line_number = 0; //reset for other functions to work

	return 0;
}

int Module::printStudentInfo(std::string teacher_id)
{
	std::fstream newfile;
 	newfile.open("module.txt", std::ios::in);

 	if (newfile.fail()) {
 		std::cout << "Error opening file." << "\n";
 		return 1; //tells terminal there is an error
 	}

	std::cout << "============================== Your Students =============================\n\n";
	module_index = 0;
	std::string mystring;
	while (std::getline(newfile, mystring)) {
		std::istringstream mystream(mystring);
		mystream >> module_id >> module_name >> teacher_id >> student_id >> student_grade >> status;
		
		if (teacher_id == user_id) {
			std::cout << std::to_string(module_index + 1) << " " << student_id << " " << student_grade << " " << status << "\n";
			module_index++;
		}
	}
	std::cout << "\n==========================================================================\n\n";
	newfile.close();
	return 0;
}

int Module::modifyModuleTeacher(int index_num)
{
	user.clear();

	std::fstream newfile;
 	newfile.open("module.txt", std::ios::in);
 	if (newfile.fail()) {
 		std::cout << "Error opening file." << "\n";
 		return 1; //tells terminal there is an error
 	}

	std::vector<std::string> file_lines;
	std::string lines;
	while (std::getline(newfile, lines)) {
		file_lines.push_back(lines);
	}

	newfile.close();

	newfile.open("module.txt", std::ios::in);
 	if (newfile.fail()) {
 		std::cout << "Error opening file." << "\n";
 		return 1; //tells terminal there is an error
 	}

	for (int i = 0; i < index_num - 1; ++i) {
		newfile.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
		//'numeric_limits<streamsize>::max()' means there is no limit for num of characters to be extracted. Extract as needed until '\n' is found
	}

	std::string mystring;
	std::getline(newfile, mystring);
	std::istringstream mystream(mystring);
	mystream >> module_id >> module_name >> teacher_id >> student_id >> student_grade >> status;

	newfile.close();

	newfile.open("module.txt", std::ios::out);
 	if (newfile.fail()) {
 		std::cout << "Error opening file." << "\n";
 		return 1; //tells terminal there is an error
 	}

	while (!acceptable) {
		std::cout << "Enter new grade for " << student_id << ": ";
		std::cin.ignore();
		std::getline(std::cin, user_input);
		if (!user_input.empty()) {
			if (user_input.length() <= 3) {
				student_grade = user_input;
				acceptable = true;
			}
			else {
				std::cout << "Student Grade must be at most 3 digits!\n"; 
			}
		}
		else {
			user.clear();
			std::cout << "Please enter grade!\n\n";
		}
	}
	acceptable = false;

 	for (int i = 0; i < file_lines.size(); i++) {
 		if (i != index_num - 1) {
			newfile << file_lines[i] << "\n";
 		}
 		else {
		 	//newfile << std::left << std::setw(5) << module_index
		 	newfile << std::left << std::setw(10) << module_id
		 	<< std::left << std::setw(17) << module_name 
		 	<< std::left << std::setw(10) << teacher_id
		 	<< std::left << std::setw(10) << student_id
		 	<< std::left << std::setw(5) << student_grade << status << "\n";
 		}
	}

	newfile.close();

	user.clear();
	std::cout << "Grade of " << student_id << " has been updated successfully!\n\n";

	return 0;
}

int Module::displayModuleInfo()
{
	std::fstream newfile;
 	newfile.open("module.txt", std::ios::in);

 	if (newfile.fail()) {
 		std::cout << "Error opening file." << "\n";
 		return 1; //tells terminal there is an error
 	}

	std::cout << "======================= Module Database =======================\n";
	module_index = 0;
	std::string mystring;
	while (std::getline(newfile, mystring)) {
		std::istringstream mystream(mystring);
		mystream >> module_id >> module_name >> teacher_id >> student_id >> student_grade >> status;
		
		std::cout << std::to_string(module_index + 1) << " " << module_id << " " << module_name << " " << teacher_id << " " << student_id << " " << student_grade << " " << status << "\n";
		module_index++;
	}
	std::cout << "===============================================================\n\n";
	newfile.close();

	return 0;
}

int Module::modifyModuleStaff()
{
	user.clear();
	displayModuleInfo();

	std::cout << "Enter index of information to be edited. (Enter 0 to return to previous page)\n";
	std::cout << ">> ";
	std::cin >> choice;

	if (choice != 0) {
		std::fstream newfile;
	 	newfile.open("module.txt", std::ios::in);
	 	if (newfile.fail()) {
	 		std::cout << "Error opening file." << "\n";
	 		return 1; //tells terminal there is an error
	 	}

		std::vector<std::string> file_lines;
		std::string lines;
		while (std::getline(newfile, lines)) {
			file_lines.push_back(lines);
		}

		newfile.close();

		newfile.open("module.txt", std::ios::in);
	 	if (newfile.fail()) {
	 		std::cout << "Error opening file." << "\n";
	 		return 1; //tells terminal there is an error
	 	}

		for (int i = 0; i < choice - 1; ++i) {
			newfile.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
			//'numeric_limits<streamsize>::max()' means there is no limit for num of characters to be extracted. Extract as needed until '\n' is found
		}

		std::string mystring;
		std::getline(newfile, mystring);
		std::istringstream mystream(mystring);
		mystream >> module_id >> module_name >> teacher_id >> student_id >> student_grade >> status;
		newfile.close();

		user.clear();
		while (!acceptable) {
			std::cout << "Change Module ID to (current: " << module_id << ")(Maximum 8 characters)\n";
			std::cin.ignore();
			std::cout << "(Press Enter to keep) >> ";
			std::getline(std::cin, user_input);
			if (!user_input.empty()) {
				if (user_input.length() <= 8) {
					module_id = user_input;
					acceptable = true;
				}
				else {
					user.clear();
					std::cout << "Module ID must be at most 8 characters!\n\n"; 
				}
			}
			else {
				acceptable = true;
			}
		}
		acceptable = false;

		user.clear();
		while (!acceptable) {
			std::cout << "Change Module Name to (current: " << module_name << ")(Maxium 15 chatacters)\n";
			std::cout << "(Press Enter to keep) >> ";
			std::getline(std::cin, user_input);
			if (!user_input.empty()) {
				if (user_input.length() <= 15) {
					module_name = user_input;
					acceptable = true;
				}
				else {
					user.clear();
					std::cout << "Module Name must be at most 15 characters!\n\n"; 
				}
			}
			else {
				acceptable = true;
			}
		}
		acceptable = false;

		user.clear();
		while (!acceptable) {
			std::cout << "Change Teacher ID to (current: " << teacher_id << ")(Maximum 5 characters)\n";
			std::cout << "(Press Enter to keep) >> ";
			std::getline(std::cin, user_input);
			if (!user_input.empty()) {
				if (user_input.length() <= 5) {
					teacher_id = user_input;
					acceptable = true;
				}
				else {
					user.clear();
					std::cout << "Teacher ID must be at most 5 characters!\n\n"; 
				}
			}
			else {
				acceptable = true;
			}
		}
		acceptable = false;

		user.clear();
		while (!acceptable) {
			std::cout << "Change Student ID to (current: " << student_id << ")(Maximum 5 characters)\n";
			std::cout << "(Press Enter to keep) >> ";
			std::getline(std::cin, user_input);
			if (!user_input.empty()) {
				if (user_input.length() <= 5) {
					student_id = user_input;
					acceptable = true;
				}
				else {
					user.clear();
					std::cout << "Student ID must be at most 5 characters!\n\n"; 
				}
			}
			else {
				acceptable = true;
			}
		}
		acceptable = false;

		user.clear();
		while (!acceptable) {
			std::cout << "Change Student Grade to (current: " << student_grade << ")(Maximum 3 digits)\n";
			std::cout << "(Press Enter to keep) >> ";
			std::getline(std::cin, user_input);
			if (!user_input.empty()) {
				if (user_input.length() <= 3) {
					student_grade = user_input;
					acceptable = true;
				}
				else {
					user.clear();
					std::cout << "Student Grade must be at most 3 digits!\n\n"; 
				}
			}
			else {
				acceptable = true;
			}
		}
		acceptable = false;

		newfile.open("module.txt", std::ios::out);
	 	if (newfile.fail()) {
	 		std::cout << "Error opening file." << "\n";
	 		return 1; //tells terminal there is an error
	 	}

	 	for (int i = 0; i < file_lines.size(); i++) {
	 		if (i != choice - 1) {
				newfile << file_lines[i] << "\n";
	 		}
	 		else {
			 	//newfile << std::left << std::setw(5) << module_index
			 	newfile << std::left << std::setw(10) << module_id
			 	<< std::left << std::setw(17) << module_name 
			 	<< std::left << std::setw(10) << teacher_id
			 	<< std::left << std::setw(10) << student_id
			 	<< std::left << std::setw(5) << student_grade << status << "\n";
	 		}
		}

		newfile.close();
		user.clear();
		std::cout << "Module modified successfully!\n\n";

	}
	else {
		std::cout << "Returned to previous page.\n";
	}

	return 0;
}

int Module::addModuleStaff()
{
	user.clear();
	while (!acceptable) {
		std::cout << "Enter Module ID (Maximum 8 characters)\n";
		std::cout << ">> ";
		std::cin.ignore();
		std::getline(std::cin, user_input);
		if (!user_input.empty()) {
			if (user_input.length() <= 8) {
				module_id = user_input;
				acceptable = true;
			}
			else {
				user.clear();
				std::cout << "Module ID must be at most 8 characters!\n\n"; 
			}
		}
		else {
			user.clear();
			std::cout << "Please input a Module ID!\n\n";
		}
	}
	acceptable = false;

	user.clear();
	while (!acceptable) {
		std::cout << "Enter Module Name (Maximum 15 characters)\n";
		std::cout << ">> ";
		std::getline(std::cin, user_input);
		if (!user_input.empty()) {
			if (user_input.length() <= 15) {
				module_name = user_input;
				acceptable = true;
			}
			else {
				user.clear();
				std::cout << "Module Name must be at most 15 characters!\n\n"; 
			}
		}
		else {
			user.clear();
			std::cout << "Please input a Module Name!\n\n";
		}
	}
	acceptable = false;

	user.clear();
	while (!acceptable) {
		std::cout << "Enter Teacher ID (Maximum 5 characters)\n";
		std::cout << ">> ";
		std::getline(std::cin, user_input);
		if (!user_input.empty()) {
			if (user_input.length() <= 5) {
				teacher_id = user_input;
				acceptable = true;
			}
			else {
				user.clear();
				std::cout << "Teacher ID must be at most 5 characters!\n\n"; 
			}
		}
		else {
			user.clear();
			std::cout << "Please input a Teacher ID!\n\n";
		}
	}
	acceptable = false;

	user.clear();
	while (!acceptable) {
		std::cout << "Enter Student ID (Maximum 5 characters)\n";
		std::cout << ">> ";
		std::getline(std::cin, user_input);
		if (!user_input.empty()) {
			if (user_input.length() <= 5) {
				student_id = user_input;
				acceptable = true;
			}
			else {
				user.clear();
				std::cout << "Student ID must be at most 5 characters!\n\n"; 
			}
		}
		else {
			user.clear();
			std::cout << "Please input a Student ID!\n\n";
		}
	}
	acceptable = false;

	user.clear();
	while (!acceptable) {
		std::cout << "Enter Student Grade (Maximum 3 characters)\n";
		std::cout << ">> ";
		std::getline(std::cin, user_input);
		if (!user_input.empty()) {
			if (user_input.length() <= 3) {
				student_grade = user_input;
				acceptable = true;
			}
			else {
				user.clear();
				std::cout << "Student Grade must be at most 3 characters!\n\n"; 
			}
		}
		else {
			user.clear();
			std::cout << "Please input Student Grade!\n\n";
		}
	}
	acceptable = false;

	user.clear();
	while (!acceptable) { 
		std::cout << "Release grade? (Yes/No)\n";
		std::cout << ">> ";
		std::cin >>	user_input;
		std::transform(user_input.begin(), user_input.end(), user_input.begin(), ::toupper); 
	
		if (user_input == "YES") {
			status = "Released";
			acceptable = true;
		}
		else if (user_input == "NO") {
			status = "Not_Released";
			acceptable = true;
		}
		else {
			user.clear();
			std::cout << "Please input Yes/No!\n\n";
		}
	}
	acceptable = false;

	std::fstream newfile;
 	newfile.open("module.txt", std::ios::in);
 	if (newfile.fail()) {
 		std::cout << "Error opening file." << "\n";
 		return 1; //tells terminal there is an error
 	}

 	last_line_number = 0;
	std::vector<std::string> file_lines;
	std::string lines;
	while (std::getline(newfile, lines)) {
		file_lines.push_back(lines);
		last_line_number++;
	}

	newfile.close();

	newfile.open("module.txt", std::ios::in);
 	if (newfile.fail()) {
 		std::cout << "Error opening file." << "\n";
 		return 1; //tells terminal there is an error
 	}

	newfile.close();

	newfile.open("module.txt", std::ios::out);
 	if (newfile.fail()) {
		std::cout << "Error opening file." << "\n";
		return 1; //tells terminal there is an error
 	}

	//module_index = std::to_string(last_line_number + 1);

 	for (int i = 0; i < last_line_number + 1; i++) {
		if (i != last_line_number) {
			newfile << file_lines[i] << "\n";
		}
		else {
		 	//newfile << std::left << std::setw(5) << module_index
		 	newfile<< std::left << std::setw(10) << module_id
		 	<< std::left << std::setw(17) << module_name 
		 	<< std::left << std::setw(10) << teacher_id
		 	<< std::left << std::setw(10) << student_id
		 	<< std::left << std::setw(5) << student_grade << status << "\n";
		}
	}

 	newfile.close();
 	user.clear();
 	std::cout << "Module " << module_id << " has been added successfully!\n\n";

 	return 0;
}

int Module::deleteModuleStaff()
{
	user.clear();
	displayModuleInfo();

	std::cout << "Enter index of information to be deleted. (Enter 0 to return to previous page)\n\n";
	std::cout << ">> ";
	std::cin >> choice;

	if (choice != 0) {
		std::fstream newfile;
 		newfile.open("module.txt", std::ios::in);
	 	if (newfile.fail()) {
	 		std::cout << "Error opening file." << "\n";
	 		return 1; //tells terminal there is an error
	 	}

		std::vector<std::string> file_lines;
		std::string lines;
		while (std::getline(newfile, lines)) {
			file_lines.push_back(lines);
		}

		newfile.close();

		newfile.open("module.txt", std::ios::out);
	 	if (newfile.fail()) {
	 		std::cout << "Error opening file." << "\n";
	 		return 1; //tells terminal there is an error
	 	}

	 	for (int i = 0; i < file_lines.size(); i++) {
	 		if (i != choice - 1) {
				newfile << file_lines[i] << "\n";
	 		}
	 		else {
			 	//delete line
	 		}
		}

		newfile.close();
		user.clear();
		std::cout << "Module deleted successfully!\n\n";
	}
	else {
		user.clear();
		std::cout << "Returned to previous page.\n\n";
	}

	return 0;
}

int Module::releaseModuleStaff()
{
	user.clear();
	displayModuleInfo();

	std::cout << "Enter index of status (Released/Not_Released) to be switched. (Enter 0 to return to previous page)\n\n";
	std::cout << ">> ";
	std::cin >> choice;

	if (choice != 0) {
		std::fstream newfile;
	 	newfile.open("module.txt", std::ios::in);
	 	if (newfile.fail()) {
	 		std::cout << "Error opening file." << "\n";
	 		return 1; //tells terminal there is an error
	 	}

		std::vector<std::string> file_lines;
		std::string lines;
		while (std::getline(newfile, lines)) {
			file_lines.push_back(lines);
		}

		newfile.close();

		newfile.open("module.txt", std::ios::in);
	 	if (newfile.fail()) {
	 		std::cout << "Error opening file." << "\n";
	 		return 1; //tells terminal there is an error
	 	}

		for (int i = 0; i < choice - 1; ++i) {
			newfile.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
			//'numeric_limits<streamsize>::max()' means there is no limit for num of characters to be extracted. Extract as needed until '\n' is found
		}

		std::string mystring;
		std::getline(newfile, mystring);
		std::istringstream mystream(mystring);
		mystream >> module_id >> module_name >> teacher_id >> student_id >> student_grade >> status;
		newfile.close();	

		if (status == "Released") {
			status = "Not_Released";

		}
		else {
			status = "Released";
		} 

		newfile.open("module.txt", std::ios::out);
	 	if (newfile.fail()) {
	 		std::cout << "Error opening file." << "\n";
	 		return 1; //tells terminal there is an error
	 	}

	 	for (int i = 0; i < file_lines.size(); i++) {
	 		if (i != choice - 1) {
				newfile << file_lines[i] << "\n";
	 		}
	 		else {
			 	newfile << std::left << std::setw(10) << module_id
			 	<< std::left << std::setw(17) << module_name 
			 	<< std::left << std::setw(10) << teacher_id
			 	<< std::left << std::setw(10) << student_id
			 	<< std::left << std::setw(5) << student_grade << status << "\n";
	 		}
		}

		newfile.close();
		user.clear();
		std::cout << "Module status changed successfully!\n\n";
	}
	else {
		user.clear();
		std::cout << "Returned to previous page.\n\n";
	}

	return 0;
}