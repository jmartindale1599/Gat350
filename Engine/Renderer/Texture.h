#pragma once

#include "Math/MathUtils.h"

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
		 
		bool CreateFromSurface(SDL_Surface* surface, Renderer& renderer);

		bool CreateTexture(int width, int height);

		bool CreateDepthTexture(int width, int height);

		bool Load(const std::string& filename);

		void setActive(GLuint unit) { glActiveTexture(unit); }

		void Bind() { glBindTexture(m_target, m_texture); }

		glm::ivec2 GetSize() const;

		static GLenum GetInternalFormat(GLuint format);

		friend class Renderer;

		friend class FrameBuffer;

		GLuint m_texture = 0;

	protected:

		void FlipSurface(SDL_Surface* surface);

		GLenum m_target = GL_TEXTURE_2D;

		int m_width = 0;

		int m_height = 0;

	};

}

