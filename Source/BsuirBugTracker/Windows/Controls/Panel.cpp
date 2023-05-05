#include "Panel.h"

DWORD Panel::GetDefaultStyles() const
{
	return WS_CHILD | WS_BORDER;
}

const wchar_t* Panel::GetWindowClassName() const
{
	return L"EMPTY PANEL CLASS";
}

LRESULT Panel::WindowProcedure(HWND InHwnd, UINT UMsg, WPARAM WParam, LPARAM LParam)
{
	switch (UMsg)
	{
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(InHwnd, &ps);
			FillRect(hdc, &ps.rcPaint, reinterpret_cast<HBRUSH>(COLOR_WINDOW));
			EndPaint(InHwnd, &ps);

			break;
		}
	}

	return BaseWindow::WindowProcedure(InHwnd, UMsg, WParam, LParam);
}

void Panel::RegisterWindowClass()
{
	RegisterWindowClassHelper();
}
