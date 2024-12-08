#include "Window.h"
#include "utils.h"
#include <locale>
#include "EventBus.h"

namespace Lamp
{
	Window::Window(const std::string& windowName, HINSTANCE hInst)
		: m_HWnd(nullptr)
		  , m_Width(0)
		  , m_Height(0)
	{
		std::wstring className = ConvertStringWstring(windowName);
		className.append(L"Class");

		WNDCLASSEX wc = {};
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = StaticWndProc;
		wc.hInstance = hInst;
		wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
		wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wc.hbrBackground = nullptr;
		wc.lpszClassName = className.c_str();
		wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

		RegisterClassEx(&wc);

		DWORD wndStyle = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
		// we should handle error cases here, for all production ready code

		HWND hwnd = CreateWindowExW(0, wc.lpszClassName, className.c_str(), wndStyle, 0, 0, 1024, 768, nullptr, nullptr,
		                            wc.hInstance, nullptr);

		DEVMODEW devmode = {};
		EnumDisplaySettingsW(nullptr, ENUM_CURRENT_SETTINGS, &devmode);
		m_Width = static_cast<int>(0.7f * devmode.dmPelsWidth);
		m_Height = static_cast<int>(0.7f * devmode.dmPelsHeight);
		int left = (devmode.dmPelsWidth - m_Width) / 2;
		int top = (devmode.dmPelsHeight - m_Height) / 2;

		RECT rc = {};
		SetRect(&rc, left, top, left + m_Width, top + m_Height);
		AdjustWindowRectEx(&rc, wndStyle, false, wndStyle);
		MoveWindow(hwnd, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, 1);
		ShowWindow(m_HWnd, SW_SHOW);
	}

	Window::~Window()
	{
	}

	bool Window::ProcessMessages()
	{
		return true;
	}

	LRESULT Window::StaticWndProc(HWND hWnd, UINT msgId, WPARAM wParam, LPARAM lParam)
	{
		Window* parent;
		if (msgId == WM_CREATE)
		{
			parent = static_cast<Window*>((reinterpret_cast<LPCREATESTRUCT>(lParam))->lpCreateParams);
			SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(parent));
		}
		else
		{
			parent = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
			if (!parent)
				return DefWindowProc(hWnd, msgId, wParam, lParam);
		}

		parent->m_HWnd = hWnd;
		return parent->WndProc(msgId, wParam, lParam);
	}

	LRESULT Window::WndProc(UINT msgId, WPARAM wParam, LPARAM lParam)
	{
		// here we do our own shit before returning a lresult
		switch (msgId)
		{
		//Handle window size change
		case WM_SIZE:
			{
				RECT clientRect = {};
				GetClientRect(m_HWnd, &clientRect);
				int width = clientRect.right - clientRect.left > 64l ? clientRect.right - clientRect.left : 64l;
				int height = clientRect.bottom - clientRect.top > 64l ? clientRect.bottom - clientRect.top : 64l;
				EventBus::GetInstance()->Event(
					std::make_shared<WindowSizeChangedEvent>(width, height, wParam == SIZE_MINIMIZED));
				return 0;
			}

		//Handle window closing
		case WM_CLOSE:
			DestroyWindow(m_HWnd); //  Sends us a WM_DESTROY
			return 0;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

		default:
			break;
		}
		return DefWindowProc(m_HWnd, msgId, wParam, lParam);
	}
}
