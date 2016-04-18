#pragma once
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
	* FilePathSet
	* Represents a set of file paths
	*
	* @author Cameron Nicolle
	* @version 1.0
	* @since 4/16/2016
	*/
	struct FilePathSet { std::string file; std::string cypherFile; std::string cypherTextFile; };

	/**
	* OTPEncrypt
	* FileOperation
	* Represents an encryption or decryption operation
	*
	* @author Cameron Nicolle
	* @version 1.0
	* @since 4/15/2016
	*/
	enum FileOperation { encrypt, decrypt };

	/**
	* OTPEncrypt
	* FileSysObj
	* Represents any file system object
	* Not mean to be instantiated 
	*
	* @author Cameron Nicolle
	* @version 1.0
	* @since 4/15/2016
	*/
	class FileSysObj
	{
	private:
		std::string filePath;
		std::string cypherFilePath;
		std::string cypherTextFilePath;
		FileOperation operation;
	public:
		/**
		* FileSysObj
		* Constructor for the FileSysObj class
		* @param filePath			file path of unencypted file/folder
		* @param cypherFilePath		file path of key
		* @param cypherTextFilePath	file path of cypher text
		*/
		FileSysObj(std::string filePath, std::string cypherFilePath, std::string cypherTextFilePath);

		/**
		* FileSysObj
		* Constructor for the FileSysObj class
		* @param files The file paths
		*/
		FileSysObj(struct otp::FilePathSet files);

		/**
		* getOperation
		* Getter for the operation of the class
		* @return The operation of the class
		*/
		virtual otp::FileOperation getOperation();
		/**
		* setOperation
		* Setter for the operation of the class
		* @param op The new operation of the class
		*/
		virtual void setOperation(FileOperation op);
		/**
		* getFilePath
		* Getter for file path of unencypted file/folder
		* @return file path of unencypted file/folder
		*/
		std::string getFilePath();
		/**
		* getCypherFilePath
		* Getter for file path of key
		* @return file path of key
		*/
		std::string getCypherFilePath();
		/**
		* getCypherTextFilePath
		* Getter for file path of cypher text
		* @return file path of cypher text
		*/
		std::string getCypherTextFilePath();

		/**
		* setFilePath
		* Setter for file path of unencypted file/folder
		* @param filePath file path of unencypted file/folder
		*/
		virtual void setFilePath(std::string filePath);
		/**
		* setCypherFilePath
		* Setter for file path of key
		* @param filePath file path of key
		*/
		virtual void setCypherFilePath(std::string filePath);
		/**
		* setCypherTextFilePath
		* Setter for file path of cypher text
		* @param filePath file path of cypher text
		*/
		virtual void setCypherTextFilePath(std::string filePath);

		/**
		* isError
		* Getter for the error state of the class
		* @return Whether the class is in an error state or not
		*/
		virtual bool isError() = 0;
		/**
		* encrypt
		* Performs encryption
		* @return Whether the operation was successful
		*/
		virtual bool encrypt() = 0;
		/**
		* decrypt
		* Performs decryption
		* @return Whether the operation was successful
		*/
		virtual bool decrypt() = 0;
		/**
		* writeFile
		* Writes unencypted file/folder
		* @param alternateFilePath	An alternate file path to write to than the specified in the class
		* @return Whether the operation was successful
		*/
		virtual bool writeFile(std::string alternateFilePath = "") = 0;
		/**
		* writeCyperText
		* Writes cypher text
		* @param alternateFilePath	An alternate file path to write to than the specified in the class
		* @return Whether the operation was successful
		*/
		virtual bool writeCyperText(std::string alternateFilePath = "") = 0;
		/**
		* writeCyperText
		* Writes key
		* @param alternateFilePath	An alternate file path to write to than the specified in the class
		* @return Whether the operation was successful
		*/
		virtual bool writeCyper(std::string alternateFilePath = "") = 0;
	};

}