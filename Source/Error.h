// Error.h
// Christopher Ball 2018
// error namespace is called when there is an error
// and saves the error into a log file

#ifndef _ERROR_H_
#define _ERROR_H_

#include "pch.h"

namespace Error
{
	// log error into error.txt
	void FileLog(std::string message);
};

#endif _ERROR_H_
