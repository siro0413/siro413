#pragma once
#include "ISubsystem.h"
#define MAX_INPUT_KEY 255 //키보드의 최대 입력 수
#define MAX_INPUT_MOUSE 8 //마우스의 최대 입력 수

enum class KeyCode : unsigned long //가상키 코드 (Virtual-Key Code)
{
    CLICK_LEFT = 0x00,		//마우스 좌클릭
    CLICK_RIGHT = 0x01,		//마우스 우클릭

    KEY_0 = 0x30,
    KEY_1 = 0x31,
    KEY_2 = 0x32,
    KEY_3 = 0x33,
    KEY_4 = 0x34,
    KEY_5 = 0x35,
    KEY_6 = 0x36,
    KEY_7 = 0x37,
    KEY_8 = 0x38,
    KEY_9 = 0x39,
    KEY_A = 0x41,
    KEY_B = 0x42,
    KEY_C = 0x43,
    KEY_D = 0x44,
    KEY_E = 0x45,
    KEY_F = 0x46,
    KEY_G = 0x47,
    KEY_H = 0x48,
    KEY_I = 0x49,
    KEY_J = 0x4A,
    KEY_K = 0x4B,
    KEY_L = 0x4C,
    KEY_M = 0x4D,
    KEY_N = 0x4E,
    KEY_O = 0x4F,
    KEY_P = 0x50,
    KEY_Q = 0x51,
    KEY_R = 0x52,
    KEY_S = 0x53,
    KEY_T = 0x54,
    KEY_U = 0x55,
    KEY_V = 0x56,
    KEY_W = 0x57,
    KEY_X = 0x58,
    KEY_Y = 0x59,
    KEY_Z = 0x5A,
    KEY_SHIFT = 0x10,
    KEY_CONTROL = 0x11,
};

class Input final : public ISubsystem
{
public:
    static std::function<LRESULT(HWND, const uint&, const WPARAM&, const LPARAM&)> MouseProc;

public:
    Input(class Context* context);
    ~Input() = default;

	const D3DXVECTOR2& GetMousePosition() const { return mousePosition; }
	const D3DXVECTOR3& GetMouseMoveValue() const{ return wheelMoveValue; }	//마우스의 이동값

    LRESULT MsgProc(HWND handle, const uint& message, const WPARAM& wParam, const LPARAM& lParam);
	//초기화 함수
    const bool Initialize() override;
	//업데이트 함수
    void Update();

	const bool BtnDown(const KeyCode& button) const { return buttonMap[static_cast<unsigned long>(button)] == static_cast<uint>(ButtonStatus::BUTTON_INPUT_STATUS_DOWN); }
	const bool BtnUp(const KeyCode& button) const { return buttonMap[static_cast<unsigned long>(button)] == static_cast<uint>(ButtonStatus::BUTTON_INPUT_STATUS_UP); }
	const bool BtnPress(const KeyCode& button) const { return buttonMap[static_cast<unsigned long>(button)] == static_cast<uint>(ButtonStatus::BUTTON_INPUT_STATUS_PRESS); }

	const bool KeyDown(const KeyCode& key) const { return keyMap[static_cast<unsigned long>(key)] == static_cast<uint>(KeyStatus::KEY_INPUT_STATUS_DOWN); }
	const bool KeyUp(const KeyCode& key) const { return keyMap[static_cast<unsigned long>(key)] == static_cast<uint>(KeyStatus::KEY_INPUT_STATUS_UP); }
	const bool KeyPress(const KeyCode& key) const { return keyMap[static_cast<unsigned long>(key)] == static_cast<uint>(KeyStatus::KEY_INPUT_STATUS_PRESS); }
private:
    enum class MouseRotationState //마우스의 움직임
    {
        MOUSE_ROTATION_NONE = 0,
        MOUSE_ROTATION_LEFT, //좌
        MOUSE_ROTATION_RIGHT //우
    };

    enum class ButtonStatus //마우스의 상태
    {
        BUTTON_INPUT_STATUS_NONE = 0,
        BUTTON_INPUT_STATUS_DOWN,	//마우스의 눌림
        BUTTON_INPUT_STATUS_UP,		//마우스의 눌렸다가 해제
        BUTTON_INPUT_STATUS_PRESS,	//마우스를 누른상태
        BUTTON_INPUT_STATUS_DBLCLK	//마우스를 더블클릭
    };

    enum class KeyStatus //키보드의 상태
    {
        KEY_INPUT_STATUS_NONE = 0,
        KEY_INPUT_STATUS_DOWN,		//키보드를 누른상태
        KEY_INPUT_STATUS_UP,		//키보드를 눌렀다 해제상태
        KEY_INPUT_STATUS_PRESS,		//키보드를 누른상태
    };

private:
    byte keyState[MAX_INPUT_KEY];			//키보드의 키의상태
    byte keyOldState[MAX_INPUT_KEY];		//키보드의 전 상태
    byte keyMap[MAX_INPUT_KEY];				//enum keycode
    byte buttonStatus[MAX_INPUT_MOUSE];		//마우스의 키상태
    byte buttonOldStatus[MAX_INPUT_MOUSE];	//마우스의 전 상태
    byte buttonMap[MAX_INPUT_MOUSE];		//enum keycode

    ulong startDblClk[MAX_INPUT_MOUSE];		//더블클릭
    int buttonCount[MAX_INPUT_MOUSE];		//마우스 눌린횟수
    ulong timeDblClk;						//더블클릭누른 간격
    D3DXVECTOR2 mousePosition;					//마우스 위치
    D3DXVECTOR3 wheelStatus;					//마우스 휠 상태
    D3DXVECTOR3 wheelOldStatus;					//마우스 휠 이동 값
    D3DXVECTOR3 wheelMoveValue;
};