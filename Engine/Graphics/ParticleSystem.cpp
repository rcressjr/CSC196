#include "ParticleSystem.h"
#include "Math/random.h"

namespace rj {
	float random() { // 0.0 - 1.0
		return rand() / static_cast<float>(RAND_MAX);
	}

	float random(float min, float max) {
		return min - (max - min) * random();
	}

	void ParticleSystem::Startup() {
		particles.resize(10000);
	}

	void ParticleSystem::Shutdown() {
		particles.clear();
	}

	void ParticleSystem::Update(float dt) {
		for (Particle& particle : particles) {
			if (particle.isActive) {
				particle.lifetime -= dt;
				particle.isActive = particle.lifetime > 0;
				particle.prevPosition = particle.position;
				particle.position += particle.velocity * dt;
			}
		}
	}

	void ParticleSystem::Draw(Core::Graphics& graphics) {
		for (const Particle& particle : particles) {
			if (particle.isActive) {
				graphics.SetColor(particle.color);
				graphics.DrawLine(particle.position.x, particle.position.y, particle.prevPosition.x, particle.prevPosition.y);
			}
		}
	}

	void ParticleSystem::Create(Vector2 position, size_t count, float lifetime, const Color& color, float speed) {
		for (size_t i = 0; i < count; i++) {
			auto particle = std::find_if(particles.begin(), particles.end(), Particle::IsNotActive);
			if (particle != particles.end()) {
				particle->isActive = true;
				particle->lifetime = lifetime;
				particle->position = position;
				particle->prevPosition = position;
				particle->color = color;

				particle->velocity = Vector2{ RandomRange(-1, 1), RandomRange(-1 , 1) } * (speed * Random());
			}
		}
	}
	
	void ParticleSystem::Create(Vector2 position, size_t count, float lifetime, const std::vector<Color>& colors, float speed, float angle, float angleRange) {
		for (size_t i = 0; i < count; i++) {
			auto particle = std::find_if(particles.begin(), particles.end(), Particle::IsNotActive);
			if (particle != particles.end()) {
				particle->isActive = true;
				particle->lifetime = lifetime;
				particle->position = position;
				particle->prevPosition = position;
				particle->color = colors[rand() % colors.size()];

				particle->velocity = rj::Vector2::Rotate(rj::Vector2::right, (angle + rj::RandomRange(-angleRange, angleRange)) * (speed * Random()));
			}
		}
	}
}