#pragma once

#include "Event.h"

#include <map>

#include <list>

namespace neu {

	class EventManager {

	public:

		struct Observer {

			GameObject* reciever = nullptr;

			Event::functionPtr function;

		};

		void Initialize();

		void Shutdown();

		void Update();

		void Subscribe(std::string name, Event::functionPtr function, GameObject* reciever = nullptr);

		void UnSubscribe(std::string name, GameObject* reciever);

		void Notify(const Event& event);

	private:

		std::map<std::string, std::list<Observer>> m_events;

	};

}
