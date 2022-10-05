#include "SpriteComponent.h"

#include "../FrameWork/Actor.h"

#include "../Engine.h"

namespace neu {

	void SpriteComponent::Update() {



	}

	void SpriteComponent::Draw(Renderer& renderer) {

		renderer.Draw(m_texture, GetSource(), m_owner->m_transform, registration, flipHorizontal);

	}

	bool SpriteComponent::Write(const rapidjson::Value& value) const {

		return true;

	}

	bool SpriteComponent::Read(const rapidjson::Value& value) {

		std::string texture_name;

		READ_DATA(value, texture_name);

		m_texture = g_resources.Get<Texture>(texture_name, g_renderer);

		if (READ_DATA(value, source) == false) {

			source.x = 0;

			source.y = 0;

			source.w = (int)m_texture->GetSize().x;

			source.h = (int)m_texture->GetSize().y;

		}

		return true;

	}

	//Rect& SpriteAnimeComponent::GetSource(){
	//	
	//	Vector2 cellSize = m_texture->GetSize() / Vector2{ num_colums, num_rows };

	//	int column = (frame - 1) % num_colums;
	//	
	//	int row = (frame - 1) / num_colums;

	//	source.x = (int)(column * cellSize.x);
	//	
	//	source.y = (int)(row * cellSize.y);
	//	
	//	source.w = (int)(cellSize.x);
	//	
	//	source.h = (int)(cellSize.y);

	//	return source;
	//
	//}

}
