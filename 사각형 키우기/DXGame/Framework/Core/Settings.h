#pragma once
#include "stdafx.h"

class Settings final
{
public:
	static Settings& Get()
	{
		static Settings instance;
		return instance;
	}

	auto GetWindowInstance() const -> HINSTANCE { return hInstance; }
	void SetWindowInstance(HINSTANCE hInstance) { this->hInstance = hInstance; }

	auto GetWindowHandle() const -> HWND { return handle; }
	void SetWindowHandle(HWND handle) { this->handle = handle; }

	auto GetWindowWidth() const -> const float { return windowSize.x; }
	void SetWindowWidth(const float& width) { this->windowSize.x = width; }

	auto GetWindowHeight() const -> const float { return windowSize.y; }
	void SetWindowHeight(const float& height) { this->windowSize.y = height; }

private:
	Settings()
		: hInstance(nullptr),
		handle(nullptr),
		windowSize(0, 0)
	{
		;
	}
	~Settings() = default;

private:
	HINSTANCE hInstance;
	HWND handle;
	D3DXVECTOR2 windowSize;
};