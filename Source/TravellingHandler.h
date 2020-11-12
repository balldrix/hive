#pragma once

class TravellingHandler
{
public:
	TravellingHandler();
	~TravellingHandler();

	float GetTravelTimer() const { return m_travelTimer; }
	void SetTravelTimer(float time);
	void Update(float deltaTime);

private:
	float m_travelTimer;
};
