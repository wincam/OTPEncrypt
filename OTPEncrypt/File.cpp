#include "File.h"



File::File() : FileSysObj()
{
}

File::File(std::string filePath) : FileSysObj(filePath)
{
	
}


File::~File()
{
}

bool File::encrypt()
{
	return false;
}

bool File::writeCyperText()
{
	return false;
}

bool File::writeCyper()
{
	return false;
}
