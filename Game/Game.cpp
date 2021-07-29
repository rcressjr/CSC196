#include "Game.h"
#include "Actors/Player.h"
#include "Actors/Enemy.h"
#include "Actors/Projectile.h"

void Game::Initialize() {
	engine = std::make_unique<rj::Engine>();
	engine->Startup();
	scene = std::make_unique<rj::Scene>();
	scene->engine = engine.get();

	engine->Get<rj::AudioSystem>()->AddAudio("PlayerDied", "explosion.wav");
	engine->Get<rj::AudioSystem>()->AddAudio("EnemyDied", "EnemyKilled.wav");
	engine->Get<rj::AudioSystem>()->AddAudio("EnemyFire", "EnemyShoot.wav");
	engine->Get<rj::AudioSystem>()->AddAudio("PlayerShoot", "PlayerShoot.wav");

	engine->Get<rj::EventSystem>()->Subscribe("AddPoints", std::bind(&Game::OnAddPoints, this, std::placeholders::_1));
	engine->Get<rj::EventSystem>()->Subscribe("PlayerDead", std::bind(&Game::OnPlayerDead, this, std::placeholders::_1));
	engine->Get<rj::EventSystem>()->Subscribe("PlayerHurt", std::bind(&Game::OnPlayerHurt, this, std::placeholders::_1));

	//stateFunction = &Game::UpdateTitle;
}

void Game::Shutdown() {
	scene->RemoveAllActors();
	engine->Shutdown();
}

void Game::Update(float dt) {
	stateTimer += dt;

	switch (state)
	{
	case Game::eState::Title:
		if (Core::Input::IsPressed(VK_SPACE)) {
			state = eState::StartGame;
		}
		break;
	case Game::eState::StartGame:
		score = 0;
		lives = 18;
		state = eState::StartLevel;
		break;
	case Game::eState::StartLevel:
		UpdateLevelStart(dt);
		state = eState::Game;
		break;
	case Game::eState::Game:
		if (scene->GetActors<Enemy>().size() == 0) {
			level++;
			if (level >= 10 && level < 20) {
				creating = 10;
			}
			else if (level >= 20 && level < 30) {
				creating = 15;
			}
			else if (level >= 30 && level < 40) {
				creating = 20;
			}
			else if (level >= 40 && level < 50) {
				creating = 25;
			}
			else if (level >= 50) {
				creating += 5;
			}

			state = eState::StartLevel;
		}
		break;
	case Game::eState::GameOver:
		break;
	default:
		break;
	}

	engine->Update(dt);
	scene->Update(dt);
}

void Game::Draw(Core::Graphics& graphics) {
	switch (state)
	{
	case Game::eState::Title:
		graphics.SetColor(rj::Color::purple);
		graphics.DrawString(300, 300 + std::sin(stateTimer * 3) * 250, "VECTORY WARS");
		graphics.SetColor(rj::Color::blue);
		graphics.DrawString(320, 350, "Press Space to Start");

		break;
	case Game::eState::StartGame:
		break;
	case Game::eState::StartLevel: {
		break;
	}
	case Game::eState::Game:
		currentString = "level  " + std::to_string(level);
		graphics.SetColor(rj::Color::white);
		graphics.DrawString(400, 20, currentString.c_str());
		break;
	case Game::eState::GameOver:
		graphics.SetColor(rj::Color::red);
		graphics.DrawString(350, 300, "Game Over");
		break;
	default:
		break;
	}

	graphics.SetColor(rj::Color::white);
	graphics.DrawString(30, 20, std::to_string(score).c_str());
	graphics.DrawString(750, 20, std::to_string(lives).c_str());
	
	scene->Draw(graphics);
	engine->Draw(graphics);
}

void Game::UpdateTitle(float dt) {
	if (Core::Input::IsPressed(VK_SPACE)) {
		stateFunction = &Game::UpdateLevelStart;
		state = eState::StartGame;
	}
}

void Game::UpdateLevelStart(float dt) {
	if (scene->GetActors<Player>().size() == 0) {
		scene->AddActor(std::make_unique<Player>(rj::Transform{ rj::Vector2(400, 300), 0, 3 }, engine->Get<rj::ResourceSystem>()->Get<rj::Shape>("shape.txt"), 300.0f));
	}
	for (size_t i = 0; i < creating; i++) {
		scene->AddActor(std::make_unique<Enemy>(rj::Transform{ rj::Vector2(rj::RandomEnemy(0.0f, 800.0f), rj::RandomEnemy(0.0f, 600.0f)), rj::RandomEnemy(0.0f, rj::TwoPi), 2 }, engine->Get<rj::ResourceSystem>()->Get<rj::Shape>("enemy.txt"), 150.0f));
	}

	state = eState::Game;
}

void Game::OnAddPoints(const rj::Event& event) {
	score += std::get<int>(event.data);
}

void Game::OnPlayerHurt(const rj::Event& event) {
	lives--;
}

void Game::OnPlayerDead(const rj::Event& event) {
	state = eState::GameOver;
}
