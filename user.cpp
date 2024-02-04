#include "user.h"

int user_index;
std::string user_name;
std::string user_category;
std::string user_id;
int user_line_number;
bool loggedIn;

void User::clear()
{
	#if defined _WIN32
	    system("cls");
	#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__) || (__APPLE__)
	    system("clear");
	#endif
}

char User::identifyStatus(std::string user_category)
{
	if (user_category == "student") 
		return 'S';
	else if (user_category == "teacher")
		return 'T';
	else
		return 'F'; 
}

int User::login(std::string input_id, std::string input_password)
{
	//bool status;
	std::fstream newfile;
 	newfile.open("user.txt", std::ios::in);

 	if (newfile.fail()) {
 		std::cout << "Error opening file." << "\n";
 		return 1; //tells terminal there is an error
 	}

	std::string mystring;
	while (std::getline(newfile, mystring)) {
		user_line_number++;
		std::istringstream mystream(mystring);
		mystream >> user_id >> user_name >> user_password >> user_category;

		if (input_id == user_id && input_password == user_password) {
			loggedIn = true;
			break;
		}
		else {
			loggedIn = false;
		}
	}

	newfile.close();
	return loggedIn;
}

int User::modifyInfo(int user_line_number) 
{
	std::fstream newfile;
 	newfile.open("user.txt", std::ios::in);
 	if (newfile.fail()) {
 		std::cout << "Error opening file." << "\n";
 		return 1; //tells terminal there is an error
 	}

	std::vector<std::string> file_lines;
	std::string lines;
	while (std::getline(newfile, lines)) {
		file_lines.push_back(lines);
	}

	newfile.close(); //IDK why I need to close and reopen here. If not user_address & user_phone won't appear

	newfile.open("user.txt", std::ios::in);
 	if (newfile.fail()) {
 		std::cout << "Error opening file." << "\n";
 		return 1; //tells terminal there is an error
 	}

 	//goes to specific line in file for next operation
	for (int i = 0; i < user_line_number - 1; ++i) {
		newfile.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
		//'numeric_limits<streamsize>::max()' means there is no limit for num of characters to be extracted. Extract as needed until '\n' is found
	}
	//consider changing to file_lines[user_line_number - 1] for convenience

	clear();
	std::string mystring;
	std::getline(newfile, mystring);
	std::istringstream mystream(mystring);
	mystream >> user_id >> user_name >> user_password >> user_category >> user_phone >> user_address;
	
	newfile.close();


	int choice;
	std::string newPhone, newAddress;
	do {
		std::cout << "=========================== CURRENT INFORMATION ===========================" << "\n\n";
		std::cout << "Phone number: " << user_phone << "\n";
		std::cout << "Address: " << user_address << "\n\n";
		std::cout << "===========================================================================" << "\n\n";
		std::cout << "--------------------------------------------------------------------------------" << "\n\n";
		std::cout << "================================ OPTIONS ==================================" << "\n\n";
		std::cout << "1. Change phone number" << "\n";
		std::cout << "2. Change address" << "\n";
		std::cout << "3. Return to homepage" << "\n\n";
		std::cout << "===========================================================================" << "\n\n";
		std::cout << ">> ";
		std::cin >> choice;

		switch (choice) {
		case 1:
			clear();
			while (!acceptable) {
				std::cout << "Change current phone number to (current: " << user_phone << ")(Maximum 14 characters)\n";
				std::cout << "(Press Enter to keep) >> ";
				std::cin.ignore();
				std::getline(std::cin, user_input);
				if (!user_input.empty()) {
					if (user_input.length() <= 14) {
						user_phone = user_input;
						acceptable = true;
					}
					else {
						std::cout << "User Phone must be at most 14 characters!\n"; 
					}
				}
				else {
					acceptable = true;
				}
			}
			acceptable = false;

			clear();
			std::cout << "Information modified successfully!\n\n";
			break;
		case 2: 
			clear();
			while (!acceptable) {
				std::cout << "Change current address to (current: " << user_address << ")(Maximum 10 characters)\n";
				std::cout << "(Press Enter to keep) >> ";
				std::cin.ignore();
				std::getline(std::cin, user_input);
				if (!user_input.empty()) {
					if (user_input.length() <= 10) {
						user_address = user_input;
						acceptable = true;
					}
					else {
						std::cout << "User Address must be at most 10 characters!\n"; 
					}
				}
				else {
					acceptable = true;
				}
			}
			acceptable = false;

			clear();
			std::cout << "Information modified successfully!\n\n";
			break;
		case 3: 
			clear();
			break;
		default:
			clear();
			std::cout << "Invalid choice!\n\n";
			break;
		}
	} while (choice != 3); //keep showing menu until user chooses return to homepage
	newfile.open("user.txt", std::ios::out); //reopen to write into file

 	if (newfile.fail()) {
 		std::cout << "Error opening file." << "\n";
 		return 1; //tells terminal there is an error
 	}

 	for (int i = 0; i < file_lines.size(); i++) {
 		if (i != user_line_number - 1) {
			newfile << file_lines[i] << "\n";
 		}
 		else {
	  		//newfile << std::left << std::setw(5) << user_index
	 		newfile << std::left << std::setw(10) << user_id 
	 		<< std::left << std::setw(12) << user_name
	 		<< std::left << std::setw(10) << user_password
	 		<< std::left << std::setw(11) << user_category
	 		<< std::left << std::setw(16) << user_phone << user_address << "\n";
 		}
	}

	clear();
	newfile.close();

	return 0;
}

