#pragma once

#include "Cutscene.h"
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
	void PlayStep(int index);
	void TriggerEvent(const CutsceneEvent& evt);

	bool m_isActive;
	std::vector<Cutscene> m_cutscenes;
	Cutscene* m_activeCutscene;
	int m_currentStep;
	float m_timer;
	int m_pendingCompletions;
	std::unordered_map<std::string, EventManager*> m_eventManagers;
	std::unordered_map<std::string, int> m_cutsceneIndexByName;
};