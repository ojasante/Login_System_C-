	//Include below code to create/reset user.txt and module.txt

	/**std::fstream newfile;
	newfile.open("user.txt", std::ios::out);
	if (newfile.is_open()) {
	 	//newfile << std::left << std::setw(5) << '1'
	 	newfile << std::left << std::setw(10) << "SF001" 
	 	<< std::left << std::setw(12) << "Oliver" 
	 	<< std::left << std::setw(10) << "12345"
	 	<< std::left << std::setw(11) << "staff"
	 	<< std::left << std::setw(16) << "08176812333" << "Suzhou\n";

	 	//newfile << std::left << std::setw(5) << '2'
	 	newfile << std::left << std::setw(10) << "TC001"
	 	<< std::left << std::setw(12) << "Enrico"
	 	<< std::left << std::setw(10) << "67890"
	 	<< std::left << std::setw(11) << "teacher"
	 	<< std::left << std::setw(16) << "12345678910" << "Suzhou\n";

	 	//newfile << std::left << std::setw(5) << '3'
	 	newfile << std::left << std::setw(10) << "ST001"
	 	<< std::left << std::setw(12) << "Avery"
	 	<< std::left << std::setw(10) << "12345"
	 	<< std::left << std::setw(11) << "student"
	 	<< std::left << std::setw(16) << "12345678910" << "Shanghai\n";

	 	//newfile << std::left << std::setw(5) << '4'
	 	newfile << std::left << std::setw(10) << "ST002"
	 	<< std::left << std::setw(12) << "Cash"
	 	<< std::left << std::setw(10) << "12345"
	 	<< std::left << std::setw(11) << "student"
	 	<< std::left << std::setw(16) << "12345678910" << "Shanghai\n"; 	


	 	newfile.close();
	 }

	//NOTE: Module name can't have whitespace or the system will consider them as different variables
	newfile.open("module.txt", std::ios::out);
 	if (newfile.is_open()) {
	 	//newfile << std::left << std::setw(5) << '1'
	 	newfile << std::left << std::setw(10) << "DTS102TC" 
	 	<< std::left << std::setw(17) << "C++" 
	 	<< std::left << std::setw(10) << "TC001"
	 	<< std::left << std::setw(10) << "ST001"
	 	<< std::left << std::setw(5) << "90" << "Released\n";

	 	//newfile << std::left << std::setw(5) << '2'
	 	newfile << std::left << std::setw(10) << "DTS102TC" 
	 	<< std::left << std::setw(17) << "C++" 
	 	<< std::left << std::setw(10) << "TC001"
	 	<< std::left << std::setw(10) << "ST002"
	 	<< std::left << std::setw(5) << "92" << "Released\n";

	 	newfile.close();
 	}**/