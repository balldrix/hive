#include "NPCManager.h"
#include "Enemy.h"
#include "Error.h"

NPCManager::NPCManager()
{
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

	result = InitNPCs("GameData\\EnemyData\\positionData.txt");
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
		std::string result;

		// loop until end of file
		while(!file.eof())
		{
			// ready data
			result = "";

			// Type
			file >> result;

			// start health
			file >> result;
			data.m_objectData.m_startingHealth = std::stoi(result);

			// walk speed
			file >> result;
			data.m_objectData.m_walkSpeed = std::stof(result);

			// running speed
			file >> result;
			data.m_objectData.m_runningSpeed = std::stof(result);

			// acceleration
			file >> result;
			data.m_objectData.m_acceleration = std::stof(result);

			// deceleration
			file >> result;
			data.m_objectData.m_deceleration = std::stof(result);

			// thinking time
			file >> result;
			data.m_thinkingTime = std::stof(result);

			// fighting range
			file >> result;
			data.m_fightingRange = std::stof(result);

			// attack range
			file >> result;
			data.m_attackRange = std::stof(result);

			// add npc to list
			m_typeDataList.push_back(data);
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
			data.m_objectData.m_ID = result;
			
			// Type
			file >> result;

			EnemyType type = EnemyType::Mook;
			if(result == "Mook")
			{
				type = EnemyType::Mook;
			}

			data.m_type = type;

			// type data
			switch(type)
			{
			case Mook:
				data.m_objectData = m_typeDataList[Mook].m_objectData;
				data.m_thinkingTime = m_typeDataList[Mook].m_thinkingTime;
				data.m_fightingRange = m_typeDataList[Mook].m_fightingRange;
				data.m_attackRange = m_typeDataList[Mook].m_attackRange;
				break;
			default:
				break;
			}
			
			// start position X
			file >> result;
			data.m_objectData.m_startingPosition.x = std::stof(result);
			
			// start position Y
			file >> result;
			data.m_objectData.m_startingPosition.y = std::stof(result);

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
	for(int i = m_enemyList.size() - 1; i >= 0; i--)
	{
		if(m_enemyList[i] != nullptr)
		{
			delete m_enemyList[i];
			m_enemyList[i] = nullptr;
		}
	}

	m_enemyList.clear();
}
