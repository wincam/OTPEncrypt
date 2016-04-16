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
			this->cypherSupplied = false;
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

void otp::File::deallocFile()
{
	delete[] this->fileBytes;
	delete[] this->fileCypherBytes;
	delete[] this->fileCypherTextBytes;
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
		deallocFile();
	}	
}

bool otp::File::is_error()
{
	return this->errorState;
}

void otp::File::setFilePath(std::string filePath)
{
	FileSysObj::setFilePath(filePath);
	//reprocess file
	if (this->operation = otp::encrypt) {
		deallocFile();
		readFile(this->operation);
	}
}

void otp::File::setCypherFilePath(std::string filePath)
{
	FileSysObj::setCypherFilePath(filePath);
	//reprocess file
	std::ifstream inCypherFile;
	inCypherFile.open(FileSysObj::getCypherFilePath(), std::ios::binary);
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
}

void otp::File::setCypherTextFilePath(std::string filePath)
{
	FileSysObj::setCypherTextFilePath(filePath);
	//reprocess file
	if (this->operation = otp::decrypt) {
		deallocFile();
		readFile(this->operation);
	}
}

bool otp::File::encrypt()
{
	if ((this->operation != otp::encrypt)||this->errorState) {
		return false;
	}
	//generate cypher
	if (!this->cypherSupplied) {
		for (unsigned long i = 0; i < this->size; i++)
		{
			this->fileCypherBytes[i] = rand();
		}
	}

	// add cypher to file using modular addition
	for (unsigned long i = 0; i < this->size; i++)
	{
		this->fileCypherTextBytes[i] = this->fileBytes[i] + this->fileCypherBytes[i];
	}

	return true;
	
}

bool otp::File::decrypt()
{
	if ((this->operation != otp::decrypt)||this->errorState||(!this->cypherSupplied)) {
		return false;
	}
	// add cypher to file using modular addition
	for (unsigned long i = 0; i < this->size; i++)
	{
		this->fileBytes[i] = this->fileCypherTextBytes[i] - this->fileCypherBytes[i];
	}


	return true;
}

bool otp::File::writeFile(std::string alternateFilePath)
{
	if (this->errorState) {
		return false;
	}
	// open and write
	std::ofstream outfile(alternateFilePath == "" ? this->getFilePath() : alternateFilePath, std::ios::binary);
	for (unsigned long i = 0; i < this->size; i++)
	{
		outfile.write(&fileBytes[i], sizeof(char));
	}
	outfile.close();
	return true;
}

bool otp::File::writeCyperText(std::string alternateFilePath)
{
	if (this->errorState) {
		return false;
	}
	// open and write
	std::ofstream outfile(alternateFilePath == "" ? this->getCypherTextFilePath() : alternateFilePath, std::ios::binary);
	for (unsigned long i = 0; i < this->size; i++)
	{
		outfile.write(&fileCypherTextBytes[i], sizeof(char));
	}
	outfile.close();
	return true;
}

bool otp::File::writeCyper(std::string alternateFilePath)
{
	if (this->errorState) {
		return false;
	}
	// open and write
	std::ofstream outfile(alternateFilePath == "" ? this->getCypherFilePath() : alternateFilePath, std::ios::binary);
	for (unsigned long i = 0; i < this->size; i++)
	{
		outfile.write(&fileCypherBytes[i], sizeof(char));
	}
	outfile.close();
	return true;
}
