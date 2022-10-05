#include "Font.h"

#include "..\Core\Logger.h"

#include "Math/Color.h"

#include "SDL_surface.h"

#include <SDL_ttf.h>

neu::Font::Font(const std::string& filename, int fontSize){

	Load(filename, fontSize);

}

neu::Font::~Font(){

	if (!m_ttfFont) {

		TTF_CloseFont(m_ttfFont);

	}

}

bool neu::Font::Create(std::string filename, ...){

    va_list args;

    va_start(args, filename);

    int fontSize = va_arg(args, int);

    va_end(args);

	return Load(filename, fontSize);

}

SDL_Surface* neu::Font::CreateSurface(const std::string& text, const Color& color){
	
	SDL_Color c = *((SDL_Color*)(&color));
	
	SDL_Surface* surface = TTF_RenderText_Solid(m_ttfFont, text.c_str(), c);
	
	if (surface == nullptr){

		LOG(SDL_GetError());
	
	}

	return surface;


}

bool neu::Font::Load(const std::string& filename, int fontSize){

	m_ttfFont = TTF_OpenFont(filename.c_str(), fontSize);
	
	if (m_ttfFont == nullptr){

		LOG("Could not load font %s", filename.c_str());
		
		return false;
	
	}

	return true;
}
