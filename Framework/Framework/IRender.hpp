#pragma once
#include <wtypes.h>

namespace FRMWRK {
	class IRender {
	protected:

	public:
		IRender(void);

		virtual bool Init(HWND hwnd) = 0;
		virtual bool Draw(void)      = 0;
		virtual void Close(void)     = 0;

		virtual ~IRender(void);
	};
};