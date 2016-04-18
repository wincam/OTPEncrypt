#include "Folder.h"
#include "File.h"
#include "dirent\dirent.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <iostream>

void otp::Folder::readFile(FileOperation op)
{
	this->errorState = false;
	FileSysObj::setOperation(op);

	if (this->subObjectsCount != 0) {
		delete[] this->subObjects;
	}
	this->subObjectsCount = 0;


	// open folder
	DIR           *d;
	struct dirent *dir;

	d = opendir(this->getFilePath().c_str());
	if (d)
	{
		//skip . and ..
		readdir(d);
		readdir(d);

		struct stat info;
		std::string filePath;
		// read folder contents
		while ((dir = readdir(d)) != NULL)
		{
			std::cout << dir->d_name << std::endl;
			//get type
			switch (this->getOperation())
			{
			case otp::decrypt:
				filePath = this->getCypherTextFilePath() + "\\" + dir->d_name;
				break;
			case otp::encrypt:
				filePath = this->getFilePath() + "\\" + dir->d_name;
				break;
			default:
				filePath = "";
				break;
			}

			if (stat(filePath.c_str(), &info) != 0) {
				this->errorState = true;
				break;
			}

			// object type
			// folder
			
			if (info.st_mode & S_IFDIR)
			{
				addNewObject(new Folder(this->getFilePath() + "\\" + dir->d_name, this->getCypherFilePath() + "\\" + dir->d_name, this->getCypherTextFilePath() + "\\" + dir->d_name, this->getOperation()));
			}
			// file
			else if (info.st_mode & S_IFREG)
			{
				addNewObject(new File(this->getFilePath() + "\\" + dir->d_name, this->getCypherFilePath() + "\\" + dir->d_name, this->getCypherTextFilePath() + "\\" + dir->d_name, this->getOperation()));
			}
			// neither error
			else
			{
				this->errorState = true;
				break;
			}
		}
		// close folder
		closedir(d);
	}
	else
	{
		this->errorState = true;
	}


}

void otp::Folder::addNewObject(FileSysObj * object)
{
	FileSysObj** newObjectList = new FileSysObj*[this->subObjectsCount + 1];
	// copy from old array to new one
	for (unsigned long i = 0; i < this->subObjectsCount; i++)
	{
		newObjectList[i] = this->subObjects[i];
	}

	// add new element
	newObjectList[this->subObjectsCount] = object;

	// deallocate
	if (this->subObjectsCount != 0) {
		delete[] this->subObjects;
	}

	this->subObjectsCount++;
	this->subObjects = newObjectList;
}

otp::Folder::Folder(std::string filePath, std::string cypherFilePath, std::string cypherTextFilePath, FileOperation op) : FileSysObj(filePath, cypherFilePath, cypherTextFilePath)
{
	this->subObjectsCount = 0;
	readFile(op);
}

otp::Folder::Folder(otp::FilePathSet files, FileOperation op) : FileSysObj(files)
{
	this->subObjectsCount = 0;
	readFile(op);
}

otp::Folder::~Folder()
{
	if (this->subObjectsCount != 0) {
		delete[] this->subObjects;
	}
}

bool otp::Folder::isError()
{
	bool error = this->errorState;
	// check all others
	for (unsigned long i = 0; i < this->subObjectsCount; i++)
	{
		error = error && this->subObjects[i][0].isError();
	}
	return error;
}

void otp::Folder::setOperation(FileOperation op)
{
	readFile(op);
}

void otp::Folder::setFilePath(std::string filePath)
{
	FileSysObj::setFilePath(filePath);
	readFile(this->getOperation());
}

void otp::Folder::setCypherFilePath(std::string filePath)
{
	FileSysObj::setCypherFilePath(filePath);
	readFile(this->getOperation());
}

void otp::Folder::setCypherTextFilePath(std::string filePath)
{
	FileSysObj::setCypherTextFilePath(filePath);
	readFile(this->getOperation());
}

bool otp::Folder::encrypt()
{
	return false;
}

bool otp::Folder::decrypt()
{
	return false;
}

bool otp::Folder::writeFile(std::string alternateFilePath)
{
	return false;
}

bool otp::Folder::writeCyperText(std::string alternateFilePath)
{
	return false;
}

bool otp::Folder::writeCyper(std::string alternateFilePath)
{
	return false;
}
