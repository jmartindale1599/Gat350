#include "Actor.h"

#include "Factory.h"

#include "../Components/RenderComponent.h"

#include "Engine.h"

neu::Actor::Actor(const Actor& other){

	name = other.name;

	lifespan = other.lifespan;

	tag = other.tag;

	m_transform = other.m_transform;

	scene = other.scene;

	for (auto& component : other.m_components) {

		auto clone = std::unique_ptr<Component>((Component*)component->Clone().release());

		addComponent(std::move(clone));

	}

}

void neu::Actor::Update(){

	if (!active) return; 

	if (lifespan != 0){

		lifespan -= g_time.deltaTime;
		
		if (lifespan <= 0){

			setDestroy();
		
		}
	
	}

	for (auto& component : m_components) {

		component->Update();

	}

	for (auto& child : m_children) {

		child->Update();

	}

	if (m_parent) {

		m_transform.Update(m_parent->m_transform.matrix);

	}else {

		m_transform.Update();

	}

}

void neu::Actor::Initialize() {

	for (auto& component : m_components) {

		component->Initialize();

	}

	for (auto& child : m_children) {

		child->Initialize();

	}

}

void neu::Actor::Draw(Renderer& renderer){

	if (!active) return;

	for (auto& component : m_components) {
		
		auto renderComponent = dynamic_cast<RenderComponent*>(component.get());

		if (renderComponent) {

			renderComponent->Draw(renderer);

		}

		//component->Update();

	}

	for (auto& child : m_children) {

		child->Draw(renderer);

	}

}

void neu::Actor::addChild(std::unique_ptr<Actor> child){
	
	child->m_parent = this;

	child->m_scene = this->m_scene;

	m_children.push_back(std::move(child));

}

void neu::Actor::addComponent(std::unique_ptr<Component> component){

	component->m_owner = this;

	m_components.push_back(std::move(component));

}

bool neu::Actor::Write(const rapidjson::Value& value) const{



	return true;

}

bool neu::Actor::Read(const rapidjson::Value& value){

	READ_DATA(value, tag);

	READ_DATA(value, name);

	READ_DATA(value, active);

	READ_DATA(value, lifespan);

	if (value.HasMember("transform")) m_transform.Read(value["transform"]);

	if (value.HasMember("components") && value["components"].IsArray()) {

		for (auto& componentValue : value["components"].GetArray()) {

			std::string type;

			READ_DATA(componentValue, type);

			auto component = Factory::Instance().Create<Component>(type);

			if (component) {

				component->Read(componentValue);

				addComponent(std::move(component));

			}

		}

	}

	return true;

}
