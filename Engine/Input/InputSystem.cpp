#include "InputSystem.h"

#include <sdl.h>

#include <iostream>

namespace neu {

	const uint32_t key_space = SDL_SCANCODE_SPACE;

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

		//std::cout << (bool)m_keyboardState[SDL_SCANCODE_W] << std::endl;

		//for (auto state : m_keyboardState) {

		//	std::cout << (bool)state << std::endl;

		//}

		m_prevMouseButtonState = m_mouseButtonState;

		int x, y;

		uint32_t buttons = SDL_GetMouseState(&x, &y);

		m_mousePosition = neu::Vector2{ x , y };

		m_mouseButtonState[0] = buttons & SDL_BUTTON_LMASK; // buttons [0001] & [0RML] 

		m_mouseButtonState[1] = buttons & SDL_BUTTON_MMASK; // buttons [0010] & [0RML] 

	    m_mouseButtonState[2] = buttons & SDL_BUTTON_RMASK; // buttons [0100] & [0RML]

	}

	neu::InputSystem::State InputSystem::GetButtonState(uint32_t button){

		State keyState = State::Idle;

		bool buttonDown = GetButtonDown(button);

		bool prevButtonDown = GetPreviousButtonDown(button);

		if (buttonDown && prevButtonDown) {

			keyState = State::Held;

		}else if (!buttonDown && prevButtonDown) {

			keyState = State::Released;

		}
		else if (!prevButtonDown && buttonDown) {

			keyState = State::Pressed;

		}
		else {

			keyState = State::Idle;

		}

		return keyState;
	
	}

}