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
		std::wstring Caption;	// ��������� ����
		int Width;				// ������ ���������� ����� ����
		int Height;				// ������ ���������� ����� ����
		bool isResizing;
	};

	class Window {
	private:
		void m_UpdateWindowState(void);

		static Window* m_WndInstance;

		WinDesc       m_Desc;	     // �������� ����
		InputManager* m_InputMgr;
		HWND          m_WndHandler;  // ���������� ����	
		bool          m_isExit;		 // ���� ���������� � ������� ������	
		bool          m_isActive;    // ���� �������?
		bool          m_isMinimized;
		bool          m_isMaximized;
		bool          m_isResize;	 // ���� ���� �������� ������
	public:
		Window(void);


		static Window* Get(void) { return m_WndInstance; }


		// ������� ����
		bool Create(const WinDesc& desc);


		// ��������� ������� ����
		void RunEvent(void);


		// ������� ����.
		void Close(void);


		void SetInputMgr(InputManager* imgr);


		HWND GetHWND(void)   const { return m_WndHandler; }
		int  GetLeft(void)   const { return m_Desc.PosX; }
		int  GetTop(void)    const { return m_Desc.PosY; }
		int  GetWidth(void)  const { return m_Desc.Width; }
		int  GetHeight(void) const { return m_Desc.Height; }
		

		// ������� ��������� ����
		const std::wstring& GetCaption(void) const { return m_Desc.Caption; }


		// ��������, ���� �� ��������� � ������
		bool IsExit(void) const   { return m_isExit; }
		// �������� �� ���������� ����
		bool IsActive(void) const { return m_isActive; }


		// �������� �� ��������� ����
		// ��������������: ����� ������ ��������� ���� �� ��������� �������
		bool IsResize(void) {
			bool ret   = m_isResize;
			m_isResize = false;

			return ret;
		}

		// ��������� �������
		LRESULT WndProc(HWND hwnd, UINT nMsg, WPARAM wParam, LPARAM lParam);
	};

	// ��������� �������
	static LRESULT CALLBACK StaticWndProc(HWND hwnd, UINT nMsg, WPARAM wParam, LPARAM lParam);
};