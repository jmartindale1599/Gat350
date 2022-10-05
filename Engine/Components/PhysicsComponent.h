#pragma once

#include "../FrameWork/Component.h"

#include "../Math/Vector2.h"

namespace neu {

	class PhysicsComponent : public Component{

	public:

		PhysicsComponent() = default;

		CLASS_CLONE(PhysicsComponent)

		void Update() override;

		virtual bool isDead() { if (this == nullptr) return true; }

		virtual void ApplyForce(const Vector2& force) { acceleration += force; }

		virtual bool Write(const rapidjson::Value& value) const override;

		virtual bool Read(const rapidjson::Value& value) override;
	
		Vector2 velocity;

		Vector2 acceleration;

		float damping = 1.0f;

	};

}
