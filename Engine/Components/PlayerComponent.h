#pragma once

#include "../FrameWork/Component.h"

#include "Physics/Collision.h"

#include "CharacterComponent.h"

namespace neu {

	class PlayerComponent : public CharacterComponent {

	public:

		PlayerComponent() = default;

		CLASS_CLONE(PlayerComponent)

		void Update() override;

		void Initialize() override;

		virtual bool Write(const rapidjson::Value& value) const override;

		virtual bool Read(const rapidjson::Value& value) override;

		virtual void onCollisionEnter(Actor* other) override;

		virtual void onCollisionExit(Actor* other) override;
		
		virtual void OnNotify(const Event& event) override;

		float jump = 150000;

	};

}
