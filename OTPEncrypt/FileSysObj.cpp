#include "FileSysObj.h"



otp::FileSysObj::FileSysObj(std::string filePath, std::string cypherFilePath, std::string cypherTextFilePath)
{
	this->filePath = filePath;
	this->cypherFilePath = cypherFilePath;
	this->cypherTextFilePath = cypherTextFilePath;
}

std::string otp::FileSysObj::getFilePath()
{
	return this->filePath;
}

std::string otp::FileSysObj::getCypherFilePath()
{
	return this->cypherFilePath;
}

std::string otp::FileSysObj::getCypherTextFilePath()
{
	return this->cypherTextFilePath;
}

void otp::FileSysObj::setFilePath(std::string filePath)
{
	this->filePath = filePath;
}

void otp::FileSysObj::setCypherFilePath(std::string filePath)
{
	this->cypherFilePath = filePath;
}

void otp::FileSysObj::setCypherTextFilePath(std::string filePath)
{
	this->cypherTextFilePath = filePath;
}
