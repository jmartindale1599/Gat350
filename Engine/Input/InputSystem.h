#pragma once

#include "Math/MathUtils.h"

#include <cstdint>

#include <vector>

#include <map>

#include <array>

#include <string>

namespace neu {

	class InputSystem {

	public:

		enum State {

			Idle, Pressed, Held, Released

		};

		InputSystem() = default;

		~InputSystem() = default;

		void Initialize();

		void Shutdown();

		void Update();

		State GetKeyState(uint32_t key);

		bool GetKeyDown(int key) { return m_keyboardState[key]; }

		bool GetPrevKeyDown(uint32_t key) { return m_prevKeyboardState[key]; }

		const glm::vec2& GetMousePosition() const { return m_mousePosition; }

		const glm::vec2& GetMouseRelative() const { return m_mouseRelative; }

		bool GetButtonDown(uint32_t button) { return m_mouseButtonState[button]; }

		bool GetPreviousButtonDown(uint32_t button) { return m_prevMouseButtonState[button]; }

		int m_numKeys;

	private:

		//keyboard

		std::vector<uint8_t> m_keyboardState;
		
		std::vector<uint8_t> m_prevKeyboardState;

		// mouse

		glm::vec2 m_mousePosition;

		glm::vec2 m_prevMousePosition;

		glm::vec2 m_mouseRelative;
		
		std::array<uint8_t, 3> m_mouseButtonState;

		std::array<uint8_t, 3> m_prevMouseButtonState;

	};

	extern const uint32_t key_space;

	extern const uint32_t key_shift;
	
	extern const uint32_t key_w;
	
	extern const uint32_t key_a;
	
	extern const uint32_t key_s;
	
	extern const uint32_t key_d;

	extern const uint32_t key_escape;

	extern const uint32_t button_left;

	extern const uint32_t button_middle;

	extern const uint32_t button_right;

}

