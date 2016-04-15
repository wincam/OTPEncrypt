#pragma once
#include "FileSysObj.h"
#include <string>
class File : public FileSysObj
{
private:
	unsigned long fileBytes;
	unsigned long fileCypherBytes;
	unsigned long fileCypherTextBytes;
public:
	File();
	File(std::string filePath);
	~File();

	virtual bool encrypt() override;
	virtual bool writeCyperText() override;
	virtual bool writeCyper() override;
};

