#include "window.h"

int APIENTRY WinMain(HINSTANCE hInstance,
HINSTANCE hPrevInstance,
LPSTR     lpCmdLine,
int       nCmdShow)
{
	Window window(800, 600, "IT WORKS!");

	while (window.IsRunning())
	{
		window.Update();
	}
	return window.GetResult();
}