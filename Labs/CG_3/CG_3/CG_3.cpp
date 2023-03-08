#include <iostream>

#include "CGF.hpp"
#include "InputListener.hpp"

#include "Render.hpp"

using namespace FRMWRK;

int main(int argc, char* argv[]) {
	Framework framework;

	Render* render = new Render();

	framework.SetRender(render);
	framework.Init();

	framework.Run();

	framework.Close();

	return 0x0;
}