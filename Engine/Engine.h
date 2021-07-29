#pragma once
#include "Graphics/ParticleSystem.h"
#include "Audio/AudioSystem.h"
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "Math/random.h"
#include "Math/MathUtils.h"
#include "Math/Transform.h"
#include "Graphics/Shape.h"
#include "Base/Actor.h"
#include "Base/Object.h"
#include "Base/Scene.h"
#include "Framework/EventSystem.h"
#include "Framework/ResourceSystem.h"
#define NOMINMAX
#include "core.h"
#include <vector>
#include <algorithm>
#include <memory>

namespace rj {
	
	class Engine {
	public:
		void Startup();
		void Shutdown();

		void Update(float dt);
		void Draw(Core::Graphics& graphics);

		template<typename T>
		T* Get();

	private:
		std::vector<std::unique_ptr<System>> systems;
	};

	template<typename T>
	inline T* Engine::Get() {
		for (auto& system : systems) {
			if (dynamic_cast<T*>(system.get())) return dynamic_cast<T*>(system.get());
		}

		return nullptr;
	}
}