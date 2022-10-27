#include "LightComponent.h"

#include "Engine.h"

namespace neu{

	void LightComponent::Update(){

		// transform the light position by the view, puts light in model view space
		
		glm::vec4 position = g_renderer.getView() * glm::vec4(m_owner->m_transform.position, 1);

		// get all programs in the resource system
		
		auto programs = g_resources.Get<Program>();
		
		// set programs light properties
		
		for (auto& program : programs){

			program->Use();

			program->SetUniform("light.ambient", glm::vec3(0.2f));

			program->SetUniform("light.color", color);
			
			program->SetUniform("light.position", position);
		
		}
	
	}

	bool LightComponent::Write(const rapidjson::Value& value) const{

		return true;
	
	}

	bool LightComponent::Read(const rapidjson::Value& value){

		READ_DATA(value, color);

		return true;
	
	}

}