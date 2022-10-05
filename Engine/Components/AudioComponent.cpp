#include "AudioComponent.h"

#include "../Engine.h"

neu::AudioComponent::~AudioComponent(){

	Stop();

}

void neu::AudioComponent::Initialize(){

	if (m_playOnAwake){

		Play();
	
	}

}

void neu::AudioComponent::Update(){



}

void neu::AudioComponent::Play(){

	Stop();

	g_audio.PlayAudio(m_soundName, m_volume, m_pitch, m_loop);

}

void neu::AudioComponent::Stop(){

	m_channel.Stop();

}

bool neu::AudioComponent::Write(const rapidjson::Value& value) const{

	return true;

}

bool neu::AudioComponent::Read(const rapidjson::Value& value){

	READ_DATA(value, m_soundName);

	READ_DATA(value, m_loop);
	
	READ_DATA(value, m_volume);
	
	READ_DATA(value, m_pitch);
	
	READ_DATA(value, m_playOnAwake);

	g_audio.AddAudio(m_soundName, m_soundName);

	return true;

}
