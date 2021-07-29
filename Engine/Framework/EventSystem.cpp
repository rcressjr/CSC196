#include "EventSystem.h"

void rj::EventSystem::Startup() {

}

void rj::EventSystem::Shutdown() {

}

void rj::EventSystem::Update(float dt) {

}

void rj::EventSystem::Subscribe(const std::string& name, function_t function) {
	Observer observer;
	observer.function = function;
	observers[name].push_back(observer);
}

void rj::EventSystem::Notify(const Event& event) { 
	auto& eventObservers = observers[event.name];
	for (auto& observer : eventObservers) {
		observer.function(event);
	}
}
