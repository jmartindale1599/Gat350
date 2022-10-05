#pragma once

#include "RenderComponent.h"

#include <map>

namespace neu {

	class SpriteAnimeComponent : public RenderComponent {

	public:

		struct Sequence {

		std::string name;

		float fps = 0;

		int num_columns = 0;

		int num_rows = 0;

		int start_frame = 0;

		int end_frame = 0;

		bool loop = true;

		std::shared_ptr<Texture> texture;

		};

		CLASS_CLONE(SpriteAnimeComponent)

		virtual void Update() override;

		virtual void Draw(Renderer& renderer) override;

		virtual void SetSequence(const std::string& name);

		virtual std::string getSequence() { return m_sequence->name; };

		Rect& GetSource() override;

		virtual bool Write(const rapidjson::Value& value) const override;

		virtual bool Read(const rapidjson::Value& value) override;

		float fps = 0;

		int num_colums = 0;

		int num_rows = 0;

		int startFrame = 0;

		int endFrame = 0;

		int frame = 0;

		float frameTimer = 0;

		std::shared_ptr<Texture> m_texture;

		std::map<std::string, Sequence> m_sequences;

		Sequence* m_sequence = nullptr;

	};

}
