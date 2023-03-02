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

		// ������� �������� �������
		void m_EventMoveCursor(void);
		// ������� ������� ����
		void m_EventMouseKey(const MOUSE_KEY_CODES key, bool isPressed);
		// ������� �������� �������� ����
		void m_EventMouseScroll(int scroll);
		// ������� �������
		void m_EventKey(const KEY_CODES key, wchar_t symb, bool isPressed);	
	public:
		void Init(void);
		void Close(void);

		void Run(const UINT& msg, WPARAM wParam, LPARAM lParam);

		void AddListener(InputListener* listener);

		void SetWinRect(const RECT& rect);
	};
};