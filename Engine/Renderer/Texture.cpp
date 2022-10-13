#include "Texture.h" 

#include "../Renderer/Renderer.h" 

#include "../Core/Logger.h"

#include <SDL.h> 

#include <SDL_image.h> 

namespace neu{

    Texture::~Texture(){

        if (!m_texture) {

            glDeleteTextures(1, &m_texture);

        }
    
    }



    bool Texture::Create(std::string filename, ...){

        va_list args;

        va_start(args, filename);

        Renderer& renderer = va_arg(args, Renderer);
 
        va_end(args);

        return Create(renderer, filename);
    }

    bool Texture::Create(Renderer& renderer, const std::string& filename){

        // load surface 
        
        SDL_Surface* surface = IMG_Load(filename.c_str());

        if (surface == nullptr) {

            LOG(SDL_GetError());

            SDL_FreeSurface(surface);

            return false;

        }

        glGenTextures(1, &m_texture);

        glBindTexture(m_target, m_texture);

        GLenum format = (surface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
        
        glTexImage2D(m_target, 0, format, surface->w, surface->h, 0, format, GL_UNSIGNED_BYTE, surface->pixels);

        glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        
        glTexParameteri(m_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        glTexParameteri(m_target, GL_TEXTURE_WRAP_S, GL_CLAMP);
        
        glTexParameteri(m_target, GL_TEXTURE_WRAP_T, GL_CLAMP);

        SDL_FreeSurface(surface);

        return true;

    }

    bool Texture::CreateFromSurface(SDL_Surface* surface, Renderer& renderer){
        
        /*if (m_texture) SDL_DestroyTexture(m_texture);

        m_texture = SDL_CreateTextureFromSurface(renderer.m_renderer, surface);

        SDL_FreeSurface(surface);
            
            if (m_texture == nullptr){

                LOG(SDL_GetError());
              
                return false;
            } */

        return true; 
    
    }

    neu::Vector2 Texture::GetSize() const{

        /*SDL_Point point;
        
        SDL_QueryTexture(m_texture, nullptr, nullptr, &point.x, &point.y);*/

        return Vector2{ 0, 0 };

    }

}
