#pragma once
#include "Base/Actor.h"
#include "Engine.h"

class Projectile : public rj::Actor {
public:
	Projectile(const rj::Transform& transform, std::shared_ptr<rj::Shape> shape, float speed) : rj::Actor{ transform, shape }, speed{ speed } {}

	void Update(float dt) override;

private:
	float lifetime{ 2 };
	float speed{ 300 };
};