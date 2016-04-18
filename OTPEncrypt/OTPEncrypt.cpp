/**
* OTPEncrypt
* OTPEncrypt.cpp
* Uses one time pad encryption to encrypt and decrypt files
*
* @author Cameron Nicolle
* @version 1.0
* @since 4/15/2016
*/

#include <iostream>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>

#include "FileSysObj.h"
#include "Folder.h"
#include "File.h"

/**
* errorMessage
* Prints error message
*/
void errorMessage();
/**
* insertFile
* Adds new file path set to list
* @param newFilePath	New file path set
* @param filePaths		List of file path sets
* @param s				Size of of the list of file path sets
*/
void insertFile(struct otp::FilePathSet newFilePath, struct  otp::FilePathSet* &filePaths, int &s);



int main(int argc, char* argv[])
{
	struct  otp::FilePathSet* encryptFiles = NULL;
	int encryptFilesSize = 0;
	struct  otp::FilePathSet* decryptFiles = NULL;
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
		struct otp::FilePathSet files;
		// add to file path lists
		for (int i = 1; i < argc - 1; i++) {
			

			//encrypt
			if (strcmp(argv[i], "encrypt") == 0) {
				if (stat(argv[i + 1], &info) == 0) {
					// add file
					files.file = argv[i + 1];
					
					// add cypher file
					if ((i + 2 < argc) && (!(strcmp(argv[i + 2], "decrypt") == 0 || strcmp(argv[i + 2], "encrypt") == 0))) {
						files.cypherFile = argv[i + 2];
						// add cypher text file
						if ((i + 3 < argc) && (!(strcmp(argv[i + 3], "decrypt") == 0 || strcmp(argv[i + 3], "encrypt") == 0))) {
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
				// add cypher and cypher text files
				if ((stat(argv[i + 1], &info) == 0) && (i + 2 < argc) && (stat(argv[i + 2], &info) == 0)) {
					files.cypherTextFile = argv[i + 1];
					files.cypherFile = argv[i + 2];

					// add file
					if ((i + 3 < argc) && (!(strcmp(argv[i + 3], "decrypt") == 0 || strcmp(argv[i + 3], "encrypt") == 0))) {
						files.file = argv[i + 3];
						i += 3;
					}
					else
					{
						i += 2;
						files.file = "";
					}

					insertFile(files, decryptFiles, decryptFilesSize);
					
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
	//---------------------------------------------------------------------------------------------------------
	otp::FileSysObj** filesToEncrypt = new otp::FileSysObj*[encryptFilesSize];
	
	for (int i = 0; i < encryptFilesSize; i++)
	{
		filesToEncrypt[i] = new otp::Folder(encryptFiles[i], otp::encrypt);
		/*filesToEncrypt[i][0].encrypt();
		filesToEncrypt[i][0].writeCyperText();*/
	}

	//file decrypting
	otp::FileSysObj** filesToDecrypt = new otp::FileSysObj*[decryptFilesSize];

	for (int i = 0; i < decryptFilesSize; i++)
	{
		filesToDecrypt[i] = new otp::Folder(decryptFiles[i], otp::decrypt);
		/*filesToDecrypt[i][0].decrypt();
		filesToDecrypt[i][0].writeFile();*/
	}


    return 0;
}

void errorMessage() {
	std::cout << "Improper Use" << std::endl <<
		"encrypt \"FILEPATH\"  \"CYPHER FILEPATH\"(Optional) \"OUTPUT ENCYPTED FILE FILEPATH\"(Optional)  or decrypt \"FILE TO DECYPT FILEPATH\" \"CYPHER FILEPATH\"  \"OUTPUT DECYPTED FILE FILEPATH\"(Optional) " << std::endl;
}

void insertFile(struct  otp::FilePathSet newFilePath, struct  otp::FilePathSet* &filePaths, int &s) {
	struct  otp::FilePathSet* newFilePaths = new struct otp::FilePathSet [s + 1];
	// copy from old array to new one
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


