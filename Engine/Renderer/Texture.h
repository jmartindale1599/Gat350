#pragma once

#include "..\Math\Vector2.h" 

#include "../Resource/Resource.h"

#include "Renderer.h"

#include <string> 

#include <glad/glad.h>

struct SDL_Pointer;

struct SDL_Texture;

struct SDL_Surface;

namespace neu{

	class Renderer;

	class Texture : public Resource{

	public:

		Texture() = default;

		~Texture();

		bool Create(std::string filename, ...) override;
		 
		bool Create(Renderer& renderer, const std::string& filename);

		bool CreateFromSurface(SDL_Surface* surface, Renderer& renderer);

		void setActive(GLuint unit) { glActiveTexture(unit); }

		void Bind() { glBindTexture(m_target, m_texture); }

		Vector2 GetSize() const;

		friend class Renderer;

	private:

		//SDL_Texture* m_texture = nullptr;

		void FlipSurface(SDL_Surface* surface);

		GLuint m_texture = 0;

		GLenum m_target = GL_TEXTURE_2D;

	};

}

