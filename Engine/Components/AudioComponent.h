#pragma once

#include "../FrameWork/Component.h"

#include "Audio/AudioChannel.h"

namespace neu {

	class AudioComponent : public Component {

	public:

		AudioComponent() = default;

		~AudioComponent();

		CLASS_CLONE(AudioComponent)

		void Initialize() override;

		void Update() override;

		void Play();

		void Stop();

		AudioChannel m_channel;

		std::string m_soundName;

		bool m_playOnAwake = false;

		bool m_loop = false;

		float m_volume = 1;

		float m_pitch = 1;

		virtual bool Write(const rapidjson::Value& value) const override;

		virtual bool Read(const rapidjson::Value& value) override;

	};

}