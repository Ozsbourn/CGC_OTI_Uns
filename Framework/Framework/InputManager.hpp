#include "InputCodes.hpp"
#include <list>
#include <wtypes.h>

#pragma once

namespace FRMWRK {
	class InputListener;

	class InputManager {
	private:
		std::list<InputListener*> m_Listener;

		RECT m_WinRect;
		int  m_CursorX;
		int  m_CursorY;
		int  m_CursorScroll;

		// Событие движения курсора
		void m_EventMoveCursor(void);
		// Событие клавиши мыши
		void m_EventMouseKey(const MOUSE_KEY_CODES key, bool isPressed);
		// Событие вращения колесика мыши
		void m_EventMouseScroll(int scroll);
		// Событие клавиши
		void m_EventKey(const KEY_CODES key, wchar_t symb, bool isPressed);	
	public:
		void Init(void);
		void Close(void);

		void Run(const UINT& msg, WPARAM wParam, LPARAM lParam);

		void AddListener(InputListener* listener);

		void SetWinRect(const RECT& rect);
	};
};