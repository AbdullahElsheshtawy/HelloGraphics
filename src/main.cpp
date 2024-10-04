#include "window.h"
#include "DeviceResources.h"
int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
	_In_ int nShowCmd)
{
	Window window(800, 600, "D3D11 INITIALIZATION!");
	DeviceResources dr;
	dr.CreateDeviceResources(window.GetHandle());
	while (window.IsRunning())
	{
		window.Update();
		dr.Present();
	}
	return window.GetResult();
}