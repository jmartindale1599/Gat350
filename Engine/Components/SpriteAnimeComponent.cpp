#include "SpriteAnimeComponent.h"

#include "../FrameWork/Actor.h"

#include "../Engine.h"

void neu::SpriteAnimeComponent::Update(){


    frameTimer += g_time.deltaTime;
    
    if (frameTimer >= 1.0f / m_sequence->fps){

        frameTimer = 0;
        
        frame++;
        
        if (frame > m_sequence->end_frame){

            frame = (m_sequence->loop) ? m_sequence->start_frame : m_sequence->end_frame;
        
        }
    
    }

 /*   frameTimer += g_time.deltaTime;

    if (frameTimer >= 1.0f / fps){

        frameTimer = 0;
        
        frame++;
        
        if (frame > endFrame){

            frame = startFrame;
        
        }
    }

    Vector2 cellSize = m_texture->GetSize() / Vector2{ num_colums, num_rows };

    int column = (frame - 1) % num_colums;

    int row = (frame - 1) / num_colums;

    source.x = (int)(column * cellSize.x);

    source.y = (int)(row * cellSize.y);
    
    source.w = (int)(cellSize.x);
    
    source.h = (int)(cellSize.y);*/

}

void neu::SpriteAnimeComponent::Draw(Renderer& renderer){

    renderer.Draw(m_sequence->texture, GetSource(), m_owner->m_transform, registration, flipHorizontal);

}

void neu::SpriteAnimeComponent::SetSequence(const std::string& name){
    
    if (m_sequence && m_sequence->name == name) return;

    if (m_sequences.find(name) != m_sequences.end()){

        m_sequence = &m_sequences[name];

        frame = m_sequence->start_frame;
 
        frameTimer = 0;
    
    }

}

neu::Rect& neu::SpriteAnimeComponent::GetSource(){

    /*glm::vec2 cellSize = m_sequence->texture->GetSize() / glm::vec2{ m_sequence->num_columns, m_sequence->num_rows };

    int column = (frame - 1) % m_sequence->num_columns;
    
    int row = (frame - 1) / m_sequence->num_columns;

    source.x = (int)(column * cellSize.x);
    
    source.y = (int)(row * cellSize.y);
    
    source.w = (int)(cellSize.x);
    
    source.h = (int)(cellSize.y);

    return source;*/

    return source;

}

bool neu::SpriteAnimeComponent::Write(const rapidjson::Value& value) const{

    return true;

}

bool neu::SpriteAnimeComponent::Read(const rapidjson::Value& value){

    // read in animation sequences 
    if (value.HasMember("sequences") && value["sequences"].IsArray()){

        for (auto& sequenceValue : value["sequences"].GetArray()){

            Sequence sequence;

            READ_DATA(sequenceValue, sequence.name);
            
            READ_DATA(sequenceValue, sequence.fps);
            
            READ_DATA(sequenceValue, sequence.num_columns);
            
            READ_DATA(sequenceValue, sequence.num_rows);
            
            READ_DATA(sequenceValue, sequence.start_frame);
            
            READ_DATA(sequenceValue, sequence.end_frame);

            std::string texture_name;
            
            READ_DATA(sequenceValue, texture_name);

            sequence.texture = g_resources.Get<Texture>(texture_name, g_renderer);

            m_sequences[sequence.name] = sequence;
        
        }
    
    }

    std::string default_sequence;

    if (!READ_DATA(value, default_sequence) && !m_sequences.empty()){

        default_sequence = m_sequences.begin()->first;
    
    }

    SetSequence(default_sequence);

    return true;

}
