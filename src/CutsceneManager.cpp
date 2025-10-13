#include "CutsceneManager.h"

#include "CutsceneData.h"
#include "EventManager.h"
#include "GameDataManager.h"
#include "Logger.h"
#include "WaitEvent.h"

#include <fmt/core.h>
#include <string>

CutsceneManager::CutsceneManager() :
	m_cutscenes(),
	m_activeCutscene(),
	m_currentStepIndex(0),
	m_timer(0.0f),
	m_eventManagers(),
	m_cutsceneIndexByName(),
	m_isActive(false),
	m_eventManager(nullptr)
{
}

CutsceneManager::~CutsceneManager()
{
	Shutdown();
}

void CutsceneManager::Init(const std::string& filepath) {
	Logger::LogInfo("Initialising CutsceneManager.");

	m_cutscenes = GameDataManager::LoadAllCutscenes(filepath);

	for(int i = 0; i < m_cutscenes.size(); i++)
	{
		m_cutsceneIndexByName[m_cutscenes[0].name] = i;
	}

	m_eventManager = new EventManager();
	m_eventManager->RegisterEvent("Wait", new WaitEvent());

	RegisterEventManager("CutsceneManager", m_eventManager);
}

void CutsceneManager::StartCutscene(std::string name)
{
	if(m_cutscenes.size() == 0)
	{
		Logger::LogWarning("[CutsceneManager] StartCutscene - no cutscenes listed.");
		return;
	}
	
	int index = -1;
	auto cutsceneIndex = m_cutsceneIndexByName.find(name);
	if(cutsceneIndex != m_cutsceneIndexByName.end()) index = cutsceneIndex->second;

	if(index  < 0 || index >= m_cutscenes.size())
	{
		Logger::LogWarning("[CutsceneManager] StartCutscene - index is out of bounds.");
		return;
	}

	m_activeCutscene = &m_cutscenes[index];
	m_currentStepIndex = 0;
	m_timer = 0.0f;
	m_isActive = true;

	for(auto& steps : m_activeCutscene->steps)
	{
		for(auto& eventData : steps.events)
		{
			auto manager = m_eventManagers.find(eventData.target);
			if(manager != m_eventManagers.end())
			{
				auto event = manager->second->GetEvent(eventData.name);
				if(event != nullptr) event->Reset();
			}
		}
	}

	Logger::LogInfo(fmt::format("[CutsceneManager] Starting {} Cutscene", m_activeCutscene->name));
}

void CutsceneManager::Update(float deltaTime)
{
	if(!m_isActive) return;

	if(m_currentStepIndex < 0 || m_currentStepIndex >= m_activeCutscene->steps.size())
	{
		m_isActive = false;
		return;
	}

	CutsceneStepData currentStep = m_activeCutscene->steps[m_currentStepIndex];
	if(currentStep.stepCompleted)
	{
		m_timer = 0;
		m_currentStepIndex++;

		if(m_currentStepIndex < m_activeCutscene->steps.size())
		{
			auto& nextStep = m_activeCutscene->steps[m_currentStepIndex];
			for(auto& data : nextStep.events)
			{
				auto manager = m_eventManagers.find(data.target);
				if(manager != m_eventManagers.end())
				{
					auto event = manager->second->GetEvent(data.name);
					if(event) event->Reset();
				}
			}
		}

		return;
	}
	else
	{
		bool allEventsCompleted = true;

		for(size_t i = 0; i < currentStep.events.size(); i++)
		{
			auto& data = currentStep.events[i];
			auto manager = m_eventManagers.find(data.target);
			
			if(manager != m_eventManagers.end())
			{
				auto event = manager->second->GetEvent(data.name);

				if(event == nullptr) continue;

				if(!event->HasStarted())
				{
					event->OnStart(data.arg);
				}
				if(!event->IsComplete())
				{
					event->OnUpdate(deltaTime);
					if(data.waitForCompletion) allEventsCompleted = false;
				}
			}
		}

		if(allEventsCompleted) m_activeCutscene->steps[m_currentStepIndex].stepCompleted = true;
	}

	m_timer += deltaTime;
}

void CutsceneManager::Shutdown()
{
	m_eventManager->UnRegisterEvent("Wait");
	m_eventManagers.clear();
}

void CutsceneManager::RegisterEventManager(std::string target, EventManager* eventManager)
{
	if(m_eventManagers.find(target) != m_eventManagers.end())
	{
		Logger::LogWarning(fmt::format("[CutsceneManager] Event with target {0} already registered.", target));
		return;
	}

	m_eventManagers[target] = eventManager;
}

void CutsceneManager::UnregisterEventManager(std::string target)
{
	if(m_eventManagers.find(target) == m_eventManagers.end())
	{
		Logger::LogWarning(fmt::format("[CutsceneManager] Event attempt to erase event manager with target {0} failed.", target));
	}

	m_eventManagers.erase(target);
}
