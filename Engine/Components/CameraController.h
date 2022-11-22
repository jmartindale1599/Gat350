#pragma once 

#include "Framework/Component.h" 

namespace neu{

	class CameraController : public Component{

	public:

		CLASS_CLONE(CameraController)

		void Initialize() override;

		void Update() override;

		virtual bool Write(const rapidjson::Value& value) const override;

		virtual bool Read(const rapidjson::Value& value) override;

		float sensitivity = 0.1f;

		float speed = 0;

	private:

		float m_yaw = 0.0f; // left and right

		float m_pitch = 0; // up and down

	};

}
