#include "NPCManager.h"

#include "Enemy.h"
#include "Error.h"
#include "NPCFactory.h"

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

void NPCManager::Init(Graphics* graphics, Camera* camera, Player* player, InGameHudManager* hudManager, Texture* standardShadowTexture,
					  Texture* hitBoxTexture)
{
	bool result = false;

	m_enemyDataContainer = new EnemyDataContainer();
	m_NPCFactory = new NPCFactory();

	result = InitTypes("GameData\\EnemyData\\typeData.txt");
	if(result == false)
	{
		Error::FileLog(" Error initialising enemy type data. EnemyManager.cpp line 17");
		PostQuitMessage(0); // quit game
	}

	result = InitNPCs(graphics, camera, player, hudManager, standardShadowTexture, hitBoxTexture, "GameData\\EnemyData\\enemyData.txt");

	if(result == false)
	{
		Error::FileLog(" Error initialising enemy list. EnemyManager.cpp line 24");
		PostQuitMessage(0); // quit game
	}
}

bool NPCManager::InitTypes(const std::string &fileName)
{
	std::ifstream file; // ifstream file buffer
	file.open(fileName); // opens file and reads to buffer
	if(file) // if file is open
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
				data.fightingRange = std::stof(result);

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

bool NPCManager::InitNPCs(Graphics* graphics, Camera* camera, Player* player, InGameHudManager* hudManager, Texture* standardShadowTexture,
						  Texture* hitBoxTexture, const std::string &fileName)
{
	std::ifstream file; // ifstream file buffer
	file.open(fileName); // opens file and reads to buffer
	if(file) // if file is open
	{
		m_NPCFactory->Init(graphics, camera, player, 
						   hudManager, standardShadowTexture,
						   hitBoxTexture);

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
	for(size_t i = m_enemyList.size() - 1; i-- > 0;)
	{
		if(m_enemyList[i] != nullptr)
		{
			delete m_enemyList[i];
			m_enemyList[i] = nullptr;
		}
	}

	m_enemyList.clear();
	
	if(m_NPCFactory != nullptr)
	{
		delete m_NPCFactory;
		m_NPCFactory = nullptr;
	}
	
	if(m_enemyDataContainer != nullptr)
	{
		delete m_enemyDataContainer;
		m_enemyDataContainer = nullptr;
	}
}
