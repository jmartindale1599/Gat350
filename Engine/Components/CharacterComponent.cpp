
#include "CharacterComponent.h"

#include "Engine.h"

namespace neu {

	CharacterComponent::~CharacterComponent(){

		g_eventManager.UnSubscribe("EVENT_DAMAGE", m_owner);
	
	}

	void CharacterComponent::Initialize(){

		// bind events
		
		g_eventManager.Subscribe("EVENT_DAMAGE", std::bind(&CharacterComponent::OnNotify, this, std::placeholders::_1), m_owner);

		// bind collision events
		
		auto component = m_owner->GetComponent<CollisionComponent>();

		if (component){

			component->setCollisionEnter(std::bind(&CharacterComponent::onCollisionEnter, this, std::placeholders::_1));

			component->setCollisionExit(std::bind(&CharacterComponent::onCollisionExit, this, std::placeholders::_1));
		
		}
	
	}
	
	bool CharacterComponent::Write(const rapidjson::Value& value) const{

		return true;
	
	}

	bool CharacterComponent::Read(const rapidjson::Value& value){

		READ_DATA(value, health);
		
		READ_DATA(value, damage);
		
		READ_DATA(value, speed);

		return true;
	
	}

}
