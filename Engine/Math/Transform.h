#pragma once

#include "Vector2.h"

#include "3X3.h"

#include "MathUtils.h"

#include "../Serialization/ISerialisable.h"

namespace neu {

	struct Transform : public ISerializable {

		glm::vec3 position{ 1 };

		glm::quat rotation;

		glm::vec3 scale{ 1 };

		glm::mat4 matrix;

		virtual bool Write(const rapidjson::Value& value) const override;

		virtual bool Read(const rapidjson::Value& value) override;

		Transform() = default;

		Transform(const glm::vec3& position, const glm::quat& rotation = glm::vec3{0}, const glm::vec3& scale = glm::vec3{1}) : position{position}, rotation{rotation}, scale{scale}{}

		glm::vec3 getRight() { return rotation * glm::vec3{ 1, 0, 0 }; }
		
		glm::vec3 getUp() { return rotation * glm::vec3{ 0, 1, 0 }; }
		
		glm::vec3 getForward() { return rotation * glm::vec3{ 0, 0, 1 }; }

		void Update() {

			matrix = *this;

		}

		void Update(const glm::mat4& parent) {

			matrix = parent * (glm::mat4)*this;

		}

		operator glm::mat4() const {

			glm::mat4 mxScale = glm::scale(scale);

			glm::mat4 mxRotation =glm::mat4_cast(rotation);

			glm::mat4 mxTranslation = glm::translate(position);

			return { mxTranslation * mxRotation * mxScale };

		}

	};

}

