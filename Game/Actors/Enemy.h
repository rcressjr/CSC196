#pragma once
#include "Base/Actor.h"

class Enemy : public rj::Actor {
public:
	Enemy(const rj::Transform& transform, std::shared_ptr<rj::Shape> shape, float speed) : rj::Actor{ transform, shape }, speed{ speed } {}

	void Update(float dt) override;
	void OnCollision(Actor* actor) override;

private:
	float speed{ 150 };
	float fireTimer{ 0 };
	float fireRate = 1;
};