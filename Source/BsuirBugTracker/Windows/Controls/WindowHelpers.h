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