#include "pch.h"

#include "WindowHandler.hpp"
#include "Log.hpp"

namespace FRMWRK {
	Window* Window::m_WndInstance = nullptr;

	Window::Window(void) 
	: m_InputMgr(nullptr),
	  m_WndHandler(0x0),
	  m_isExit(false),
	  m_isActive(true),
	  m_isMinimized(false),
	  m_isMaximized(false),
	  m_isResize(false) {
		if (!m_WndInstance) {
			m_WndInstance = this;
		} else {
			ERR("Window object was created already!");
		}
	}

	bool Window::Create(const WinDesc& desc) {
		DEBUG("Window Created");
		m_Desc = desc;

		WNDCLASSEXW wnd;

		wnd.cbSize = sizeof(WNDCLASSEXW);
		wnd.style  = CS_HREDRAW | CS_VREDRAW;
		wnd.lpfnWndProc = StaticWndProc;
		wnd.cbClsExtra  = 0x0;
		wnd.cbWndExtra  = 0x0;
		wnd.hInstance   = 0x0;
		wnd.hIcon   = LoadIcon(NULL, IDI_WINLOGO);
		wnd.hIconSm = wnd.hIcon;
		wnd.hCursor = LoadCursor(0x0, IDC_ARROW);
		wnd.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		wnd.lpszMenuName  = NULL;
		wnd.lpszClassName = L"CG";
		wnd.cbSize = sizeof(WNDCLASSEX);

		if (!RegisterClassEx(&wnd)) {
			ERR("Can't registrate the window");
			return false;
		}

		RECT rect = { 0x0, 0x0, m_Desc.Width, m_Desc.Height };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW | WS_VISIBLE, FALSE);

		long lwidth  = rect.right  - rect.left;
		long lheight = rect.bottom - rect.top;

		long lleft = (long)m_Desc.PosX;
		long ltop  = (long)m_Desc.PosY;

		m_WndHandler = CreateWindowEx(NULL, L"CG", m_Desc.Caption.c_str(), WS_OVERLAPPEDWINDOW | WS_VISIBLE, lleft, ltop, lwidth, lheight, NULL, NULL, NULL, NULL);

		if (!m_WndHandler) {
			ERR("Can't create the window");
			return false;
		}

		ShowWindow(m_WndHandler, SW_SHOW);
		UpdateWindow(m_WndHandler);

		return true;
	}

	void Window::RunEvent(void) {
		MSG msg;			// события окна	

		// просматриваем все поступившие события
		while (PeekMessage(&msg, 0x0, 0x0, 0x0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	void Window::Close(void) {
		if (m_WndHandler) {
			DestroyWindow(m_WndHandler);
		}
		m_WndHandler = nullptr;

		DEBUG("Window Closed");
	}

	LRESULT Window::WndProc(HWND hwnd, UINT nMsg, WPARAM wParam, LPARAM lParam) {
		switch (nMsg) {
			case WM_CREATE:
				return 0x0;
			case WM_CLOSE:
				m_isExit = true;
				return 0x0;
			case WM_ACTIVATE:
				if (LOWORD(wParam) != WA_INACTIVE) {
					m_isActive = true;
				} else {
					m_isActive = false;
				}
					
				return 0x0;
			case WM_MOVE:
				m_Desc.PosX = LOWORD(lParam);
				m_Desc.PosY = HIWORD(lParam);
				m_UpdateWindowState();

				return 0x0;
			case WM_SIZE:
				if (!m_Desc.isResizing) {
					return 0x0;
				}

				m_Desc.Width = LOWORD(lParam);
				m_Desc.Height = HIWORD(lParam);
				m_isResize = true;

				if (wParam == SIZE_MINIMIZED) {
					m_isActive = false;
					m_isMinimized = true;
					m_isMaximized = false;
				} else if (wParam == SIZE_MAXIMIZED) {
					m_isActive = true;
					m_isMinimized = false;
					m_isMaximized = true;
				} else if (wParam == SIZE_RESTORED) {
					if (m_isMinimized) {
						m_isActive    = true;
						m_isMinimized = false;
					} else if (m_isMaximized) {
						m_isActive    = true;
						m_isMaximized = false;
					}
				}

				m_UpdateWindowState();
				
				return 0x0;
			case WM_MOUSEMOVE: 
			case WM_LBUTTONUP: 
			case WM_LBUTTONDOWN: 
			case WM_MBUTTONUP: 
			case WM_MBUTTONDOWN: 
			case WM_RBUTTONUP: 
			case WM_RBUTTONDOWN: 
			case WM_MOUSEWHEEL: 
			case WM_KEYDOWN: 
			case WM_KEYUP:
				if (m_InputMgr)
					m_InputMgr->Run(nMsg, wParam, lParam);

				return 0x0;
		}

		return DefWindowProcW(hwnd, nMsg, wParam, lParam);
	}

	void Window::SetInputMgr(InputManager* inputmgr) {
		m_InputMgr = inputmgr;
		m_UpdateWindowState();
	}

	void Window::m_UpdateWindowState(void) {
		RECT ClientRect;
		ClientRect.left   = m_Desc.PosX;
		ClientRect.top    = m_Desc.PosY;
		ClientRect.right  = m_Desc.Width;
		ClientRect.bottom = m_Desc.Height;
		
		if (m_InputMgr) {
			m_InputMgr->SetWinRect(ClientRect);
		}
	}

	LRESULT CALLBACK FRMWRK::StaticWndProc(HWND hwnd, UINT nMsg, WPARAM wParam, LPARAM lParam) {
		return Window::Get()->WndProc(hwnd, nMsg, wParam, lParam);
	}
};