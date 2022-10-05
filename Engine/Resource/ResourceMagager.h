#pragma once

#include "Resource.h"

#include <map>

#include <string>

#include <memory>

namespace neu {

	class ResourceManager
	{
	public:
		ResourceManager() = default;

		~ResourceManager() = default;

		void initialize();

		void shutDown();

		template <typename T, typename ... TArgs>

		std::shared_ptr<T> Get(const std::string& name, TArgs... args);

	private:

		std::map<std::string, std::shared_ptr<Resource>> m_library;

	};

	template<typename T, typename ... TArgs>

	inline std::shared_ptr<T> ResourceManager::Get(const std::string& name, TArgs... args){

		if (m_library.find(name) != m_library.end()){

			// found 

			return std::dynamic_pointer_cast<T>(m_library[name]);

		}else{

			// not found, create resource and enter into resources 

			std::shared_ptr<T> resource = std::make_shared<T>();

			resource->Create(name, args...);

			m_library[name] = resource;

			return resource;

		}

	}

}
