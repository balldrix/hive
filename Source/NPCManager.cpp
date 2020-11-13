#include "NPCManager.h"
#include "Enemy.h"
#include "Error.h"

NPCManager::NPCManager()
{
	m_enemyDataContainer = new EnemyDataContainer();
}

NPCManager::~NPCManager()
{
	DeleteAll();
}

void NPCManager::Init()
{
	bool result = false;

	result = InitTypes("GameData\\EnemyData\\typeData.txt");
	if(result == false)
	{
		Error::FileLog(" Error initialising enemy type data. EnemyManager.cpp line 17");
		PostQuitMessage(0); // quit game
	}

	result = InitNPCs("GameData\\EnemyData\\enemyData.txt");
	if(result == false)
	{
		Error::FileLog(" Error initialising enemy list. EnemyManager.cpp line 24");
		PostQuitMessage(0); // quit game
	}
}

bool NPCManager::InitTypes(std::string fileName)
{
	std::ifstream file; // ifstream file buffer
	file.open(fileName); // opens file and reads to buffer
	if(file) // if file is open
	{
		EnemyData data;
		std::string line;

		// loop until end of file
		while(std::getline(file, line))
		{
			if(line[0] != '#')
			{
				std::string result;
				std::istringstream iss(line);

				// Type
				iss >> result;
				data.type = result;

				// start health
				iss >> result;
				data.objectData.startingHealth = std::stoi(result);

				iss >> result;
				data.objectData.startingLives = std::stoi(result);

				// walk speed
				iss >> result;
				data.objectData.walkSpeed = std::stof(result);

				// running speed
				iss >> result;
				data.objectData.runningSpeed = std::stof(result);

				// acceleration
				iss >> result;
				data.objectData.acceleration = std::stof(result);

				// deceleration
				iss >> result;
				data.objectData.deceleration = std::stof(result);

				// thinking time
				iss >> result;
				data.thinkingTime = std::stof(result);

				// fighting range
				iss >> result;
				data.fightingRange = std::stof(result);

				// attack range
				iss >> result;
				data.attackRange = std::stof(result);

				// add enemy type data to list
				m_enemyDataContainer->Add(data);
			}
		}
	}
	else
	{
		return false;
	}
	file.close(); // close file
	return true;
}

bool NPCManager::InitNPCs(std::string fileName)
{
	std::ifstream file; // ifstream file buffer
	file.open(fileName); // opens file and reads to buffer
	if(file) // if file is open
	{
		EnemyData data;
		std::string result;

		// loop until end of file
		while(!file.eof())
		{
			// ready data
			result = "";

			// ID
			file >> result;
			std::string id = result;
			
			if(id[0] == '#')
			{
				std::getline(file, id);
				continue;
			}

			// Type
			file >> result;
			data = m_enemyDataContainer->GetData(result);
			
			data.objectData.id = id;

			// start position X
			file >> result;
			data.objectData.startingPosition.x = std::stof(result);
			
			// start position Y
			file >> result;
			data.objectData.startingPosition.y = std::stof(result);

			file >> result;
			data.encounterIndex = std::stoi(result);

			Enemy* enemy = new Enemy();
			enemy->SetData(data);

			// add npc to list
			m_enemyList.push_back(enemy);
		}
	}
	else
	{
		return false;
	}
	file.close(); // close file
	return true;
}

void NPCManager::SpawnEncounter(int& encounterIndex)
{
	for(size_t i = 0; i < m_enemyList.size(); i++)
	{
		if(m_enemyList[i]->GetData().encounterIndex == encounterIndex);
			m_enemyList[i]->SetActive(true);
	}
}

void NPCManager::Render(Graphics* graphics)
{
	for(size_t i = 0; i < m_enemyList.size(); i++)
	{
		m_enemyList[i]->Render(graphics);
	}
}

void NPCManager::Update(float deltaTime)
{
	for(size_t i = 0; i < m_enemyList.size(); i++)
	{
		m_enemyList[i]->Update(deltaTime);
	}
}

void NPCManager::Reset()
{
	for(size_t i = 0; i < m_enemyList.size(); i++)
	{
		m_enemyList[i]->Reset();
	}
}

void NPCManager::DeleteAll()
{
	for(size_t i = m_enemyList.size() - 1; i-- > 0;)
	{
		if(m_enemyList[i] != nullptr)
		{
			delete m_enemyList[i];
			m_enemyList[i] = nullptr;
		}
	}

	m_enemyList.clear();
	if(m_enemyDataContainer)
	{
		delete m_enemyDataContainer;
		m_enemyDataContainer = nullptr;
	}
}
