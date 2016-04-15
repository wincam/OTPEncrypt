#include "File.h"
#include <random>
#include <fstream>



void otp::File::readFile(FileOperation op)
{
	this->operation = op;

	std::ifstream infile;
	infile.open(FileSysObj::getFilePath(), std::ios::binary | std::ios::ate);
	this->size = infile.tellg();
	infile.seekg(std::ios::beg);

	//alloc file
	this->fileBytes = new char[this->size];
	this->fileCypherBytes = new char[this->size];
	this->fileCypherTextBytes = new char[this->size];

	//read file
	for (unsigned long i = 0; i < this->size; i++)
	{
		infile.read(&fileBytes[i], sizeof(char));
	}

	infile.close();
}

otp::File::File(std::string filePath, FileOperation op) : FileSysObj(filePath, filePath + "_cypher", filePath + "_cyphertext")
{
	readFile(op);
}

otp::File::File(std::string filePath, std::string cypherFilePath, std::string cypherTextFilePath, FileOperation op) : FileSysObj(filePath, cypherFilePath, cypherTextFilePath)
{
	readFile(op);
}


otp::File::~File()
{
	delete[] this->fileBytes;
	delete[] this->fileCypherBytes;
	delete[] this->fileCypherTextBytes;
}

bool otp::File::encrypt()
{
	if (this->operation != otp::encrypt) {
		return false;
	}

	return false;
	
}

bool otp::File::decrypt()
{
	if (this->operation != otp::decrypt) {
		return false;
	}
	return false;
}

bool otp::File::writeCyperText()
{
	return false;
}

bool otp::File::writeCyper()
{
	return false;
}
