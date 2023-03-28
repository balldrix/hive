#pragma once

#include "pch.h"

class Graphics;

const unsigned int MAX_PARTICLES = 1000;

struct ParticleData
{
	Vector2 Position;
	Vector2 Velocity;
	Vector2 VelocityVariation;
	Color ColorBegin;
	Color ColorEnd;
	float SizeBegin;
	float SizeEnd;
	float SizeVariation;
	float LifeTime = 1.0f;
};

class ParticlaSystem
{
public:
	ParticlaSystem();
	
	void Update(float deltaTime);
	void Render(Graphics* graphics);

	void Emit(const ParticleData& particleData);


private:
	struct Particle
	{
		Vector2 Position;
		Vector2 Velocity;
		Color ColorBegin;
		Color ColorEnd;
		float Rotation = 0.0f;
		float SizeBegin;
		float SizeEnd;

		float LifeTime = 1.0f;
		float LifeRemaining = 0.0f;

		bool Active = false;
	};

	//int m_quadVertexArray;
	std::vector<Particle> m_particlePool;
	unsigned int m_poolIndex = 0;
};