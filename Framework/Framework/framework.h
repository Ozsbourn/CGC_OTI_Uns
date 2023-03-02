#pragma once

#include <clocale>
#include <ctime>

#include <string>
#include <list>

#define WIN32_LEAN_AND_MEAN             // Исключение редко используемых компонентов из заголовков Windows
#include <Windows.h>

#include <d3d11.h>
//#include <d3dx11.h>					// Устарел

#pragma comment(lib, "d3d11.lib")
//#ifdef _DEBUG
//#	pragma comment(lib, "d3dx11d.lib")
//#else
//#	pragma comment(lib, "d3dx11.lib")
//#endif