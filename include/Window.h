#pragma once

#include <Windows.h>
#include "DeviceResources.h"

class Window
{
public:
	Window(const int width, const int height, const char* windowName);
	Window(const int width, const int height, const LPCSTR windowName, const char* className);
	void InitDirectX11();
	const HWND& GetHandle() const noexcept { return m_windowHandle; }
	const bool IsRunning() const noexcept { return m_isRunning; }
	void Update();
	const int GetResult() const noexcept { return static_cast<int>(m_msg.lParam); }
	const float GetAspectRatio() const noexcept { return m_dr.GetAspectRatio(); }
	~Window();

private:
	static LRESULT CALLBACK HandleMsgSetup(HWND handle, UINT msg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK HandleMsgThunk(HWND handle, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK HandleMsg(HWND handle, UINT msg, WPARAM wParam, LPARAM lParam);

	HWND m_windowHandle;
	WNDCLASS m_wc;
	LPCSTR m_windowName;
	bool m_isRunning;
	MSG m_msg;
	DeviceResources m_dr; 
};