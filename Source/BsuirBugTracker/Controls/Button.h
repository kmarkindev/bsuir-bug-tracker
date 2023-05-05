#pragma once

#include <Windows.h>
#include <BsuirBugTracker/Types/Types.h>
#include <functional>

class BaseWindow;

struct ButtonInitializeParams
{
	String ButtonText { L"New Button"};
	int X = 0;
	int Y = 0;
	int Width = 150;
	int Height = 100;
	bool InitiallyShown = true;
};

class Button
{
public:

	Button() = default;

	Button(const Button&) = delete;

	Button(Button&& Other) noexcept;

	Button& operator = (const Button&) = delete;

	Button& operator = (Button&& Other) noexcept;

	void InitializeButtonInstance(const BaseWindow& ParentWindow, const ButtonInitializeParams& Params);

	void DestroyButtonInstance();

	void SetOnClickCallback(std::function<void(Button&)> NewCallback);

	void RaiseClickEvent();

	[[nodiscard]] bool IsValid() const;

private:

	HWND Hwnd;

	bool WasInitialized = false;

	std::function<void(Button&)> Callback;

};