int User::displayUserInfo()
{
	std::fstream newfile;
 	newfile.open("user.txt", std::ios::in);

 	if (newfile.fail()) {
 		std::cout << "Error opening file." << "\n";
 		return 1; //tells terminal there is an error
 	}

	std::cout << "======================= User Database =======================\n\n";
	user_index = 0;
	std::string mystring;
	while (std::getline(newfile, mystring)) {
		std::istringstream mystream(mystring);
		mystream >> user_id >> user_name >> user_password >> user_category >> user_phone >> user_address;
		
		std::cout << std::to_string(user_index + 1) << " " << user_id << " " << user_name << " " << user_phone << " " << user_address << "\n";
		user_index++;
	}
	std::cout << "=============================================================\n\n";
	newfile.close();

	return 0;
}

int User::modifyUserStaff()
{
	clear();
	displayUserInfo();

	std::cout << "Enter index of information to be edited. (Enter 0 to return to previous page)\n";
	std::cout << ">> ";
	std::cin >> choice;

	if (choice != 0) {
		std::fstream newfile;
	 	newfile.open("user.txt", std::ios::in);
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

		newfile.open("user.txt", std::ios::in);
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
		mystream >> user_id >> user_name >> user_password >> user_category >> user_phone >> user_address;
		newfile.close();

		clear();
		while (!acceptable) {
			std::cout << "User ID to (current: " << user_id << ")(Maximum 5 characters)\n";
			std::cin.ignore();
			std::cout << "(Press Enter to keep) >> ";
			std::getline(std::cin, user_input);
			if (!user_input.empty()) {
				if (user_input.length() <= 5) {
					user_id = user_input;
					acceptable = true;
				}
				else {
					clear();
					std::cout << "User ID must be at most 5 characters!\n\n"; 
				}
			}
			else {
				acceptable = true;
			}
		}
		acceptable = false;

		clear();
		while (!acceptable) {
			std::cout << "Change User Name to (current: " << user_name << ")(Maximum 10 chatacters)\n";
			std::cout << "(Press Enter to keep) >> ";
			std::getline(std::cin, user_input);
			if (!user_input.empty()) {
				if (user_input.length() <= 10) {
					user_name = user_input;
					acceptable = true;
				}
				else {
					clear();
					std::cout << "User Name must be at most 10 characters!\n\n"; 
				}
			}
			else {
				acceptable = true;
			}
		}
		acceptable = false;

		clear();
		while (!acceptable) {
			std::cout << "Change User Phone to (current: " << user_phone << ")(Maximum 14 characters)\n";
			std::cout << "(Press Enter to keep) >> ";
			std::getline(std::cin, user_input);
			if (!user_input.empty()) {
				if (user_input.length() <= 14) {
					user_phone = user_input;
					acceptable = true;
				}
				else {
					clear();
					std::cout << "User Phone must be at most 14 characters!\n\n"; 
				}
			}
			else {
				acceptable = true;
			}
		}
		acceptable = false;

		clear();
		while (!acceptable) {
			std::cout << "Change User Address to (current: " << user_address << ")(Maximum 10 characters)\n";
			std::cout << "(Press Enter to keep) >> ";
			std::getline(std::cin, user_input);
			if (!user_input.empty()) {
				if (user_input.length() <= 10) {
					user_address = user_input;
					acceptable = true;
				}
				else {
					clear();
					std::cout << "User Address must be at most 10 characters!\n\n"; 
				}
			}
			else {
				acceptable = true;
			}
		}
		acceptable = false;

		newfile.open("user.txt", std::ios::out);
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
			 	newfile << std::left << std::setw(10) << user_id
			 	<< std::left << std::setw(12) << user_name 
			 	<< std::left << std::setw(10) << user_password
			 	<< std::left << std::setw(11) << user_category
			 	<< std::left << std::setw(16) << user_phone << user_address << "\n";
	 		}
		}

		newfile.close();
		clear();
		std::cout << "User information modified successfully!\n\n";
	}
	else {
		clear();
		std::cout << "Returned to previous page.\n\n";
	}

	return 0;
}

