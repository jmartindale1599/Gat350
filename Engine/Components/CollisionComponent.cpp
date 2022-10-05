#include "CollisionComponent.h"

#include "Engine.h"

#include <iostream>

namespace neu {

    void CollisionComponent::Initialize() {

        auto component = m_owner->GetComponent<RBPhysicsComponent>();

        if (component){

            if ( data.size.x == 0 && data.size.y == 0 ){

                auto renderComponent = m_owner->GetComponent<RenderComponent>(); 

                    if (renderComponent){

                        data.size = Vector2{ renderComponent->GetSource().w, renderComponent->GetSource().h};

                    }

            }

            data.size = data.size * scaleOffset; //*m_owner->m_transform.scale;

            if (component->m_body->GetType() == b2_staticBody) {

                g_physicsSystem.SetCollisionBoxStatic(component->m_body, data, m_owner);

            }else {

                g_physicsSystem.SetCollisionBox(component->m_body, data, m_owner);

            }
        
        }

    }

    void CollisionComponent::Update() {



    }

    void CollisionComponent::onCollisionEnter(Actor* other) {

        if(m_enterFunction) m_enterFunction(other);

    }

    void CollisionComponent::onCollisionExit(Actor* other) {

        if (m_exitFunction) m_exitFunction(other);

    }

    bool CollisionComponent::Write(const rapidjson::Value& value) const {

        return true;

    }

    bool CollisionComponent::Read(const rapidjson::Value& value) {

        READ_DATA(value, data.size);

        READ_DATA(value, data.density);
        
        READ_DATA(value, data.friction);
        
        READ_DATA(value, data.restitution);
        
        READ_DATA(value, data.isTrigger);

        READ_DATA(value, scaleOffset);

        return true;

    }

}