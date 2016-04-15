#pragma once
#include "FileSysObj.h"
#include <string>


namespace otp {

	class File : public FileSysObj
	{
	private:
		FileOperation operation;
		unsigned long size;
		char* fileBytes;
		char* fileCypherBytes;
		char* fileCypherTextBytes;
		
		void readFile(FileOperation op);	// inializer helper
	public:
		File(std::string filePath, FileOperation op);
		File(std::string filePath, std::string cypherFilePath, std::string cypherTextFilePath, FileOperation op);
		~File();

		virtual bool encrypt() override;
		virtual bool decrypt() override;
		virtual bool writeCyperText() override;
		virtual bool writeCyper() override;
	};
}
