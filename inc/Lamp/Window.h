#pragma once
#include <string>
#include "Lamp_Interface.h"
#include <windows.h>
#include "EventBus.h"
#include "util.h"

namespace Lamp
{
	class WindowSizeChangedEvent : public IEvent
	{
	public:
		WindowSizeChangedEvent(int width, int height, bool minimized)
			: m_Width(width)
			, m_Height(height)
			, m_Minimized(minimized)
		{
		}
		~WindowSizeChangedEvent() override = default;
		static const EventID ID = LampEventID::WindowSizeChanged;
		EventID GetID() const override { return ID; }
		const int m_Width;;
		const int m_Height;
		const bool m_Minimized;

	private:
		NO_MOVE_COPY(WindowSizeChangedEvent)
	};

	class Window
	{
	public:
		LAMP_API Window(const std::string& windowName, HINSTANCE hInst);
		LAMP_API ~Window();

		LAMP_API bool ProcessMessages();
		HWND GetHWnd() const { return m_HWnd; }
		int GetWidth() const { return m_Width; }
		int GetHeight() const { return m_Height; }

	private:
		NO_MOVE_COPY(Window)

		static LRESULT WINAPI StaticWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		LRESULT CALLBACK WndProc(UINT, WPARAM, LPARAM);

		HWND m_HWnd;
		int m_Width;
		int m_Height;
	};
}
