#include "FileSysObj.h"



FileSysObj::FileSysObj()
{
	this->filePath= "";
}

FileSysObj::FileSysObj(std::string filePath)
{
	this->filePath = filePath;
}
