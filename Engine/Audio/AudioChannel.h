#pragma once

namespace FMOD{

	class Channel;

}


namespace neu {

	class AudioChannel{

	public:
		
		AudioChannel() {}
		
		AudioChannel(FMOD::Channel* channel) { m_channel = channel; } // !! set m_channel 

		bool IsPlaying();
		
		void Stop();

		void setPitch(float pitch);

		float getPitch();

		void setVolume(float volume);

		float getVolume();

	private:

		FMOD::Channel* m_channel = nullptr;

	};

}
