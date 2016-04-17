#pragma once
#include "FileSysObj.h"

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
	public:
		Folder();
		~Folder();
	};

}