//CONTINUE:: copy code from module.cpp and change variables to user variables for below functions
int User::addUserStaff()
{
	clear();
	while (!acceptable) {
		std::cout << "Enter User ID (Maximum 5 characters)\n";
		std::cout << ">> ";
		std::cin.ignore();
		std::getline(std::cin, user_input);
		if (!user_input.empty()) {
			if (user_input.length() <= 5) {
				user_id = user_input;
				acceptable = true;
			}
			else {
				clear();
				std::cout << "User ID must be at most 5 characters!\n\n"; 
			}
		}
		else {
			clear();
			std::cout << "Please input User ID!\n\n";
		}
	}
	acceptable = false;

	clear();
	while (!acceptable) {
		std::cout << "Enter User Name (Maximum 10 chatacters)\n";
		std::cout << ">> ";
		std::getline(std::cin, user_input);
		if (!user_input.empty()) {
			if (user_input.length() <= 10) {
				user_name = user_input;
				acceptable = true;
			}
			else {
				clear();
				std::cout << "User Name must be at most 10 characters!\n\n"; 
			}
		}
		else {
			clear();
			std::cout << "Please input User Name!\n\n";
		}
	}
	acceptable = false;

	clear();
	while (!acceptable) {
		std::cout << "Enter User Password (Maximum 8 characters)\n";
		std::cout << ">> ";
		std::getline(std::cin, user_input);
		if (!user_input.empty()) {
			if (user_input.length() <= 8) {
				user_password = user_input;
				acceptable = true;
			}
			else {
				clear();
				std::cout << "User Password must be at most 8 characters!\n\n"; 
			}
		}
		else {
			clear();
			std::cout << "Please input User Password!\n\n";
		}
	}
	acceptable = false;

	clear();
	while (!acceptable) {
		std::cout << "Enter User Category:\n";
		std::cout << "1. Staff\n";
		std::cout << "2. Teacher\n";
		std::cout << "3. Student\n\n";
		std::cout << ">> ";
		std::cin >> user_input;
		if (user_input.std::string::compare("1") == 0) {
			user_category = "staff";
			acceptable = true;
		}
		else if (user_input.std::string::compare("2") == 0) {
			user_category = "teacher";
			acceptable = true;
		}
		else if (user_input.std::string::compare("3") == 0) {
			user_category = "student";
			acceptable = true;
		}
		else {
			clear();
			std::cout << "Invalid input!\n\n";
		}
	}
	acceptable = false;

	clear();
	while (!acceptable) {
		std::cout << "Enter User Phone (Maximum 14 characters)\n";
		std::cout << ">> ";
		std::cin.ignore();
		std::getline(std::cin, user_input);
		if (!user_input.empty()) {
			if (user_input.length() <= 14) {
				user_phone = user_input;
				acceptable = true;
			}
			else {
				clear();
				std::cout << "User Phone must be at most 14 characters!\n\n"; 
			}
		}
		else {
			clear();
			std::cout << "Please input User Phone!\n\n";
		}
	}
	acceptable = false;

	clear();
	while (!acceptable) {
		std::cout << "Enter User Address (Maximum 10 characters)\n";
		std::cout << ">> ";
		std::getline(std::cin, user_input);
		if (!user_input.empty()) {
			if (user_input.length() <= 10) {
				user_address = user_input;
				acceptable = true;
			}
			else {
				clear();
				std::cout << "User Address must be at most 10 characters!\n\n"; 
			}
		}
		else {
			clear();
			std::cout << "Please input User Address!\n\n";
		}
	}
	acceptable = false;

	std::fstream newfile;
 	newfile.open("user.txt", std::ios::in);
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

	newfile.open("user.txt", std::ios::out);
 	if (newfile.fail()) {
 		std::cout << "Error opening file." << "\n";
 		return 1; //tells terminal there is an error
 	}

 	for (int i = 0; i < last_line_number + 1; i++) {
 		if (i != last_line_number) {
			newfile << file_lines[i] << "\n";
 		}
 		else {
		 	//newfile << std::left << std::setw(5) << module_index
		 	newfile << std::left << std::setw(10) << user_id
		 	<< std::left << std::setw(12) << user_name 
		 	<< std::left << std::setw(10) << user_password
		 	<< std::left << std::setw(11) << user_category
		 	<< std::left << std::setw(16) << user_phone << user_address << "\n";
 		}
	}

	newfile.close();
	clear();
	std::cout << "User added successfully!\n\n";

	return 0;
}

int User::deleteUserStaff()
{
	clear();
	displayUserInfo();

	std::cout << "Enter index of information to be deleted. (Enter 0 to return to previous page)\n\n";
	std::cout << ">> ";
	std::cin >> choice;

	if (choice != 0) {
		std::fstream newfile;
 		newfile.open("user.txt", std::ios::in);
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

		newfile.open("user.txt", std::ios::out);
	 	if (newfile.fail()) {
	 		std::cout << "Error opening file." << "\n";
	 		return 1; //tells terminal there is an error
	 	}

	 	for (int i = 0; i < file_lines.size(); i++) {
	 		if (i != choice - 1) {
				newfile << file_lines[i] << "\n";
	 		}
		}

		newfile.close();
		clear();
		std::cout << "User deleted successfully!\n\n";
	}
	else {
		clear();
		std::cout << "Returned to previous page.\n\n";
	}

	return 0;
}