// OTPEncrypt.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>

void errorMessage();

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
		for (int i = 1; i < argc - 1; i++) {
			struct stat info;

			if (argv[i] == "encrypt") {
				i++;
				if (stat(argv[i], &info) == 0) {
					//TODO add to list
				}
			}
			else if (argv[i] == "decrypt") {
				i++;
				if (stat(argv[i], &info) == 0) {
					//TODO add to list
				}
			}

			else
			{
				errorMessage();
				return 1;
			}
		}
	}

    return 0;
}

void errorMessage() {
	std::cout << "Improper Use" << std::endl <<
		"encrypt \"FILEPATH\" or decrypt \"FILEPATH\" ";
}


