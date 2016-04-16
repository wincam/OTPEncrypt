#pragma once
#include <string>
namespace otp {

	enum FileOperation { encrypt, decrypt };

	class FileSysObj
	{
	private:
		std::string filePath;
		std::string cypherFilePath;
		std::string cypherTextFilePath;
	public:
		FileSysObj(std::string filePath, std::string cypherFilePath, std::string cypherTextFilePath);

		std::string getFilePath();
		std::string getCypherFilePath();
		std::string getCypherTextFilePath();

		virtual void setFilePath(std::string filePath);
		virtual void setCypherFilePath(std::string filePath);
		virtual void setCypherTextFilePath(std::string filePath);

		virtual bool encrypt() = 0;
		virtual bool decrypt() = 0;
		virtual bool writeFile(std::string alternateFilePath = "") = 0;
		virtual bool writeCyperText(std::string alternateFilePath = "") = 0;
		virtual bool writeCyper(std::string alternateFilePath = "") = 0;
	};

}