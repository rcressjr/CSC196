#pragma once
#include "Object.h"
#include "Math/Transform.h"
#include "Core.h"
#include <vector>
#include <memory>

namespace rj {
	class Shape;
	class Scene;

	class Actor : public Object {
	public:
		Actor() {}
		Actor(const Transform& transform, std::shared_ptr<Shape> shape) : transform{ transform }, shape{ shape } {}

		virtual void Update(float dt);
		virtual void Draw(Core::Graphics& graphics);

		virtual void OnCollision(Actor* actor) {}
		void AddChild(std::unique_ptr<Actor> actor);
		virtual void Initialize() {}

		float GetRadius();

	public:
		bool destroy{ false };
		Transform transform;
		std::shared_ptr<Shape> shape;
		Scene* scene{ nullptr };
		std::string tag;

		Actor* parent{ nullptr };
		std::vector<std::unique_ptr<Actor>> children;
	};
}