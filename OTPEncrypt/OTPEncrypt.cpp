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
void insertFile(struct FilePathSet newFilePath, struct FilePathSet* &filePaths, int &s);

struct FilePathSet { std::string file; std::string cypherFile; std::string cypherTextFile; };

int main(int argc, char* argv[])
{
	struct FilePathSet* encryptFiles = NULL;
	int encryptFilesSize = 0;
	struct FilePathSet* decryptFiles = NULL;
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
		struct stat info;
		struct FilePathSet files;
		// add to file path lists
		for (int i = 1; i < argc - 1; i++) {
			

			//encrypt
			if (strcmp(argv[i], "encrypt") == 0) {
				if (stat(argv[i + 1], &info) == 0) {
					// add file
					files.file = argv[i + 1];
					
					// add cypher file
					if ((i + 2 > argc) && (!(strcmp(argv[i + 2], "decrypt") == 0 || strcmp(argv[i + 2], "encrypt") == 0))) {
						files.cypherFile = argv[i + 2];
						// add cypher text file
						if ((i + 3 > argc) && (!(strcmp(argv[i + 3], "decrypt") == 0 || strcmp(argv[i + 3], "encrypt") == 0))) {
							files.cypherTextFile = argv[i + 3];
							i += 3;
						}
						else
						{
							i += 2;
							files.cypherTextFile = "";
						}
					}
					else
					{
						i++;
						files.cypherFile = "";
						files.cypherTextFile = "";
					}


					insertFile(files, encryptFiles, encryptFilesSize);

				}
				else
				{
					std::cout << argv[i] << " does not exist" << std::endl;
				}
			}
			//decrypt
			else if (strcmp(argv[i], "decrypt") == 0) {
				//TODO: add input for all files
				i++;
				if (stat(argv[i], &info) == 0) {
					insertFile({"" ,"",  argv[i] }, decryptFiles, decryptFilesSize);
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

	//file encrypting
	otp::FileSysObj** filesToEncrypt = new otp::FileSysObj*[encryptFilesSize];
	
	for (int i = 0; i < encryptFilesSize; i++)
	{
		filesToEncrypt[i] = new otp::File(encryptFiles[i].file, encryptFiles[i].cypherFile, encryptFiles[i].cypherTextFile, otp::encrypt);
		filesToEncrypt[i][0].encrypt();
		filesToEncrypt[i][0].writeCyperText();
	}

	//file decrypting
	otp::FileSysObj** filesToDecrypt = new otp::FileSysObj*[decryptFilesSize];

	for (int i = 0; i < decryptFilesSize; i++)
	{
		filesToDecrypt[i] = new otp::File("test.txt", "test.txt_cypher", decryptFiles[i].cypherTextFile, otp::decrypt);
		filesToDecrypt[i][0].decrypt();
		filesToDecrypt[i][0].writeFile();
	}


    return 0;
}

// Prints error message and shows how to use
void errorMessage() {
	std::cout << "Improper Use" << std::endl <<
		"encrypt \"FILEPATH\"  \"CYPHER FILEPATH\"(Optional) \"OUTPUT ENCYPTED FILE FILEPATH\"(Optional)  or decrypt \"FILE TO DECYPT FILEPATH\" \"CYPHER FILEPATH\"  \"OUTPUT DECYPTED FILE FILEPATH\"(Optional) " << std::endl;
}

// inserts file into file path array
void insertFile(struct FilePathSet newFilePath, struct FilePathSet* &filePaths, int &s) {
	struct FilePathSet* newFilePaths = new struct FilePathSet [s + 1];
	for (int i = 0; i < s; i++)
	{
		newFilePaths[i] = filePaths[i];
	}
	newFilePaths[s] = newFilePath;
	if (s != 0) {
		delete[] filePaths;
	}

	s++;
	filePaths = newFilePaths;
}


