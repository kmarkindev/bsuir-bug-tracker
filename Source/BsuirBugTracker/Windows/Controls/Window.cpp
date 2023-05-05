#include "Window.h"

DWORD Window::GetDefaultStyles() const
{
	return WS_OVERLAPPEDWINDOW;
}

LRESULT Window::WindowProcedure(HWND InHwnd, UINT UMsg, WPARAM WParam, LPARAM LParam)
{
	switch (UMsg)
	{
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(InHwnd, &ps);
			FillRect(hdc, &ps.rcPaint, reinterpret_cast<HBRUSH>(COLOR_WINDOW+1));
			EndPaint(InHwnd, &ps);

			break;
		}
	}

	return BaseWindow::WindowProcedure(InHwnd, UMsg, WParam, LParam);
}
