#include "Window.h"


Window::Window(const int width, const int height, const char* windowName)
	: m_windowName{ windowName }, m_msg{}, m_isRunning{ true }
{
	m_wc = { .style = CS_OWNDC, .lpfnWndProc = Window::HandleMsgSetup, .hInstance = nullptr, .lpszClassName = "Winow" };
	RegisterClass(&m_wc);
	m_windowHandle = CreateWindowExA(0, m_wc.lpszClassName, m_windowName, WS_TILEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		width, height, nullptr, nullptr, nullptr, this);


	InitDirectX11();
	ShowWindow(m_windowHandle, SW_SHOWDEFAULT);
}

Window::Window(const int width, const int height, const LPCSTR windowName, const char* className)
	: m_windowName{ windowName }, m_msg{}, m_isRunning{ true }
{
	m_wc = { .style = CS_DBLCLKS, .lpfnWndProc = Window::HandleMsgSetup, .hInstance = nullptr, .lpszClassName = className };
	RegisterClass(&m_wc);
	m_windowHandle = CreateWindowExA(0, m_wc.lpszClassName, m_windowName, WS_TILEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		width, height, nullptr, nullptr, nullptr, this);
	ShowWindow(m_windowHandle, SW_SHOWDEFAULT);
}

void Window::InitDirectX11()
{
	m_dr.CreateDeviceResources(m_windowHandle);
}

void Window::Update()
{

	while (PeekMessage(&m_msg, GetHandle(), 0, 0, PM_REMOVE))
	{
		TranslateMessage(&m_msg);
		DispatchMessage(&m_msg);
		m_dr.Present();
	}
}

Window::~Window()
{
	UnregisterClass(m_wc.lpszClassName, nullptr);
	CloseWindow(m_windowHandle);
}

LRESULT Window::HandleMsgSetup(HWND handle, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_NCCREATE)
	{
		// extract ptr to window class from creation data
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		Window* const window = static_cast<Window*>(pCreate->lpCreateParams);
		// set WinAPI-managed user data to store ptr to window instance
		SetWindowLongPtr(handle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
		// set message proc to normal (non-setup) handler now that setup is finished
		SetWindowLongPtr(handle, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMsgThunk));
		// forward message to window instance handler
		return window->HandleMsg(handle, msg, wParam, lParam);
	}
	return DefWindowProc(handle, msg, wParam, lParam);
}

LRESULT Window::HandleMsgThunk(HWND handle, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// retrieve ptr to window instance
	Window* const window = reinterpret_cast<Window*>(GetWindowLongPtr(handle, GWLP_USERDATA));
	// forward message to window instance handler
	return window->HandleMsg(handle, msg, wParam, lParam);
}

LRESULT Window::HandleMsg(HWND handle, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(2);
		m_isRunning = false;
		break;
	}
	return DefWindowProc(handle, msg, wParam, lParam);
}
