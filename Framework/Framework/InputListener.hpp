#pragma once
#include "InputCodes.hpp"

namespace FRMWRK {

	// Класс-прототип для событий мыши
	struct MouseEvent {
		int m_x;
		int m_y;

		MouseEvent(int x, int y) : m_x(x), m_y(y) {}
	};

	// Событие клика мыши
	struct MouseEventClick : public MouseEvent {
		const MOUSE_KEY_CODES m_key;
		
		MouseEventClick(MOUSE_KEY_CODES key, int x, int y) : MouseEvent(x, y), m_key(key) {}
	};

	// Событие прокручивания колесиком мыши
	struct MouseEventScroll : public MouseEvent {
		int m_scroll;

		MouseEventScroll(int scroll, int x, int y) : MouseEvent(x, y), m_scroll(scroll) {}
	};

	// Событие нажатия на клавишу
	struct KeyEvent {
		const wchar_t   m_symb;
		const KEY_CODES m_key;

		KeyEvent(wchar_t symb, KEY_CODES key) : m_symb(symb), m_key(key) {}
	};

	// Слушатель для событий 
	class InputListener {
	public:
		virtual bool isMousePressed(const MouseEventClick& arg) {
			return false;
		}

		virtual bool isMouseReleased(const MouseEventClick& arg) {
			return false;
		}

		virtual bool isMouseScrolled(const MouseEventScroll& arg) {
			return false;
		}

		virtual bool isMouseMoved(const MouseEvent& arg) {
			return false;
		}



		virtual bool isKeyPressed(const KeyEvent& arg) {
			return false;
		}

		virtual bool isKeyReleased(const KeyEvent& arg) {
			return false;
		}
	};
};