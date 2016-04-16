#pragma once
#include "FileSysObj.h"
#include <string>


namespace otp {

	class File : public FileSysObj
	{
	private:
		FileOperation operation;
		unsigned long size;
		bool errorState;
		bool cypherSupplied;
		char* fileBytes;
		char* fileCypherBytes;
		char* fileCypherTextBytes;

		void readFile(FileOperation op);	// inializer helper
		void allocFile();	// inializer allocation helper
		void deallocFile();	// desturctor deallocation helper

	public:
		File(std::string filePath, FileOperation op);
		File(std::string filePath, std::string cypherFilePath, std::string cypherTextFilePath, FileOperation op);
		~File();

		bool is_error();

		virtual void setFilePath(std::string filePath) override;
		virtual void setCypherFilePath(std::string filePath) override;
		virtual void setCypherTextFilePath(std::string filePath) override;

		virtual bool encrypt() override;
		virtual bool decrypt() override;
		virtual bool writeFile(std::string alternateFilePath = "") override;
		virtual bool writeCyperText(std::string alternateFilePath = "") override;
		virtual bool writeCyper(std::string alternateFilePath = "") override;
	};
}
