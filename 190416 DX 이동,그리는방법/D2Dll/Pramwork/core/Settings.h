#pragma once

class Settings final
{
public:
	static Settings& Get()
	{
		static Settings instance;
		return instance;
	}

	auto GetwindowInstance() const ->HINSTANCE { return hInstance; }
	void SetwindowInstance(HINSTANCE hInstance) { this->hInstance = hInstance; }

	auto GetwindowHandle() const ->HWND { return handle; }
	void SetwindowHandle(HWND handle) { this->handle = handle; }

	auto GetWidth() const -> const float { return windowSize.x; }
	void SetWidth(const float& width) { this->windowSize.x = width; }

	auto GetHeight() const -> const float { return windowSize.y; }
	void SetHeight(const float& height) { this->windowSize.y = height; }

private:
	Settings();
	~Settings() = default;


private:
	HINSTANCE hInstance;
	HWND handle;
	D3DXVECTOR2 windowSize; // FLOAT x, y; 2Â÷¿ø ÁÂÇ¥

};

