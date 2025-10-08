#pragma once

#include "CutsceneData.h"
#include "EventManager.h"

#include <string>
#include <unordered_map>
#include <vector>

class CutsceneManager
{
public:
	CutsceneManager();
	~CutsceneManager();

	void Init(const std::string& filepath);
	void StartCutscene(std::string name);
	void Update(float deltaTime);
	void Shutdown();

	void RegisterEventManager(std::string target, EventManager* eventManager);
	void UnregisterEventManager(std::string target);

	bool IsActive() const { return m_isActive; }

private:
	bool m_isActive;
	std::vector<CutsceneData> m_cutscenes;
	CutsceneData* m_activeCutscene;
	int m_currentStepIndex;
	float m_timer;
	std::unordered_map<std::string, EventManager*> m_eventManagers;
	std::unordered_map<std::string, int> m_cutsceneIndexByName;
	EventManager* m_eventManager;
};