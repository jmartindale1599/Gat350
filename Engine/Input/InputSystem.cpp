#include "InputSystem.h"

#include <sdl.h>

#include <iostream>

namespace neu {

	const uint32_t key_space = SDL_SCANCODE_SPACE;

	const uint32_t key_shift = SDL_SCANCODE_LSHIFT;

	const uint32_t key_w = SDL_SCANCODE_W;

	const uint32_t key_a = SDL_SCANCODE_A;
	
	const uint32_t key_s = SDL_SCANCODE_S;
	
	const uint32_t key_d = SDL_SCANCODE_D;

	const uint32_t key_escape = SDL_SCANCODE_ESCAPE;

	const uint32_t button_left = 0;
	
	const uint32_t button_middle = 1;

	const uint32_t button_right = 2;

	void InputSystem::Initialize(){

		const uint8_t* keyboardState = SDL_GetKeyboardState(&m_numKeys);

		m_keyboardState.resize(m_numKeys);

		std::copy(keyboardState, keyboardState + m_numKeys, m_keyboardState.begin());

		m_prevKeyboardState = m_keyboardState;

	}

	void InputSystem::Shutdown(){

		//

	}

	void InputSystem::Update(){

		SDL_Event event;

		SDL_PollEvent(&event);

		//save previouse state of keys

		m_prevKeyboardState = m_keyboardState;

		//get current state of keys
		
		const uint8_t* keyboardState = SDL_GetKeyboardState(nullptr);

		std::copy(keyboardState, keyboardState + m_numKeys, m_keyboardState.begin());

		//mouse

		int x, y;

		uint32_t buttons = SDL_GetMouseState(&x, &y);

		m_mousePosition = glm::vec2{ (float)x, (float)y };

		m_mouseRelative = m_mousePosition - m_prevMousePosition;

		m_prevMousePosition = m_mousePosition;

		m_prevMouseButtonState = m_mouseButtonState;


		m_mouseButtonState[0] = buttons & SDL_BUTTON_LMASK; // buttons [0001] & [0RML] 

		m_mouseButtonState[1] = buttons & SDL_BUTTON_MMASK; // buttons [0010] & [0RML] 

	    m_mouseButtonState[2] = buttons & SDL_BUTTON_RMASK; // buttons [0100] & [0RML]

	}

	InputSystem::State InputSystem::GetKeyState(uint32_t key){

		State keyState = State::Idle;

		bool keyDown = GetKeyDown(key);

		bool prevKeyDown = GetPrevKeyDown(key);

		if (keyDown) {

			keyState = (prevKeyDown) ? State::Held : State::Pressed;

		}else {

			keyState = (prevKeyDown) ? State::Released : State::Idle;

		}

		return keyState;
	
	}

	InputSystem::State InputSystem::GetButtonState(uint32_t key){

		State keyState = State::Idle;

		bool buttonDown = GetButtonDown(key);
		
		bool prevButtonDown = GetPreviousButtonDown(key);

		if (buttonDown){

			keyState = (prevButtonDown) ? State::Held : State::Pressed;
		
		}else{

			keyState = (prevButtonDown) ? State::Released : State::Idle;
		
		}

		return keyState;
	
	}

}