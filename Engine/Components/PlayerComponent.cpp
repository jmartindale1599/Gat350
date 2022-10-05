
#include "PlayerComponent.h"

#include "../Engine.h"

#include "../Math/Transform.h"

#include <iostream>

void neu::PlayerComponent::Initialize() {

	CharacterComponent::Initialize();

}

void neu::PlayerComponent::Update(){

	Vector2 direction = Vector2::zero;

	auto camera = m_owner->GetScene()->getActorFromName("Camera");
	
	if (camera){

		camera->m_transform.position = Math::Lerp(camera->m_transform.position, m_owner->m_transform.position, 2 * g_time.deltaTime);
	
	}

	if (neu::g_inputSystem.GetKeyDown(neu::key_w)) {

		//"jump"

		direction = Vector2::up;

	}

	if (neu::g_inputSystem.GetKeyDown(neu::key_a)) {

		direction = Vector2::left;

	}

	if (neu::g_inputSystem.GetKeyDown(neu::key_d)) {

		direction = Vector2::right;

	}

	Vector2 velocity;

	auto component = m_owner->GetComponent<PhysicsComponent>();

	if (component) {

		component->ApplyForce(direction * speed);

		velocity = component->velocity;

	}

	if (g_inputSystem.GetKeyDown(key_space)){

		auto component = m_owner->GetComponent<PhysicsComponent>();

		if (component) {

			component->ApplyForce(direction * speed);

		}

	}

	auto animeComponent = m_owner->GetComponent<SpriteAnimeComponent>();

	if (animeComponent){

		if (velocity.x != 0) animeComponent->setFlipHorizontal(velocity.x < 0);
		
		if (std::fabs(velocity.x) > 0){

			animeComponent->SetSequence("fire");
		
		}
		else{

			animeComponent->SetSequence("idle");
		
		}
	
	}

}

bool neu::PlayerComponent::Write(const rapidjson::Value& value) const{

	return false;

}

bool neu::PlayerComponent::Read(const rapidjson::Value& value){

	CharacterComponent::Read(value);

	READ_DATA(value, jump);

	return true;

}

void neu::PlayerComponent::onCollisionEnter(Actor* other){

	auto checkFace = m_owner->GetComponent<SpriteAnimeComponent>();

	if (other->getName() == "Coin") {

		Event event;

		event.name = "EVENT_ADD_POINTS";

		event.data = 100;

		g_eventManager.Notify(event);

		other->setDestroy();

	}

	if (other->getName() == "tile03") {

		std::cout << "Waah" << std::endl;

		Event event;

		event.name = "EVENT_ADD_DIES";

		event.data = 100;

		g_eventManager.Notify(event);

		m_owner->setDestroy();

		//reset game

	}

	if (other->getName() == "tile04") {

		std::cout << "h winner is you!!!!!" << std::endl;

	}

	if (other->getName() == "tile01" && checkFace->getSequence() == "fire") {

		Event event;

		event.name = "EVENT_ADD_DIES";

		g_eventManager.Notify(event);

		other->setDestroy();

	}else if (other->getName() == "tile01" && checkFace->getSequence() != "fire") {

		m_owner->setDestroy();

		//reset game

	}

	if (other->getTag() == "Enemy") {

		Event event;

		event.name = "EVENT_ADD_POINTS";

		event.data = damage;

		event.reciever = other;

		g_eventManager.Notify(event);

	}

	std::cout << "player enter\n";

}

void neu::PlayerComponent::onCollisionExit(Actor* other){

	std::cout << "player exit\n";

}

void neu::PlayerComponent::OnNotify(const Event& event){

	if (event.name == "EVENt_DAMAGE") {

		health -= std::get<float>(event.data);

		std::cout << health << std::endl;

		if (health <= 0) {

			//player dead

		}

	}

}
