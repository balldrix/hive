#include "EncounterHandler.h"

#include "Error.h"

EncounterHandler::EncounterHandler()
	: m_encounterIndex(0) 
{
	m_encounterPositions.clear();
}

EncounterHandler::~EncounterHandler()
{
}

void EncounterHandler::Init(std::string encounterDataFile)
{
	if(LoadData(encounterDataFile) == true)
		return;

	std::string error = " Error! No encounter data file " + encounterDataFile + " found.";
	Error::FileLog(error);
}

void EncounterHandler::SetEncounterIndex(const int& index)
{
	m_encounterIndex = index;
}

bool EncounterHandler::LoadData(std::string encounterDataFile)
{
	std::ifstream file;
	file.open(encounterDataFile);

	if(!file)
		return false;

	std::string line;
	m_encounterPositions.clear();

	while(std::getline(file, line))
	{
		if(line[0] == '#')
			continue;

		std::string result = "";
		
		file >> result;
		int position = std::stoi(result);

		m_encounterPositions.push_back(position);
	}

	file.close();
	return true;
}
