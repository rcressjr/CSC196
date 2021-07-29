#include "Player.h"
#include "Engine.h"
#include "Enemy.h"
#include "Projectile.h"

Player::Player(const rj::Transform& transform, std::shared_ptr<rj::Shape> shape, float speed) : Actor{ transform, shape }  {
	std::unique_ptr locator = std::make_unique<Actor>();
	locator->transform.localPosition = rj::Vector2{ -8, 0 };
	AddChild(std::move(locator));

	locator = std::make_unique<Actor>();
	locator->transform.localPosition = rj::Vector2{ 0, 5 };
	AddChild(std::move(locator));

	locator = std::make_unique<Actor>();
	locator->transform.localPosition = rj::Vector2{ 0, -5 };
	AddChild(std::move(locator));
}

void Player::Initialize() {
	std::unique_ptr engine = std::make_unique<Actor>(rj::Transform{}, scene->engine->Get<rj::ResourceSystem>()->Get<rj::Shape>("engine.txt"));
	engine->transform.localPosition = rj::Vector2{ -5, 0 };
	//locator->transform.localPosition = rj::DegToRad(180);
	AddChild(std::move(engine));
}

void Player::Update(float dt) {
	Actor::Update(dt);

	//movement
	float thrust = 0;
	if (Core::Input::IsPressed('A')) transform.rotation += -5 * dt;
	if (Core::Input::IsPressed('D')) transform.rotation += 5 * dt;
	if (Core::Input::IsPressed('W')) thrust = speed;
	
	transform.position.x = rj::Wrap(transform.position.x, 0.0f, 800.0f);
	transform.position.y = rj::Wrap(transform.position.y, 0.0f, 800.0f);

	rj::Vector2 acceleration;
	acceleration += rj::Vector2::Rotate(rj::Vector2::right, transform.rotation) * thrust;
	//rj::Vector2 gravity = (rj::Vector2{ 400, 300 } - transform.position).Normalized() * 200;
	//rj::Vector2 gravity = rj::Vector2::down * 50;
	//acceleration += gravity;

	velocity += acceleration * dt;
	transform.position += velocity * dt;

	velocity *= 0.99f;

	// fire
	fireTimer -= dt;
	if (fireTimer <= 0 && Core::Input::IsPressed(VK_SPACE)) {
		fireTimer = fireRate;
		{
			rj::Transform t = children[1]->transform;
			t.scale = 0.5f;

			std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(t, scene->engine->Get<rj::ResourceSystem>()->Get<rj::Shape>("bullet.txt"), 300);
			projectile->transform.localPosition = rj::DegToRad(180);
			projectile->tag = "Player";
			scene->AddActor(std::move(projectile));
		}

		{
			rj::Transform t = children[2]->transform;
			t.scale = 0.5f;

			std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(t, scene->engine->Get<rj::ResourceSystem>()->Get<rj::Shape>("bullet.txt"), 300);
			projectile->transform.localPosition = rj::DegToRad(180);
			projectile->tag = "Player";
			scene->AddActor(std::move(projectile));
		}
		//scene->engine->Get<rj::AudioSystem>()->PlayAudio("PlayerShoot");
	}
	
	rocketTimer -= dt;
	if (rocketTimer <= 0 && Core::Input::IsPressed(VK_SHIFT)) {
		rocketTimer = rocketRate;
		rj::Transform t = children[0]->transform;
		std::unique_ptr<Projectile> rocket = std::make_unique<Projectile>(t, scene->engine->Get<rj::ResourceSystem>()->Get<rj::Shape>("rocket.txt"), -300);
		rocket->transform.localPosition = rj::DegToRad(180);
		rocket->tag = "Player";
		scene->AddActor(std::move(rocket));
	}

	std::vector<rj::Color> colors = { rj::Color::red, rj::Color::purple, rj::Color::white, rj::Color::blue, rj::Color::orange };
	scene->engine->Get<rj::ParticleSystem>()->Create(children[0]->transform.position, 10, 3, colors, 150, children[0]->transform.rotation, rj::DegToRad(30));
}

void Player::OnCollision(Actor* actor) {
	if (dynamic_cast<Enemy*>(actor)) {
		scene->engine->Get<rj::ParticleSystem>()->Create(transform.position, 200, 1, rj::Color::purple, 50);
		scene->engine->Get<rj::AudioSystem>()->AddAudio("explosion", "explosion.wav");;

		if (lives <= 0) {
			destroy = true;
			rj::Event event;
			event.name = "PlayerDead";
			event.data = "yes I'm dead!";
			scene->engine->Get<rj::EventSystem>()->Notify(event);
		}
		else {
			lives--;
			rj::Event event;
			event.name = "PlayerHurt";
			event.data = "yes, I took damage";
			scene->engine->Get<rj::EventSystem>()->Notify(event);
		}
	}
}
