#include "Folder.h"
#include "dirent.h"
#include <iostream>

void otp::Folder::readFile(FileOperation op)
{
	//TODO: make useful
	std::cout << this->getFilePath();
	DIR           *d;
	struct dirent *dir;
	//char dirlist[] = {};
	int i = 0;
	d = opendir(this->getFilePath().c_str());
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
		{
			i++;
			std::cout<<dir->d_name<<std::endl;
			//dirlist[i] = *dir->d_name;
		}
		//std::cout << dirlist << std::endl;

		closedir(d);
	}


}

otp::Folder::Folder(std::string filePath, std::string cypherFilePath, std::string cypherTextFilePath, FileOperation op) : FileSysObj(filePath, cypherFilePath, cypherTextFilePath)
{
	readFile(op);
}

otp::Folder::Folder(otp::FilePathSet files, FileOperation op) : FileSysObj(files)
{
	readFile(op);
}

otp::Folder::~Folder()
{
}

bool otp::Folder::isError()
{
	return false;
}

void otp::Folder::setOperation(FileOperation op)
{
}

void otp::Folder::setFilePath(std::string filePath)
{
}

void otp::Folder::setCypherFilePath(std::string filePath)
{
}

void otp::Folder::setCypherTextFilePath(std::string filePath)
{
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
