#pragma once

#include "pch.h"
#include "Log.hpp"
#include "IRender.hpp"
#include "WindowHandler.hpp"

namespace FRMWRK {
	class Framework {
	protected:
		bool CalculateFrame(void);

		Window*       m_WndInst;
		IRender*      m_Render;
		InputManager* m_InputMgr;
		Log	          m_Log;

		bool          m_isInit;
	public:
		Framework(void);
		
		bool Init(void);
		void Run(void);
		void Close(void);

		void SetRender(IRender* render);
		void AddInputListener(InputListener* listener);

		~Framework(void);
	};
};