#include "ImpactFxPool.h"

#include "Logger.h"
#include "SpriteFx.h"

#include <directxtk/SimpleMath.h>

ImpactFxPool::ImpactFxPool()
{
	Logger::LogInfo("Initialising ImpactFX Pool");
}

SpriteFx* ImpactFxPool::Get()
{
	if(m_pool.empty()) 
	{
		SpriteFx* spriteFx = new SpriteFx();
		spriteFx->Init("t_impact", "impactfx", Vector2(12.0f, 12.0f));
		return spriteFx;
	}

	SpriteFx* obj = m_pool.front();
	m_pool.pop_front();
	return obj;
}