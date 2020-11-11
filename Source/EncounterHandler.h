// EncounterHandler.h
// Christopher Ball 2019-2020
// handles encounter data

#pragma once

#include <string>
#include <vector>

class EncounterHandler
{
public:
	EncounterHandler();
	~EncounterHandler();

	void Init(std::string encounterDataFile);
	void SetEncounterIndex(const int& index);
	
	int GetEncounterIndex() const { return m_encounterIndex; }
	int GetEncounterPosition() const { return m_encounterPositions[m_encounterIndex]; }

private:
	bool				LoadData(std::string encounterDataFile);
	int					m_encounterIndex;
	std::vector<int>    m_encounterPositions;
};

