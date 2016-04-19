#pragma once
#include "FileSysObj.h"
#include <string>
#include <direct.h>

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
	* Folder
	* Represents a folder in the file system and performs operations on them
	*
	* @author Cameron Nicolle
	* @version 1.0
	* @since 4/15/2016
	*/
	class Folder : public FileSysObj
	{
	private:
		/**
		* OTPEncrypt
		* FSOItm
		* Container for FileSysObj and name of that object
		*
		* @author Cameron Nicolle
		* @version 1.0
		* @since 4/18/2016
		*/
		struct FSOItm
		{
			FileSysObj* object;
			std::string name;
		}* subObjects;
		
		unsigned long subObjectsCount;
		bool errorState;

		/**
		* readFile
		* Reads parses proivded files and sets error state
		* @param op Operation of the class
		*/
		void readFile(FileOperation op);
		/**
		* addNewObject
		* Adds new object to class
		* @param object new object to add
		*/
		void addNewObject(struct FSOItm object);
	public:
		/**
		* Folder
		* Constructor for the folder class
		* @param filePath			file path of unencypted file/folder
		* @param cypherFilePath		file path of key
		* @param cypherTextFilePath	file path of cypher text
		* @param op					Operation to be performed
		*/
		Folder(std::string filePath, std::string cypherFilePath, std::string cypherTextFilePath, FileOperation op);
		/**
		* Folder
		* Constructor for the folder class
		* @param files	The file paths
		* @param op		Operation to be performed
		*/
		Folder(struct otp::FilePathSet files, FileOperation op);
		~Folder();

		/**
		* isError
		* Getter for the error state of the class
		* @return Whether the class is in an error state or not
		*/
		virtual bool isError() override;
		/**
		* setOperation
		* Setter for the operation of the class
		* @param op The new operation of the class
		*/
		virtual void setOperation(FileOperation op) override;

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