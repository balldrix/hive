#pragma once

#include <directxtk/SimpleMath.h>
#include <vector>

using namespace DirectX::SimpleMath;

class Graphics;
class Texture;

const unsigned int MAX_PARTICLES = 1000;

struct ParticleData
{
	Vector2 Position;
	Vector2 Velocity;
	Vector2 VelocityVariation = Vector2::One;
	Color ColorBegin;
	Color ColorEnd;
	float SizeBegin = 1.0f;
	float SizeEnd = 1.0f;
	float SizeVariation = 1.0f;
	float LifeTime = 1.0f;
};

class ParticleSystem
{
public:
	ParticleSystem();
	~ParticleSystem() = default;
	
	void Init(Graphics* graphics);

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

	Texture* m_texture;
	std::vector<Particle> m_particlePool;
	unsigned int m_poolIndex = 0;
};