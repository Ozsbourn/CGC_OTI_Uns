#include "pch.h"

#include "framework.h"

#include "InputCodes.hpp"
#include "InputListener.hpp"
#include "InputManager.hpp"

#include "Log.hpp"

namespace FRMWRK {
	void InputManager::Init(void) {
		m_CursorScroll = m_CursorX = m_CursorY = 0x0;

		DEBUG("InputManager Initializated");
	}

	void InputManager::Close(void) {
		if (!m_Listener.empty()) {
			m_Listener.clear();
		}
			
		DEBUG("InputManager Closed");
	}

	void InputManager::SetWinRect(const RECT& winrect) {
		m_WinRect.left   = winrect.left;
		m_WinRect.right  = winrect.right;
		m_WinRect.top    = winrect.top;
		m_WinRect.bottom = winrect.bottom;
	}



	void InputManager::AddListener(InputListener* Listener) {
		m_Listener.push_back(Listener);
	}

	void InputManager::Run(const UINT& msg, WPARAM wParam, LPARAM lParam) {
		if (m_Listener.empty()) {
			return;
		}

		KEY_CODES KeyIndex;
		wchar_t   buffer[0x1];
		BYTE      lpKeyState[0x100]; // 0x100 == 256

		m_EventMoveCursor();         // событие движения мыши
		switch (msg) {
			case WM_KEYDOWN:
				KeyIndex = static_cast<KEY_CODES>(wParam);
				GetKeyboardState(lpKeyState);
				ToUnicode(wParam, HIWORD(lParam) & 0xFF, lpKeyState, buffer, 0x1, 0x0);
				m_EventKey(KeyIndex, buffer[0], true);
				break;
			case WM_KEYUP:
				KeyIndex = static_cast<KEY_CODES>(wParam);
				GetKeyboardState(lpKeyState);
				ToUnicode(wParam, HIWORD(lParam) & 0xFF, lpKeyState, buffer, 0x1, 0x0);
				m_EventKey(KeyIndex, buffer[0x0], false);
				break;
			case WM_LBUTTONDOWN:
				m_EventMouseKey(MOUSE_LEFT, true);
				break;
			case WM_LBUTTONUP:
				m_EventMouseKey(MOUSE_LEFT, false);
				break;
			case WM_RBUTTONDOWN:
				m_EventMouseKey(MOUSE_RIGHT, true);
				break;
			case WM_RBUTTONUP:
				m_EventMouseKey(MOUSE_RIGHT, false);
				break;
			case WM_MBUTTONDOWN:
				m_EventMouseKey(MOUSE_MIDDLE, true);
				break;
			case WM_MBUTTONUP:
				m_EventMouseKey(MOUSE_MIDDLE, false);
				break;
			case WM_MOUSEWHEEL:
				m_EventMouseScroll((short)GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA);
				break;
		}
	}

	// Событие движения курсора
	void InputManager::m_EventMoveCursor(void) {
		POINT pos;
		GetCursorPos(&pos);

		pos.x -= m_WinRect.left;
		pos.y -= m_WinRect.top;
	
		if (m_CursorX == pos.x && m_CursorY == pos.y) {
			return;
		}

		m_CursorX = pos.x;
		m_CursorY = pos.y;

		for (auto i : m_Listener) {
			if (!i) {
				continue;
			} else if (i->isMouseMoved(MouseEvent(m_CursorX, m_CursorY)) == true) {
				return;
			}
		}
	}

	// Событие кнопки мыши
	void InputManager::m_EventMouseKey(const MOUSE_KEY_CODES key, bool isPressed) {
		for (auto i : m_Listener) {
			if (!i) {
				continue;
			} 

			if (isPressed == true) {
				if (i->isMousePressed(MouseEventClick(key, m_CursorX, m_CursorY)) == true) {
					return;
				}
			} else {
				if (i->isMouseReleased(MouseEventClick(key, m_CursorX, m_CursorY)) == true) {
					return;
				}
			}
		}
	}

	// Событие вращения колесика мыши
	void InputManager::m_EventMouseScroll(int scroll) {
		if (m_CursorScroll == scroll) {
			return;
		}

		m_CursorScroll = scroll;

		for (auto i : m_Listener) {
			if (!i) {
				continue;
			} else if (i->isMouseScrolled(MouseEventScroll(m_CursorScroll, m_CursorX, m_CursorY)) == true) {
				return;
			}
		}
	}

	// Событие клавиши
	void InputManager::m_EventKey(const KEY_CODES key, wchar_t symb, bool isPressed) {
		for (auto i : m_Listener) {
			if (!i) {
				continue;
			}

			if (isPressed == true) {
				if (i->isKeyPressed(KeyEvent(symb, key)) == true) {
					return;
				}
			} else {
				if (i->isKeyReleased(KeyEvent(symb, key)) == true) {
					return;
				}
			}
		}
	}
};