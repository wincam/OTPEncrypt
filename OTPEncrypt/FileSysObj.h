#pragma once
#include <string>
class FileSysObj
{
private:
	std::string filePath;
public:
	FileSysObj();
	FileSysObj(std::string filePath);
	virtual bool encrypt() = 0;
	virtual bool writeCyperText() = 0;
	virtual bool writeCyper() = 0;
};

