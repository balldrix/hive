#include "Error.h"

void 
Error::FileLog(std::string message)
{
	time_t rawTime; // raw time
	struct tm timeInfo; // struct for time information
	char buffer[80]; // character buffer for the date and time

	time(&rawTime); // get current time
	localtime_s(&timeInfo, &rawTime); // convert to local time

	// get time info and put in char buffer
	strftime(buffer, sizeof(buffer), "%d.%m.%Y %I:%M:%S", &timeInfo);

	std::string s = buffer + message; // string to log data

	// open file and log error	
	std::ofstream file;

	// check file is opened
	if(file)
	{
		// open text file with in, out and append modes
		file.open("Logs//Error.txt", std::fstream::in | std::fstream::out | std::fstream::app);
		file << s; // write message to file
		file.close(); // close file
	}
}
