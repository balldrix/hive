#include "ParticleSystem.h"

#include "Randomiser.h"

ParticlaSystem::ParticlaSystem()
{
	m_particlePool.resize(MAX_PARTICLES);
}

void ParticlaSystem::Update(float deltaTime)
{
	for(auto& particle : m_particlePool)
	{
		if(!particle.Active)
			continue;

		if(particle.LifeRemaining <= 0.0f)
		{
			particle.Active = false;
			continue;
		}

		particle.LifeRemaining -= deltaTime;
		particle.Position += particle.Velocity * deltaTime;
		particle.Rotation += 0.01f * deltaTime;
	}
}

void ParticlaSystem::Render(Graphics* graphics)
{
		
}

void ParticlaSystem::Emit(const ParticleData& particleData)
{
	Particle& particle = m_particlePool[m_poolIndex];
	particle.Active = true;
	particle.Position = particleData.Position;
	particle.Rotation = 0;

	// velocity
	particle.Velocity = particleData.Velocity;
	particle.Velocity.x = particleData.VelocityVariation.x * (Randomiser::Instance()->GetRandNum(0.0f, 1.0f) - 0.5f);
	particle.Velocity.y = particleData.VelocityVariation.x * (Randomiser::Instance()->GetRandNum(0.0f, 1.0f) - 0.5f);

	// color

	particle.ColorBegin = particleData.ColorBegin;
	particle.ColorEnd = particleData.ColorEnd;

	// lifetime
	particle.LifeTime = particleData.LifeTime;
	particle.LifeRemaining = particleData.LifeTime;

	// size
	particle.SizeBegin = particleData.SizeBegin;
	particle.SizeEnd = particleData.SizeEnd;

	m_poolIndex = ++m_poolIndex % m_particlePool.size();
}