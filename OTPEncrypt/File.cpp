#include "File.h"
#include <random>
#include <fstream>



void otp::File::readFile(FileOperation op)
{
	this->errorState = false;
	this->operation = op;

	std::ifstream inFile;
	std::ifstream inCypherFile;
	std::ifstream inCypherTextFile;

	inFile.open(FileSysObj::getFilePath(), std::ios::binary | std::ios::ate);
	inCypherFile.open(FileSysObj::getCypherFilePath(), std::ios::binary);
	inCypherTextFile.open(FileSysObj::getCypherTextFilePath(), std::ios::binary | std::ios::ate);

	switch (this->operation)
	{
	case otp::encrypt:

		if (!inFile.is_open()) {
			this->errorState = true;
			break;
		}
		else
		{
			this->size = inFile.tellg();
			inFile.seekg(std::ios::beg);
			allocFile();
			//read file
			for (unsigned long i = 0; i < this->size; i++)
			{
				inFile.read(&fileBytes[i], sizeof(char));
			}
		}
		//read cypher
		if (inCypherFile.is_open()) {
			//read file
			for (unsigned long i = 0; i < this->size; i++)
			{
				inCypherFile.read(&fileCypherBytes[i], sizeof(char));
			}
			this->cypherSupplied = true;
		}
		else
		{
			this->cypherSupplied = false;
		}
		break;

	case otp::decrypt:

		if (!(inCypherTextFile.is_open() || inCypherFile.is_open())) {
			this->errorState = true;
			this->cypherSupplied = true;
			break;
		}
		else
		{
			this->size = inCypherTextFile.tellg();
			inCypherTextFile.seekg(std::ios::beg);
			allocFile();
			this->cypherSupplied = true;
			//read file
			for (unsigned long i = 0; i < this->size; i++)
			{
				inCypherTextFile.read(&fileCypherTextBytes[i], sizeof(char));
				inCypherFile.read(&fileCypherBytes[i], sizeof(char));
			}
		}
		break;

	default:
		break;
	}

	
	inFile.close();
	inCypherFile.close();
	inCypherTextFile.close();
}

void otp::File::allocFile()
{
	//alloc file
	this->fileBytes = new char[this->size];
	this->fileCypherBytes = new char[this->size];
	this->fileCypherTextBytes = new char[this->size];
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
	if (!this->errorState) {
		delete[] this->fileBytes;
		delete[] this->fileCypherBytes;
		delete[] this->fileCypherTextBytes;
	}	
}

bool otp::File::encrypt()
{
	if ((this->operation != otp::encrypt)||this->errorState||(!this->cypherSupplied)) {
		return false;
	}

	return false;
	
}

bool otp::File::decrypt()
{
	if ((this->operation != otp::decrypt)||this->errorState) {
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
