#include "InputManager.hpp"

#pragma once

namespace FRMWRK {
	struct WinDesc {
		WinDesc(void) 
		: Caption(L""),
		  Width(640),
		  Height(480),
	      PosX(200),
		  PosY(20),
	      isResizing(true) {}

		int PosX;
		int PosY;
		std::wstring Caption;	// заголовок окна
		int Width;				// ширина клиентской части окна
		int Height;				// высота клиентской части окна
		bool isResizing;
	};

	class Window {
	private:
		void m_UpdateWindowState(void);

		static Window* m_WndInstance;

		WinDesc       m_Desc;	     // описание окна
		InputManager* m_InputMgr;
		HWND          m_WndHandler;  // дескриптор окна	
		bool          m_isExit;		 // флаг сообщающий о событии выхода	
		bool          m_isActive;    // окно активно?
		bool          m_isMinimized;
		bool          m_isMaximized;
		bool          m_isResize;	 // если окно изменило размер
	public:
		Window(void);


		static Window* Get(void) { return m_WndInstance; }


		// Создать окно
		bool Create(const WinDesc& desc);


		// Обработка событий окна
		void RunEvent(void);


		// Закрыть окно.
		void Close(void);


		void SetInputMgr(InputManager* imgr);


		HWND GetHWND(void)   const { return m_WndHandler; }
		int  GetLeft(void)   const { return m_Desc.PosX; }
		int  GetTop(void)    const { return m_Desc.PosY; }
		int  GetWidth(void)  const { return m_Desc.Width; }
		int  GetHeight(void) const { return m_Desc.Height; }
		

		// Вернуть заголовок окна
		const std::wstring& GetCaption(void) const { return m_Desc.Caption; }


		// сообщает, было ли сообщение о выходе
		bool IsExit(void) const   { return m_isExit; }
		// сообщает об активности окна
		bool IsActive(void) const { return m_isActive; }


		// сообщает об изменении окна
		// предупреждение: после вызова оповещает окно об обработке события
		bool IsResize(void) {
			bool ret   = m_isResize;
			m_isResize = false;

			return ret;
		}

		// обработка событий
		LRESULT WndProc(HWND hwnd, UINT nMsg, WPARAM wParam, LPARAM lParam);
	};

	// обработка событий
	static LRESULT CALLBACK StaticWndProc(HWND hwnd, UINT nMsg, WPARAM wParam, LPARAM lParam);
};