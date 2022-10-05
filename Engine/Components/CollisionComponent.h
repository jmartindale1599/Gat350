#pragma once

#include "FrameWork/Component.h"

#include "Physics/Collision.h"

#include "Physics/PhysicsSystem.h"

#include <functional>

namespace neu {

	class CollisionComponent : public Component, public ICollision {

	public:

		CLASS_CLONE(CollisionComponent)

		using functionPtr = std::function<void(Actor*)>;

		virtual void Initialize() override;

		virtual bool Write(const rapidjson::Value& value) const override;

		virtual bool Read(const rapidjson::Value& value) override;

		virtual void Update() override;

		void setCollisionEnter(functionPtr function) { m_enterFunction = function; }

		void setCollisionExit(functionPtr function) { m_exitFunction = function; }

		virtual void onCollisionEnter(Actor* other) override;

		virtual void onCollisionExit(Actor* other) override;

	private:

		PhysicsSystem::CollisionData data;

		Vector2 scaleOffset{ 1,1 };

		functionPtr m_enterFunction;

		functionPtr m_exitFunction;

	};

}
