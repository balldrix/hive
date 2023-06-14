#include "ParticleSystem.h"

#include "pch.h"

#include "PixelTexture.h"
#include "Graphics.h"
#include "Randomiser.h"


ParticleSystem::ParticleSystem() : 
	m_texture(nullptr),
	m_particlePool(0)
{
}

ParticleSystem::~ParticleSystem()
{
	DeleteAll();
}

void ParticleSystem::Init(Graphics* graphics)
{
	m_particlePool.resize(MAX_PARTICLES);

	m_texture = new PixelTexture();
	m_texture->Init(graphics);
}

void ParticleSystem::Update(float deltaTime)
{
	for(auto& particle : m_particlePool)
	{
		if(particle.LifeRemaining <= 0.0f)
			continue;

		particle.LifeRemaining -= deltaTime;
		particle.Velocity += Vector2(0.0f, 20.0f) * deltaTime;
		particle.Position += particle.Velocity * deltaTime;
		particle.Rotation += 0.01f * deltaTime;
	}
}

void ParticleSystem::Render(Graphics* graphics)
{
	for(auto& particle : m_particlePool)
	{
		if(particle.LifeRemaining <= 0.0f)
			continue;

		float life = particle.LifeRemaining / particle.LifeTime;
		Color colour = Color::Lerp(particle.ColorBegin, particle.ColorEnd, life);
		colour.w *= life;
		
		float size = std::lerp(particle.SizeBegin, particle.SizeEnd, life);
		
		RECT rect;
		rect.top = 0;
		rect.left = 0;
		rect.right = 1;
		rect.bottom = 1;

		graphics->GetSpriteBatch()->Draw(m_texture->GetTexture(),
			particle.Position,
			&rect,
			colour,
			particle.Rotation,
			Vector2::Zero,
			size,
			SpriteEffects_None,
			1.0f);
	}
}

void ParticleSystem::Emit(const ParticleData& particleData)
{
	Particle& particle = m_particlePool[m_poolIndex];
	particle.Position = particleData.Position;
	particle.Rotation = 0;

	// velocity
	particle.Velocity = particleData.Velocity;
	particle.Velocity.x *= (Randomiser::Instance()->GetRandNum(-5.0f, 5.0f));
	particle.Velocity.y *= (Randomiser::Instance()->GetRandNum(-5.0f, 5.0f));
	//particle.Velocity.Normalize();

	particle.Velocity *= particleData.VelocityVariation * Randomiser::Instance()->GetRandNum(1.0f, 5.0f);

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

void ParticleSystem::DeleteAll()
{
	delete m_texture;
	m_texture = nullptr;
}
