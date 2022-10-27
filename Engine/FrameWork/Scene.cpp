#include "Scene.h"

#include "Engine.h"

#include "Factory.h"

#include <algorithm>

#include <iostream>

namespace neu {

	void Scene::Update() {

		auto iter = m_actors.begin();

		while (iter != m_actors.end()) {

			(*iter)->Update();

			if ((*iter)->m_destroy) {

				iter = m_actors.erase(iter);

			}
			else {

				iter++;

			}

		}

	}

	void Scene::Initialize(){

		for (auto& actor : m_actors) {

			actor->Initialize();

		}

	}

	void Scene::Draw(Renderer& renderer){

		// get camera / set renderer view/projection 

		auto camera =  getActorFromName("Camera");

		if (camera){

			g_renderer.setView(camera->GetComponent<CameraComponent>() -> GetView());

			g_renderer.setProjection(camera->GetComponent<CameraComponent>() -> GetProjection());

		}

		// draw actors 

		for (auto& actor : m_actors){

			actor->Draw(renderer);
		
		}

	}

	bool Scene::Create(std::string name, ...) {

		rapidjson::Document document;

		bool success = neu::json::Load(name, document);

		// here

		if (!success) {

			LOG("Error loading scene file %s.", name.c_str());

		}

		Read(document);

		Initialize();

		LOG("Scene initiallized . . . ");

		return true;

	}

	void Scene::Add(std::unique_ptr<Actor> actor){

		actor->m_scene = this;

		m_actors.push_back(std::move(actor));

	}

	void Scene::removeAll(){

		for (auto& actor : m_actors) { actor->setDestroy(); }

		m_actors.clear();

	}

	bool Scene::Write(const rapidjson::Value& value) const{

		return true;
	
	}

	bool Scene::Read(const rapidjson::Value& value){

		if (!value.HasMember("actors") || !value["actors"].IsArray()) {

			return false;

		}

		//read actors

		for (auto& actorValue : value["actors"].GetArray()) {

			std::string type;

			READ_DATA(actorValue, type);

			auto actor = Factory::Instance().Create<Actor>(type);

			if (actor) {

				//read actor

				actor->Read(actorValue);

				bool prefab = false;

				READ_DATA(actorValue, prefab);

				if (prefab) {

					std::string name = actor->getName();

					Factory::Instance().RegisterPrefab(name, std::move(actor));

				}else {

					Add(std::move(actor));

				}

			}

		}

		return true;
	
	}

}
