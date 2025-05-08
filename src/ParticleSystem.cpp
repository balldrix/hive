#include "ParticleSystem.h"

#include "AssetLoader.h"
#include "Graphics.h"
#include "Randomiser.h"
#include "Texture.h"

#include <cmath>
#include <directxtk/SimpleMath.h>
#include <directxtk/SpriteBatch.h>
#include <windef.h>

ParticleSystem::ParticleSystem() : 
	m_texture(nullptr),
	m_particlePool(0)
{
}

void ParticleSystem::Init(Graphics* graphics)
{
	m_particlePool.resize(MAX_PARTICLES);

	m_texture = AssetLoader::GetTexture("t_pixel");
}

void ParticleSystem::Update(float deltaTime)
{
	for(auto& particle : m_particlePool)
	{
		if(particle.LifeRemaining <= 0.0f)
			continue;

		particle.LifeRemaining -= deltaTime;
		particle.Velocity += Vector2(0.0f, 50.0f) * deltaTime;
		particle.Position += particle.Velocity * deltaTime;
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

		graphics->GetDefaultSpriteBatch()->Draw(m_texture->GetTexture(),
			particle.Position,
			&rect,
			colour,
			particle.Rotation,
			Vector2::Zero,
			size,
			SpriteEffects_None,
			0.8f);
	}
}

void ParticleSystem::Emit(const ParticleData& particleData)
{
	Particle& particle = m_particlePool[m_poolIndex];

	// position
	auto randomOffset = Randomiser::Instance()->GetRandNumUniform(-1.0f, 1.0f);
	auto positionOffset = Vector2(Randomiser::Instance()->GetRandNumUniform(-1.0f, 1.0f), Randomiser::Instance()->GetRandNumUniform(-1.0f, 1.0f));
	positionOffset.Normalize();

	auto randomDistance = Randomiser::Instance()->GetRandNumUniform(0.0f, 2.0f);

	particle.Position = particleData.Position + positionOffset * randomDistance;
	particle.Rotation = 0;

	// velocity
	particle.Velocity = particleData.Velocity;
	
	Vector2 velocityOffset;
	velocityOffset = particleData.VelocityVariation;

	if (particle.Velocity.x < 0)
		velocityOffset.x *= -1;

	particle.Velocity += velocityOffset;

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