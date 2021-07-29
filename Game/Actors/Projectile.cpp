#include "Projectile.h"
#include "Math/MathUtils.h"

void Projectile::Update(float dt) {
	Actor::Update(dt);

	lifetime -= dt;
	if (lifetime <= 0) destroy = true;

	transform.position += rj::Vector2::Rotate(rj::Vector2::right, transform.rotation) * speed * dt;
	transform.position.x = rj::Wrap(transform.position.x, 0.0f, 800.0f);
	transform.position.y = rj::Wrap(transform.position.y, 0.0f, 800.0f);

	std::vector<rj::Color> colors = { rj::Color::purple, rj::Color::blue, rj::Color::cyan, rj::Color::orange };
	//scene->engine->Get<rj::ParticleSystem>()->Create(transform.position, 10, 0.5f, colors[rj::RandomRangeInt(0, colors.size())], 150);

	transform.Update();
}
