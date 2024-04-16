// hospital_management.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <sqlite3.h>

// function to execute SQL query
static int callback(void* NotUsed, int argc, char** argv, char** azColName)
{
	for (int i = 0; i < argc; i++)
	{
		std::cout << azColName[i] << ": " << (argv[i] ? argv[i] : "NULL") << std::endl;
	}
	return 0;
}

int main()
{
	sqlite3* db;
	char* zErrMsg = 0;
	int rc; 

	// open database 
	rc = sqlite_open("hospital.db", &db);
	if (rc) {
		std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
		return (0);
	} 
	else
	{
		std::cout << "Opened database successfully" << std::endl;
	}

	// Create SQL statement 
	const char* sql = "CREATE TABLE PATIENTS (" \
		"ID INT PRIMARY KEY NOT NULL," \
		"NAME TEXT NOT NULL," \
		"AGE INT NOT NULL," \
		"GENDER CHAR(1)," \
		"ADDRESS CHAR(50));"

		// Execute SQL statement
	rc = sqlite_exec(db, sql, callback, 0, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		std::cerr << "SQL error: " << zErrMsg << std::endl;
		sqlite3_free(zErrMsg);
	}

	// close database
	sqlite_close(db);
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
