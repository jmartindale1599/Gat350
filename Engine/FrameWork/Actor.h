#pragma once

#include "../Framework/GameObject.h"

#include "../Math/Transform.h"

#include "Component.h"

#include <vector>

namespace neu {

	class Scene;

	class Renderer;

	class Actor : public GameObject, public ISerializable {

	public:

		Actor() = default;

		Actor(const Actor& other);

		Actor(const Transform& transform) : m_transform{ transform } {}

		CLASS_CLONE(Actor)

		virtual void Update() override;

		virtual void Initialize() override;

		virtual void Draw(Renderer& renderer);

		void addChild(std::unique_ptr<Actor> child);

		void addComponent(std::unique_ptr<Component> component);

		//virtual void onCollision(Actor* other) {}

		float GetRadius() { return 0; }

		const std::string& getTag() { return tag; }

		void GetTag(const std::string& tag) { this->tag = tag; }

		const std::string& getName() { return name; }

		void GetName(const std::string& name) { this->name = name; }

		void setDestroy() { m_destroy = true; }

		void setActive(bool active) { this->active = active; }

		bool isActive() { return active; }

		bool isDestroyed() { return m_destroy; }

		Scene* GetScene() { return m_scene; }

		friend class Scene;

		friend class Component;

		Scene* scene;

		friend class Scene;

		Transform m_transform;

		template<typename T>

		T* GetComponent();
		
		virtual bool Write(const rapidjson::Value& value) const override;

		virtual bool Read(const rapidjson::Value& value) override;

	protected:

		std::string tag;

		std::string name;

		bool m_destroy = false;

		bool active = true;
		
		Scene* m_scene = nullptr;

		Actor* m_parent = nullptr;

		float lifespan = 0;

		std::vector<std::unique_ptr<Component>> m_components;

		std::vector<std::unique_ptr<Actor>> m_children;

	};

	template<typename T>

	inline T* Actor::GetComponent() {

		for (auto& component : m_components) {

			T* result = dynamic_cast<T*>(component.get());

			if (result) return result;

		}

		return nullptr;

	}

}

