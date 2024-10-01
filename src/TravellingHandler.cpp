#include "TravellingHandler.h"

TravellingHandler::TravellingHandler()
	: m_travelTimer(0.0f) { }

TravellingHandler::~TravellingHandler()
{
}

void TravellingHandler::SetTravelTimer(float time)
{
	m_travelTimer = time;
}

void TravellingHandler::Update(float deltaTime)
{
	m_travelTimer += deltaTime;
}
