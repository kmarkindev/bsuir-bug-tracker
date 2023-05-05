#pragma once

#include <Windows.h>
#include <cassert>

class BaseWindow;

inline BaseWindow* GetWindowInstance(HWND Hwnd)
{
	assert(Hwnd != nullptr);

	LONG_PTR Ptr = GetWindowLongPtr(Hwnd, GWLP_USERDATA);

	return reinterpret_cast<class BaseWindow*>(Ptr);
}

inline void SetWindowInstance(HWND Hwnd, BaseWindow* Instance)
{
	assert(Hwnd != nullptr);

	SetWindowLongPtr(Hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(Instance));
}

inline bool WindowHasStyle(HWND Hwnd, DWORD Style)
{
	assert(Hwnd != nullptr);

	LONG_PTR Ptr = GetWindowLongPtr(Hwnd, GWL_STYLE);
	DWORD ExistingStyle = static_cast<DWORD>(Ptr);

	return (ExistingStyle & Style) != 0;
}

inline void WindowSetStyle(HWND Hwnd, DWORD Style, bool bShouldActivate)
{
	assert(Hwnd != nullptr);

	LONG_PTR Ptr = GetWindowLongPtr(Hwnd, GWL_STYLE);
	DWORD ExistingStyle = static_cast<DWORD>(Ptr);

	if(bShouldActivate)
	{
		ExistingStyle |= Style;
	}
	else
	{
		ExistingStyle &= ~Style;
	}

	SetWindowLongPtr(Hwnd, GWL_STYLE, static_cast<LONG_PTR>(ExistingStyle));
	SetWindowPos(Hwnd, nullptr, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
}