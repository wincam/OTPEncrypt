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
void insertFile(struct FileData newfile, struct  FileData* &files, int &s);

/**
* OTPEncrypt
* FileSysObjTyp
* Represents a file or folder
*
* @author Cameron Nicolle
* @version 1.0
* @since 4/18/2016
*/
enum FileSysObjTyp{ file, folder };

/**
* OTPEncrypt
* FileData
* Contains all data about file system object
*
* @author Cameron Nicolle
* @version 1.0
* @since 4/18/2016
*/
struct FileData
{
	struct otp::FilePathSet filePaths;
	FileSysObjTyp type;
};

int main(int argc, char* argv[])
{
	struct  FileData* encryptFiles = NULL;
	int encryptFilesSize = 0;
	struct  FileData* decryptFiles = NULL;
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
		struct stat info[2];
		struct FileData files;
		// add to file path lists
		for (int i = 1; i < argc - 1; i++) {
			

			//encrypt
			if (strcmp(argv[i], "encrypt") == 0) {
				if (stat(argv[i + 1], &info[0]) == 0) {
					// add file
					files.filePaths.file = argv[i + 1];

					// object type
					// folder
					if (info[0].st_mode & S_IFDIR)
					{
						files.type = folder;
					}
					// file
					else if (info[0].st_mode & S_IFREG)
					{
						files.type = file;
					}
					// neither error
					else
					{
						errorMessage();
						return 1;
					}
					
					// add cypher file
					if ((i + 2 < argc) && (!(strcmp(argv[i + 2], "decrypt") == 0 || strcmp(argv[i + 2], "encrypt") == 0))) {
						files.filePaths.cypherFile = argv[i + 2];
						// add cypher text file
						if ((i + 3 < argc) && (!(strcmp(argv[i + 3], "decrypt") == 0 || strcmp(argv[i + 3], "encrypt") == 0))) {
							files.filePaths.cypherTextFile = argv[i + 3];
							i += 3;
						}
						else
						{
							i += 2;
							files.filePaths.cypherTextFile = "";
						}
					}
					else
					{
						i++;
						files.filePaths.cypherFile = "";
						files.filePaths.cypherTextFile = "";
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
				if ((stat(argv[i + 1], &info[0]) == 0) && (i + 2 < argc) && (stat(argv[i + 2], &info[1]) == 0)) {
					files.filePaths.cypherTextFile = argv[i + 1];
					files.filePaths.cypherFile = argv[i + 2];

					// object type
					// folder
					if ((info[0].st_mode & S_IFDIR) && (info[1].st_mode & S_IFDIR))
					{
						files.type = folder;
					}
					// file
					else if ((info[0].st_mode & S_IFREG) && (info[1].st_mode & S_IFREG))
					{
						files.type = file;
					}
					// neither error
					else
					{
						errorMessage();
						return 1;
					}

					// add file
					if ((i + 3 < argc) && (!(strcmp(argv[i + 3], "decrypt") == 0 || strcmp(argv[i + 3], "encrypt") == 0))) {
						files.filePaths.file = argv[i + 3];
						i += 3;
					}
					else
					{
						i += 2;
						files.filePaths.file = "";
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
		//check type
		switch (encryptFiles[i].type)
		{
		case folder:
			filesToEncrypt[i] = new otp::Folder(encryptFiles[i].filePaths, otp::encrypt);
			break;
		case file:
			filesToEncrypt[i] = new otp::File(encryptFiles[i].filePaths, otp::encrypt);
			break;
		default:
			errorMessage();
			return 1;
			break;
		}
		filesToEncrypt[i]->encrypt();
		filesToEncrypt[i]->writeCyper();
		filesToEncrypt[i]->writeCyperText();
	}

	//file decrypting
	otp::FileSysObj** filesToDecrypt = new otp::FileSysObj*[decryptFilesSize];

	for (int i = 0; i < decryptFilesSize; i++)
	{
		//check type
		switch (encryptFiles[i].type)
		{
		case folder:
			filesToDecrypt[i] = new otp::Folder(decryptFiles[i].filePaths, otp::decrypt);
			break;
		case file:
			filesToDecrypt[i] = new otp::File(decryptFiles[i].filePaths, otp::decrypt);
			break;
		default:
			errorMessage();
			return 1;
			break;
		}
		filesToDecrypt[i]->decrypt();
		filesToDecrypt[i]->writeFile();
	}


    return 0;
}

void errorMessage() {
	std::cout << "Improper Use" << std::endl <<
		"encrypt \"FILEPATH\"  \"CYPHER FILEPATH\"(Optional) \"OUTPUT ENCYPTED FILE FILEPATH\"(Optional)  or decrypt \"FILE TO DECYPT FILEPATH\" \"CYPHER FILEPATH\"  \"OUTPUT DECYPTED FILE FILEPATH\"(Optional) " << std::endl;
}

void insertFile(struct FileData newfile, struct  FileData* &files, int &s) {
	struct  FileData* newFiles = new struct FileData[s + 1];
	// copy from old array to new one
	for (int i = 0; i < s; i++)
	{
		newFiles[i] = files[i];
	}
	newFiles[s] = newfile;
	if (s != 0) {
		delete[] files;
	}

	s++;
	files = newFiles;
}


