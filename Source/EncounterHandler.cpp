#include "EncounterHandler.h"

#include "Enemy.h"
#include "Error.h"

EncounterHandler::EncounterHandler()
	: m_encounterIndex(0)
{
	m_enemyList.clear();
	m_encounterPositions.clear();
}

EncounterHandler::~EncounterHandler()
{
}

void EncounterHandler::Init(std::string encounterDataFile, const std::vector<Enemy*>& enemyList)
{
	m_enemyList = enemyList;

	if(LoadData(encounterDataFile) == true)
		return;

	std::string error = " Error! No encounter data file " + encounterDataFile + " found.";
	Error::FileLog(error);
}

void EncounterHandler::SpawnEncounter()
{
	for(size_t i = 0; i < m_enemyList.size(); i++)
	{
		int enemyEncounterIndex = m_enemyList[i]->GetData().encounterIndex;
		if(enemyEncounterIndex == m_encounterIndex)
			m_enemyList[i]->SetActive(true);
	}
}

void EncounterHandler::SetEncounterIndex(const int& index)
{
	m_encounterIndex = index;
}

bool EncounterHandler::GetIsEncounterDone()
{
	for(size_t i = 0; i < m_enemyList.size(); i++)
	{
		Enemy* enemy = m_enemyList[i];
		int encounterIndex = enemy->GetData().encounterIndex;

		if(enemy->IsDead() == false && encounterIndex == m_encounterIndex)
			return false;
	}

	return true;
}

void EncounterHandler::IncreaseEncounterIndex()
{
	m_encounterIndex++;
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