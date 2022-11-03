#pragma once

#include "Resource.h"

#include "Core/Utilities.h"

#include <map>

#include <vector>

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

		template<typename T>

		std::vector<std::shared_ptr<T>> Get();

	private:
		std::map<std::string, std::shared_ptr<Resource>> m_resources;

	};

	template<typename T, typename ... TArgs>

	inline std::shared_ptr<T> ResourceManager::Get(const std::string& name, TArgs... args){

		//std::string lowerName = tolower(name);

		std::string lower = ToLower(name);

		if (m_resources.find(lower) != m_resources.end()){

			// found 

			return std::dynamic_pointer_cast<T>(m_resources[lower]);

		}else{

			// not found, create resource and enter into resources 

			std::shared_ptr<T> resource = std::make_shared<T>();

			resource->Create(lower, args...);

			m_resources[lower] = resource;

			return resource;

		}

	}

	template <typename T>

	inline std::vector<std::shared_ptr<T>> ResourceManager::Get(){

		std::vector<std::shared_ptr<T>> result;

		for (auto& resource : m_resources) {

			// get the value of the map (first = key, second = value)

			// the value is a shared_ptr, get() the raw pointer and try to cast to type T*

			if (dynamic_cast<T*>(resource.second.get())) {

				// if it is of type T, add the shared pointer to the vector

				result.push_back(std::dynamic_pointer_cast<T>(resource.second));

			}

		}

		return result;

	}

}
