#include "CutsceneManager.h"

#include "CutsceneData.h"
#include "EventManager.h"
#include "GameDataManager.h"
#include "IEvent.h"
#include "Logger.h"
#include "WaitEvent.h"

#include <fmt/core.h>
#include <string>
#include <vector>

CutsceneManager::CutsceneManager() :
	m_cutscenes(),
	m_activeCutscene(),
	m_currentStepIndex(0),
	m_timer(0.0f),
	m_cutsceneIndexByName(),
	m_isActive(false),
	m_eventManager(nullptr)
{
}

CutsceneManager::~CutsceneManager()
{
	Shutdown();
}

void CutsceneManager::Init(const std::string& filepath, EventManager* eventManager) {
	Logger::LogInfo("Initialising CutsceneManager.");

	m_eventManager = eventManager;
	m_cutscenes = GameDataManager::LoadAllCutscenes(filepath);

	for(int i = 0; i < m_cutscenes.size(); i++)
	{
		m_cutsceneIndexByName[m_cutscenes[0].name] = i;
	}

	m_eventManager->RegisterEvent("Wait", "CutsceneManager", new WaitEvent());
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
			EventKey key = { eventData.name, eventData.target };
			IEvent* event = m_eventManager->GetEvent(key);
			if(event != nullptr) event->Reset();
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
				EventKey key = { data.name, data.target };
				IEvent* event = m_eventManager->GetEvent(key);
				if(event) event->Reset();
			}
		}

		return;
	}
	else
	{
		bool allEventsCompleted = true;

		for(size_t i = 0; i < currentStep.events.size(); i++)
		{
			CutsceneEventData data = currentStep.events[i];
			EventKey key = { data.name, data.target };
			IEvent* event = m_eventManager->GetEvent(key);

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

		if(allEventsCompleted) m_activeCutscene->steps[m_currentStepIndex].stepCompleted = true;
	}

	m_timer += deltaTime;
}

void CutsceneManager::Shutdown()
{
	m_eventManager->UnRegisterEvent({ "Wait", "CutsceneManager" });
}
