#include "pch.h"

#include "Framework.hpp"
#include "Macros.hpp"

namespace FRMWRK {
	Framework::Framework(void) 
	: m_Render(nullptr),
	  m_WndInst(nullptr),
	  m_InputMgr(nullptr),
      m_isInit(false) {}

	bool Framework::Init(void) {
		this->m_WndInst  = new Window();
		this->m_InputMgr = new InputManager();

		if (!this->m_WndInst) {
			ERR("Couldn't allocate the memory for WindowHandler!");
			return false;
		}

		if (!this->m_InputMgr) {
			ERR("Couldn't allocate the memory for InputManager!");
			return false;
		}

		this->m_InputMgr->Init();
		
		WinDesc desc;
		if (!this->m_WndInst->Create(desc)) {
			ERR("Couldn't create the window!");
			return false;
		}

		this->m_WndInst->SetInputMgr(this->m_InputMgr);

		if (!this->m_Render->Init(m_WndInst->GetHWND())) {
			ERR("Couldn't create the Render!");
			return false;
		}

		this->m_isInit = true;
		return true;
	}

	void Framework::Run(void) {
		if (m_isInit) {
			while (this->CalculateFrame()) {}
		}
	}

	void Framework::Close(void) {
		this->m_isInit = false;

		CG_DELETE(this->m_Render);
		CG_CLOSE(this->m_WndInst);
		CG_CLOSE(this->m_InputMgr);
	}

	void Framework::SetRender(IRender* render) {
		this->m_Render = render;
	}

	void Framework::AddInputListener(InputListener* listener) {
		if (m_InputMgr) {
			m_InputMgr->AddListener(listener);
		}
	}

	bool Framework::CalculateFrame(void) {
		this->m_WndInst->RunEvent();

		// Если окно неактивно, то кадр завершается
		if (!this->m_WndInst->IsActive()) {
			return true;
		}

		// Если окно закрыто, то завершаем работу фреймворка
		if (this->m_WndInst->IsExit()) {
			return false;
		}

		// Если у окна изменили размер
		if (this->m_WndInst->IsResize()) {
			//
		}

		if (!this->m_Render->Draw()) {
			return false;
		}

		return true;
	}

	Framework::~Framework(void) {
		
	}
};