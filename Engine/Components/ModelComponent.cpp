#include "ModelComponent.h"

#include "Renderer/Material.h" 

#include "Model.h"

#include "Engine.h"

#include "FrameWork/Actor.h"

void neu::ModelComponent::Draw(Renderer& renderer){

	material->Bind();
		
	material->GetProgram() -> SetUniform("model", (glm::mat4)m_owner->m_transform);

	model->m_vertexBuffer.Draw();

}

bool neu::ModelComponent::Write(const rapidjson::Value& value) const{

	return true;

}

bool neu::ModelComponent::Read(const rapidjson::Value& value){

	std::string model_name;

	READ_DATA(value, model_name);

	std::string material_name;

	READ_DATA(value, material_name);

	model = g_resources.Get<Model>(model_name);

	material = g_resources.Get<Material>(material_name);

	return true;

}
