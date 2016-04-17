#pragma once
#include "FileSysObj.h"
#include <string>

/**
* otp
* the name space used by OTPEncyrpt
*
* @author Cameron Nicolle
* @version 1.0
* @since 4/15/2016
*/
namespace otp {
	/**
	* OTPEncrypt
	* File
	* Represents a file in the file system and performs operations on them
	*
	* @author Cameron Nicolle
	* @version 1.0
	* @since 4/15/2016
	*/
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

		/**
		* readFile
		* Reads parses proivded files and sets error state
		* @param op Operation of the class
		*/
		void readFile(FileOperation op);
		/**
		* allocFile
		* Allocates space for files
		*/
		void allocFile();
		/**
		* deallocFile
		* Deallocates space for files
		*/
		void deallocFile();

	public:
		/**
		* File
		* Constructor for the File class
		* @param filePath file path of unencypted file/folder
		*/
		File(std::string filePath, FileOperation op);
		/**
		* File
		* Constructor for the File class
		* @param filePath			file path of unencypted file/folder
		* @param cypherFilePath		file path of key
		* @param cypherTextFilePath	file path of cypher text
		* @param op					Operation to be performed
		*/
		File(std::string filePath, std::string cypherFilePath, std::string cypherTextFilePath, FileOperation op);
		~File();

		/**
		* isError
		* Getter for the error state of the class
		* @return Whether the class is in an error state or not
		*/
		bool isError();
		/**
		* getOperation
		* Getter for the operation of the class
		* @return The operation of the class
		*/
		otp::FileOperation getOperation();
		/**
		* setOperation
		* Setter for the operation of the class
		* @param op The new operation of the class
		*/
		void setOperation(FileOperation op);

		/**
		* setFilePath
		* Setter for file path of unencypted file/folder
		* @param filePath file path of unencypted file/folder
		*/
		virtual void setFilePath(std::string filePath) override;
		/**
		* setCypherFilePath
		* Setter for file path of key
		* @param filePath file path of key
		*/
		virtual void setCypherFilePath(std::string filePath) override;
		/**
		* setCypherTextFilePath
		* Setter for file path of cypher text
		* @param filePath file path of cypher text
		*/
		virtual void setCypherTextFilePath(std::string filePath) override;

		/**
		* encrypt
		* Performs encryption
		* @return Whether the operation was successful
		*/
		virtual bool encrypt() override;
		/**
		* decrypt
		* Performs decryption
		* @return Whether the operation was successful
		*/
		virtual bool decrypt() override;
		/**
		* writeFile
		* Writes unencypted file/folder
		* @param alternateFilePath	An alternate file path to write to than the specified in the class
		* @return Whether the operation was successful
		*/
		virtual bool writeFile(std::string alternateFilePath = "") override;
		/**
		* writeCyperText
		* Writes cypher text
		* @param alternateFilePath	An alternate file path to write to than the specified in the class
		* @return Whether the operation was successful
		*/
		virtual bool writeCyperText(std::string alternateFilePath = "") override;
		/**
		* writeCyperText
		* Writes key
		* @param alternateFilePath	An alternate file path to write to than the specified in the class
		* @return Whether the operation was successful
		*/
		virtual bool writeCyper(std::string alternateFilePath = "") override;
	};
}
