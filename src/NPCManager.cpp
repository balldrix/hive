#include "NPCManager.h"

#include "Enemy.h"
#include "EnemyData.h"
#include "EnemyDataContainer.h"
#include "HitBoxManager.h"
#include "Logger.h"
#include "NPCFactory.h"

#include <fstream>

NPCManager::NPCManager() :
	m_enemyDataContainer(nullptr),
	m_NPCFactory(nullptr)
{
	m_enemyList.clear();
}

NPCManager::~NPCManager()
{
	DeleteAll();
}

void NPCManager::Init(Graphics* graphics, Camera* camera, Player* player)
{
	bool result = false;

	m_enemyDataContainer = new EnemyDataContainer();
	m_NPCFactory = new NPCFactory();

	result = InitTypes("data\\enemy_data\\type_data.txt");

	if(result == false)
	{
		Logger::LogError("Error initialising enemy type data. NPCManager.cpp line 31.");
		PostQuitMessage(0); // quit game
	}

	result = InitNPCs(graphics, camera, player, "data\\enemy_data\\enemy_data.txt");

	if(result == false)
	{
		Logger::LogError(" Error initialising enemy list. NPCManager.cpp line 39.");
		PostQuitMessage(0); // quit game
	}
}

bool NPCManager::InitTypes(const std::string &fileName)
{
	std::ifstream file;
	file.open(fileName);
	
	if(file)
	{
		EnemyData data;
		std::string line;

		while(std::getline(file, line))
		{
			if(line[0] != '#')
			{
				std::string result;
				std::istringstream iss(line);
				

				iss >> result;
				data.type = result;

				iss >> result;
				data.objectData.startingHealth = std::stoi(result);

				iss >> result;
				data.objectData.startingLives = std::stoi(result);

				iss >> result;
				data.objectData.walkSpeed = std::stof(result);

				iss >> result;
				data.objectData.runningSpeed = std::stof(result);

				iss >> result;
				data.objectData.acceleration = std::stof(result);

				iss >> result;
				data.objectData.deceleration = std::stof(result);

				iss >> result;
				data.thinkingTime = std::stof(result);

				iss >> result;
				data.hostileRange = std::stof(result);

				iss >> result;
				data.attackRange = std::stof(result);

				iss >> result;
				data.chargeRange = std::stof(result);

				iss >> result;
				data.chargeSpeed = std::stof(result);

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

bool NPCManager::InitNPCs(Graphics* graphics, Camera* camera, Player* player, const std::string &fileName)
{
	std::ifstream file;
	file.open(fileName);
	if(file) 
	{
		m_NPCFactory->Init(graphics, camera, player);

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

			// enemy Type
			file >> result;
			data = m_enemyDataContainer->GetData(result);
			
			data.objectData.id = id;

			// data name
			file >> result;
			data.name = result;

			// start position X
			file >> result;
			data.objectData.startingPosition.x = std::stof(result);
			
			// start position Y
			file >> result;
			data.objectData.startingPosition.y = std::stof(result);

			file >> result;
			data.encounterIndex = std::stoi(result);

			Enemy* enemy = m_NPCFactory->GetEnemy(data);
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
	for (const Enemy* i : m_enemyList)
	{
		delete i;
		i = nullptr;
	}

	m_enemyList.clear();
	
	delete m_NPCFactory;
	delete m_enemyDataContainer;

	m_NPCFactory = nullptr;	
	m_enemyDataContainer = nullptr;
}
