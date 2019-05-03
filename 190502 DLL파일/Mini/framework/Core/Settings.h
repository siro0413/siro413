#pragma once

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

    auto GetWidth() const -> const float { return windowSize.x; }
    void SetWidth(const float& width) { this->windowSize.x = width; }

    auto GetHeight() const -> const float { return windowSize.y; }
    void SetHeight(const float& height) { this->windowSize.y = height; }

    auto IsVsync() const -> const bool& { return bVsync; }
    void SetIsVsync(const bool& bVsync) { this->bVsync = bVsync; }

private:
    Settings();
    ~Settings() = default;

private:
    HINSTANCE hInstance;
    HWND handle;
    D3DXVECTOR2 windowSize;
    bool bVsync; 
};
// Vertical Synchronization - ���� ����ȭ
// - Tearing ����
// - ������ CPU, GPU ���� ����
// - ��ǻ�� ������ �������� ȭ�� ����

// - 60�����ӿ��� ���ݸ� �������� �������� ������ ���丷��
// - Input Lag