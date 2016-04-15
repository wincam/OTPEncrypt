// OTPEncrypt.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>

#include "FileSysObj.h"
#include "Folder.h"
#include "File.h"

void errorMessage();
void insertFile(std::string* &filePaths, int &s);

int main(int argc, char* argv[])
{
	std::string* encryptFiles = NULL;
	int encryptFilesSize = 0;
	std::string* decryptFiles = NULL;
	int decryptFilesSize = 0;

	// arg processor
	//---------------------------------------------
	// no args are supplied
	if (argc == 1) {
		errorMessage();
		return 1;
	}

	// args are supplied
	else {
		// add to file path lists
		for (int i = 1; i < argc - 1; i++) {
			struct stat info;

			//encrypt
			if (strcmp(argv[i], "encrypt") == 0) {
				i++;
				if (stat(argv[i], &info) == 0) {
					insertFile(encryptFiles, encryptFilesSize);
				}
				else
				{
					std::cout << argv[i] << " does not exist" << std::endl;
				}
			}
			//decrypt
			else if (strcmp(argv[i], "decrypt") == 0) {
				i++;
				if (stat(argv[i], &info) == 0) {
					insertFile(decryptFiles, decryptFilesSize);
				}
				else
				{
					std::cout << argv[i] << " does not exist" << std::endl;
				}
			}
			//neither, print error
			else
			{
				errorMessage();
				return 1;
			}
		}
	}

    return 0;
}
// Prints error message and shows how to use
void errorMessage() {
	std::cout << "Improper Use" << std::endl <<
		"encrypt \"FILEPATH\" or decrypt \"FILEPATH\" " << std::endl;
}

// inserts file into file path array
void insertFile(std::string* &filePaths, int &s) {
	std::string* newFilePaths = new std::string [s + 1];
	for (int i = 0; i < s; i++)
	{
		newFilePaths[i] = filePaths[i];
	}
	if (s != 0) {
		delete[] filePaths;
	}

	s++;
	filePaths = newFilePaths;
}


