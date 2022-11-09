#pragma once
#include "Framework/Component.h"

namespace neu{

	class LightComponent : public Component{

	public:
		
		CLASS_CLONE(LightComponent);

		enum class lightTypes{

			Point, Directional, Spot

		};

		void Update() override;

		virtual bool Write(const rapidjson::Value& value) const override;
		
		virtual bool Read(const rapidjson::Value& value) override;

	public:
		
		glm::vec3 color{ 0 };
	
		lightTypes type = lightTypes::Point;

		float cutoff = 45.0f;

		float exponent = 50.0f;

	};

}
