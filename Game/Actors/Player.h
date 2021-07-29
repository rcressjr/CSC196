#pragma once
#include "Base/Actor.h"
#include "../Game.h"

class Player : public rj::Actor {
public:
	Player(const rj::Transform& transform, std::shared_ptr<rj::Shape> shape, float speed);


	void Update(float dt) override;
	void Initialize() override;
	void OnCollision(Actor* actor) override;

private:
	float fireTimer{ 0 };
	float rocketTimer{ 0 };
	float fireRate{ 0.0f };
	float rocketRate{ 0.15f };
	float speed{ 300 };
	size_t lives = 18;
	rj::Vector2 velocity;
};