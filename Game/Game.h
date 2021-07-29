#pragma once
#include "Engine.h"

class Game {
public:
	enum class eState {
		Title,
		StartGame,
		StartLevel,
		Game,
		GameOver
	};

public:
	void Initialize();
	void Shutdown();

	void Update(float dt);
	void Draw(Core::Graphics& graphics);

private:
	void UpdateTitle(float dt);
	void UpdateLevelStart(float dt);
	void OnAddPoints(const rj::Event& event);
	void OnPlayerDead(const rj::Event& event);
	void OnPlayerHurt(const rj::Event& event);

public:
	std::unique_ptr<rj::Engine> engine;
	std::unique_ptr<rj::Scene> scene;
	size_t lives = 0;

private:
	eState state = eState::Title;
	float stateTimer = 0.0f;

	void (Game::*stateFunction)(float) = nullptr;

	size_t score = 0;
	size_t creating = 1;
	size_t level = 1;
	std::string currentString;
};