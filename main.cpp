/**#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>**/
//#include "user.h"
#include "module.h"
//using namespace std;

int choice;

int main() {
	std::fstream newfile;

	//CONTINUE: use user.clear() to decorate code!
	User user;
	Module module;
	std::string input_id, input_password;

	std::cout << "Please enter user id: ";
	std::cin >> input_id;
	std::cout << "Please enter user password: ";
	std::cin >> input_password;

	user.login(input_id, input_password);

	if (!loggedIn) {
		user.clear();
		std::cout << "Login failed! Please try again.\n";
	}

	while (loggedIn) {
		switch (user.identifyStatus(user_category)) {
		case 'S':
			user.clear();
			std::cout << "Welcome " << user_name << "!\n\n";
			do {
                std::cout << "=========================== MENU ===========================" << "\n\n";
                std::cout << "1. Modify personal information" << "\n";
                std::cout << "2. View your module information" << "\n";
                std::cout << "3. Logout" << "\n\n";
                std::cout << "============================================================" << "\n\n";
                std::cout << ">> ";
                std::cin >> choice;
                user.clear();

                switch (choice) {
                case 1:
                	user.modifyInfo(user_line_number);
                	break;
                case 2:
                	module.viewModuleStudent();
                	break;
                case 3:
                	loggedIn = false;
                	break;
                default:
                	user.clear();
                	std::cout << "Invalid choice!\n\n";
                	break;
                }
			} while (choice != 3);
			break;

		case 'T':
			user.clear();
			std::cout << "Welcome " << user_name << "!\n\n";
			do {
                std::cout << "=========================== MENU ===========================" << "\n\n";
                std::cout << "1. Modify personal information" << "\n";
                std::cout << "2. View your module information" << "\n";
                std::cout << "3. Logout" << "\n\n";
                std::cout << "============================================================" << "\n\n";
                std::cout << ">> ";
                std::cin >> choice;
                user.clear();

                switch (choice) {
                case 1:
                	user.modifyInfo(user_line_number);
                	break;
                case 2:
                	module.viewModuleTeacher();
                	std::cout << "Select index number of student ID to modify grade. (Enter 0 to return to homepage)\n";
                	std::cout << ">> ";
                	int index_num;
                	std::cin >> index_num;

                	if (index_num != 0) {
						module.modifyModuleTeacher(index_num);
                	}
                	else {
                		user.clear();
                	}
                	break;
                case 3:
                	loggedIn = false;
                	break;
                default:
                	user.clear();
                	std::cout << "Invalid choice!\n\n";
                	break;
                }
			} while (choice != 3);
			break;
		case 'F':
			user.clear();
			std::cout << "Welcome " << user_name << "!\n\n";
			do {
                std::cout << "=========================== MENU ===========================" << "\n\n";
                std::cout << "1. Modify personal information" << "\n";
                std::cout << "2. Modify user database" << "\n";
                std::cout << "3. Modify module database" << "\n";
                std::cout << "4. Logout" << "\n\n";
                std::cout << "============================================================" << "\n\n";
                std::cout << ">> ";
                std::cin >> choice;
                user.clear();

                switch (choice) {
                case 1:
                	user.modifyInfo(user_line_number);
                	break;
                case 2:
                	do {
		                std::cout << "=========================== OPTIONS ===========================" << "\n\n";
		                std::cout << "1. Modify/Delete user information" << "\n";
		                std::cout << "2. Add user" << "\n";
		                std::cout << "3. Return" << "\n\n";
		                std::cout << "===============================================================" << "\n\n";
		                std::cout << ">> ";
		                std::cin >> choice;
		                user.clear();

		                switch (choice) {
		                case 1:
		                	//consider even out the spacing in displayModuleInfo()
		                	do {
		                		user.displayUserInfo();
		                		std::cout << "-------------------------------------------------------------\n\n";
				                std::cout << "=========================== OPTIONS ===========================" << "\n\n";
				                std::cout << "1. Modify user information" << "\n";
				                std::cout << "2. Delete user information" << "\n";
				                std::cout << "3. Return" << "\n\n";
				                std::cout << "===============================================================" << "\n\n";
				                std::cout << ">> ";
				                std::cin >> choice;
				                user.clear();

				                switch (choice) {
				                case 1:
				                	user.modifyUserStaff();
				                	break;
				                case 2:
				                	user.deleteUserStaff();
				                	break;
				                case 3:
				                	user.clear();
				                	break;
				                default:
				                	user.clear();
				                	std::cout << "Invalid choice!\n\n";
				                	break;
				                }
			                } while (choice != 3);
			                break;
			            case 2:
			            	user.addUserStaff();
			            	break;
			            case 3:
			            	user.clear();
			            	break;
			            default:
			            	user.clear();
			            	std::cout << "Invalid choice!\n\n";
			            	break;
			            }
			        } while (choice != 3);
                	break;
                case 3:
                	do {
                		module.displayModuleInfo();
                		std::cout << "-------------------------------------------------------------\n\n";
		                std::cout << "=========================== OPTIONS ===========================" << "\n\n";
		                std::cout << "1. Modify/Delete module information" << "\n";
		                std::cout << "2. Add module" << "\n";
		                std::cout << "3. Return" << "\n\n";
		                std::cout << "===============================================================" << "\n\n";
		                std::cout << ">> ";
		                std::cin >> choice;
		                user.clear();

		                switch (choice) {
		                case 1:
		                	do {
		                		module.displayModuleInfo();
		                		std::cout << "-------------------------------------------------------------\n\n";
				                std::cout << "=========================== OPTIONS ===========================" << "\n\n";
				                std::cout << "1. Modify module information" << "\n";
				                std::cout << "2. Delete module information" << "\n";
				                std::cout << "3. Release/Hide module grade status" << "\n";
				                std::cout << "4. Return" << "\n\n";
				                std::cout << "===============================================================" << "\n\n";
				                std::cout << ">> ";
				                std::cin >> choice;

				                switch (choice) {
				                case 1:
				                	module.modifyModuleStaff();
				                	break;
				                case 2:
				                	module.deleteModuleStaff();
				                	break;
				                case 3:
				                	module.releaseModuleStaff();
				                	break;
				                case 4:
				                	user.clear();
				                	break;
				                default:
				                	user.clear();
				                	std::cout << "Invalid choice!\n\n";
				                	break;
				                }
			                } while (choice != 4);
		                	break;
		                case 2:
		                	module.addModuleStaff();
		                	break;
		                case 3:
		                	user.clear();
		                	break;
		                default:
		                	user.clear();
		                	std::cout << "Invalid choice!\n\n";
		                	break;
		                } 
                	} while (choice != 3);
                	break;
            	case 4:
                	loggedIn = false;
                	break;
                default:
                	user.clear();
                	std::cout << "Invalid choice!\n\n";
                	break;
                }
			} while (choice != 4);
			break;
		} 
	}

	return 0;
}