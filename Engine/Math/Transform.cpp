#include "Transform.h"

namespace neu {

    bool Transform::Write(const rapidjson::Value& value) const {

        return true;

    }

    bool Transform::Read(const rapidjson::Value& value) {
        
        READ_DATA(value, position);

        glm::vec3 euler;

        READ_NAME_DATA(value, "rotation", euler);

        rotation = Math::EulerToQuaternion(euler);

        READ_DATA(value, scale);

        return true;

    }

}
