// EncounterHandler.h
// Christopher Ball 2019-2020
// handles encounter data

#pragma once

class Enemy;

#include <string>
#include <vector>

class EncounterHandler
{
public:
	EncounterHandler();
	~EncounterHandler();

	void	Init(std::string encounterDataFile, std::vector<Enemy*> enemyList);
	void	SpawnEncounter();

	void	SetEncounterIndex(const int& index);
	
	size_t	GetEncounterIndex() const { return m_encounterIndex; }
	int		GetEncounterPosition() const { return m_encounterPositions[m_encounterIndex]; }
	bool	GetIsEncounterDone();
	size_t	GetNumberOfEncounters() const { return m_encounterPositions.size(); }

	void	IncreaseEncounterIndex();

private:
	bool				LoadData(std::string encounterDataFile);

	std::vector<Enemy*> m_enemyList;
	size_t				m_encounterIndex;
	std::vector<int>    m_encounterPositions;
	bool				m_isEncounterDone;
};