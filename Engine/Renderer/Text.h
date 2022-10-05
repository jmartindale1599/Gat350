#pragma once

#include <string>

//#include <SDL.h>

struct SDL_Texture;

	namespace neu{

		class Font;
		
		class Renderer;
		
		struct Color;

		struct Vector2;

		class Text{

		public:

			Text() = default;
				
			Text(Font* font); //<!!initialize m_font with font parameter>{}
			
			~Text();

			void Create(Renderer& renderer, const std::string& text, const Color& color);
			
			void Draw(Renderer& renderer, const Vector2& position);

			friend class Renderer;

			friend class Font;

		private:
			
			Font* m_font = nullptr; 
			
			SDL_Texture* m_texture = nullptr;
		
		};

	}

