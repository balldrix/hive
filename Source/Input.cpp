#include "Input.h"

Input::Input() :
m_newLine(true),
m_charIn(0),
m_textIn(""),
m_mouseX(0),
m_mouseY(0),
m_mouseRawX(0),
m_mouseRawY(0),
m_mouseCaptured(false),
m_mouseLButton(false),
m_mouseRButton(false),
m_mouseMButton(false),
m_mouseX1Button(false),
m_mouseX2Button(false)

{
	for (size_t index = 0; index < inputNS::KEYS_ARRAY_LEN; index++)
	{
		m_keysDown[index] = false;
	}

	for (size_t index = 0; index < inputNS::KEYS_ARRAY_LEN; index++)
	{
		m_keysPressed[index] = false;
	}

	for (int index = 0; index < MAX_CONTROLLERS; index++)
	{
		m_controllers[index].vibrateTimeLeft	= 0;
		m_controllers[index].vibrateTimeRight	= 0;
	}
}

Input::~Input()
{
	if (m_mouseCaptured)
	{
		ReleaseCapture();
	}
}

void
Input::Init(HWND hWindow, bool capture)
{
	m_mouseCaptured = capture;

	m_rid[0].usUsagePage = HID_USAGE_PAGE_GENERIC;
	m_rid[0].usUsage = HID_USAGE_GENERIC_MOUSE;
	m_rid[0].dwFlags = RIDEV_INPUTSINK;
	m_rid[0].hwndTarget = hWindow;
	RegisterRawInputDevices(m_rid, 1, sizeof(m_rid[0]));
	if (m_mouseCaptured)
	{
		SetCapture(hWindow);
	}
	ZeroMemory(m_controllers, sizeof(ControllerState) * MAX_CONTROLLERS);
	CheckControllers();
}

void 
Input::KeyDown(WPARAM wParam)
{
	if (wParam < inputNS::KEYS_ARRAY_LEN)
	{
		m_keysDown[wParam]		= true;
		m_keysPressed[wParam]	= true;
	}
}

void
Input::KeyUp(WPARAM wParam)
{
	if (wParam < inputNS::KEYS_ARRAY_LEN)
	{
		m_keysDown[wParam] = false;
	}
}

void
Input::KeyIn(WPARAM wParam)
{
	// if start of new line
	if (m_newLine)
	{
		m_textIn.clear();
		m_newLine = false;
	}

	// key is backspace
	if (wParam == '\b')
	{
		if (m_textIn.length() < 0)
		{
			m_textIn.erase(m_textIn.size() - 1);
		}
	}
	else
	{
		m_textIn += wParam;
		m_charIn = wParam;
	}

	if ((char)wParam == '/r')
	{
		m_newLine = true;
	}
}

bool
Input::IsKeyDown(UCHAR vk) const
{
	if (vk < inputNS::KEYS_ARRAY_LEN)
	{
		return m_keysDown[vk];
	}
	else
	{
		return false;
	}
}

bool				
Input::WasKeyPressed(UCHAR vk) const
{
	if (vk < inputNS::KEYS_ARRAY_LEN)
	{
		return m_keysPressed[vk];
	}
	else
	{
		return false;
	}
}

bool
Input::AnyKeyPressed() const
{
	for (size_t index = 0; index < inputNS::KEYS_ARRAY_LEN; index++)
	{
		if (m_keysPressed[index] == true)
		{
			return true;
		}
	}
	return false;
}

void
Input::ClearKeyPress(UCHAR vk)
{
	if (vk < inputNS::KEYS_ARRAY_LEN)
	{
		m_keysPressed[vk] = false;
	}
}

void
Input::Clear(UCHAR data)
{
	if (data & inputNS::KEYS_DOWN)
	{
		for (size_t index = 0; index < inputNS::KEYS_ARRAY_LEN; index++)
		{
			m_keysDown[index] = false;
		}
	}

	if (data & inputNS::KEYS_PRESSED)
	{
		for (size_t index = 0; index < inputNS::KEYS_ARRAY_LEN; index++)
		{
			m_keysPressed[index] = false;
		}
	}

	if (data & inputNS::MOUSE)
	{
		m_mouseX = 0;
		m_mouseY = 0;
		m_mouseRawX = 0;
		m_mouseRawY = 0;
	}

	if (data & inputNS::TEXT_IN)
	{
		ClearTextIn();
	}
}

void
Input::MouseIn(LPARAM lParam)
{
	m_mouseX = (short)LOWORD(lParam);
	m_mouseY = (short)HIWORD(lParam);
}

void
Input::MouseRawIn(LPARAM lParam)
{
	UINT dwSize = 40;
	static BYTE lpb[40];
	GetRawInputData((HRAWINPUT)lParam, RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER));

	RAWINPUT* raw = (RAWINPUT*)lpb;

	if (raw->header.dwType == RIM_TYPEMOUSE)
	{
		m_mouseRawX = raw->data.mouse.lLastX;
		m_mouseRawY = raw->data.mouse.lLastY;
	}
}

void
Input::SetMouseXButton(WPARAM wParam)
{
	m_mouseX1Button = (wParam & MK_XBUTTON1) ? true : false;
	m_mouseX2Button = (wParam & MK_XBUTTON2) ? true : false;
}

void
Input::CheckControllers()
{
	DWORD result;
	for (DWORD index = 0; index < MAX_CONTROLLERS; index++)
	{
		result = XInputGetState(index, &m_controllers[index].state);

		if (result == ERROR_SUCCESS)
		{
			m_controllers[index].connected = true;
		}
		else
		{
			m_controllers[index].connected = false;
		}
	}
}

void
Input::ReadControllers()
{
	DWORD result;
	for (DWORD index = 0; index < MAX_CONTROLLERS; index++)
	{
		if (m_controllers[index].connected)
		{
			result = XInputGetState(index, &m_controllers[index].state);
			if (result == ERROR_DEVICE_NOT_CONNECTED)
			{
				m_controllers[index].connected = false;
			}
		}
	}
}

const ControllerState*
Input::GetControllerState(UINT n)
{
	if (n > MAX_CONTROLLERS - 1)
	{
		n = MAX_CONTROLLERS - 1;
	}

	return &m_controllers[n];
}

const WORD
Input::GetGamepadButtons(UINT n)
{
	if (n > MAX_CONTROLLERS - 1)
	{
		n = MAX_CONTROLLERS - 1;
	}
	return m_controllers[n].state.Gamepad.wButtons;
}

bool
Input::GetGamepadDpadUp(UINT n)
{
	if (n > MAX_CONTROLLERS - 1)
	{
		n = MAX_CONTROLLERS - 1;
	}
	return bool((m_controllers[n].state.Gamepad.wButtons & GAMEPAD_DPAD_UP)!=0);
}

bool
Input::GetGamepadDpadDown(UINT n)
{
	if (n > MAX_CONTROLLERS - 1)
	{
		n = MAX_CONTROLLERS - 1;
	}
	return bool((m_controllers[n].state.Gamepad.wButtons & GAMEPAD_DPAD_DOWN)!=0);
}

bool
Input::GetGamepadDpadLeft(UINT n)
{
	if (n > MAX_CONTROLLERS - 1)
	{
		n = MAX_CONTROLLERS - 1;
	}
	return bool((m_controllers[n].state.Gamepad.wButtons & GAMEPAD_DPAD_LEFT)!=0);
}

bool
Input::GetGamepadDpadRight(UINT n)
{
	if (n > MAX_CONTROLLERS - 1)
	{
		n = MAX_CONTROLLERS - 1;
	}
	return bool((m_controllers[n].state.Gamepad.wButtons & GAMEPAD_DPAD_RIGHT)!=0);
}

bool
Input::GetGamepadStart(UINT n)
{
	if (n > MAX_CONTROLLERS - 1)
	{
		n = MAX_CONTROLLERS - 1;
	}
	return bool((m_controllers[n].state.Gamepad.wButtons & GAMEPAD_START_BUTTON)!=0);
}

bool
Input::GetGamepadBack(UINT n)
{
	if (n > MAX_CONTROLLERS - 1)
	{
		n = MAX_CONTROLLERS - 1;
	}
	return bool((m_controllers[n].state.Gamepad.wButtons & GAMEPAD_BACK_BUTTON)!=0);
}

bool
Input::GetGamepadLeftThumb(UINT n)
{
	if (n > MAX_CONTROLLERS - 1)
	{
		n = MAX_CONTROLLERS - 1;
	}
	return bool((m_controllers[n].state.Gamepad.wButtons & GAMEPAD_LEFT_THUMB)!=0);
}
bool
Input::GetGamepadRightThumb(UINT n)
{
	if (n > MAX_CONTROLLERS - 1)
	{
		n = MAX_CONTROLLERS - 1;
	}
	return bool((m_controllers[n].state.Gamepad.wButtons & GAMEPAD_RIGHT_THUMB)!=0);
}
bool
Input::GetGamepadLeftShoulder(UINT n)
{
	if (n > MAX_CONTROLLERS - 1)
	{
		n = MAX_CONTROLLERS - 1;
	}
	return bool((m_controllers[n].state.Gamepad.wButtons & GAMEPAD_RIGHT_SHOULDER)!=0);
}
bool
Input::GetGamepadRightShoulder(UINT n)
{
	if (n > MAX_CONTROLLERS - 1)
	{
		n = MAX_CONTROLLERS - 1;
	}
	return bool((m_controllers[n].state.Gamepad.wButtons & GAMEPAD_RIGHT_SHOULDER)!=0);
}
bool
Input::GetGamepadA(UINT n)
{
	if (n > MAX_CONTROLLERS - 1)
	{
		n = MAX_CONTROLLERS - 1;
	}
	return bool((m_controllers[n].state.Gamepad.wButtons & GAMEPAD_A) != 0);
}
bool
Input::GetGamepadB(UINT n)
{
	if (n > MAX_CONTROLLERS - 1)
	{
		n = MAX_CONTROLLERS - 1;
	}
	return bool((m_controllers[n].state.Gamepad.wButtons & GAMEPAD_B) != 0);
}
bool
Input::GetGamepadX(UINT n)
{
	if (n > MAX_CONTROLLERS - 1)
	{
		n = MAX_CONTROLLERS - 1;
	}
	return bool((m_controllers[n].state.Gamepad.wButtons & GAMEPAD_X) != 0);
}
bool
Input::GetGamepadY(UINT n)
{
	if (n > MAX_CONTROLLERS - 1)
	{
		n = MAX_CONTROLLERS - 1;
	}
	return bool((m_controllers[n].state.Gamepad.wButtons & GAMEPAD_Y) != 0);
}

BYTE
Input::GetGamepadLeftTrigger(UINT n)
{
	if (n > MAX_CONTROLLERS - 1)
	{
		n = MAX_CONTROLLERS - 1;
	}
	return m_controllers[n].state.Gamepad.bLeftTrigger;
}

BYTE
Input::GetGamepadRightTrigger(UINT n)
{
	if (n > MAX_CONTROLLERS - 1)
	{
		n = MAX_CONTROLLERS - 1;
	}
	return m_controllers[n].state.Gamepad.bRightTrigger;
}

SHORT
Input::GetGamepadThumbLX(UINT n)
{
	if (n > MAX_CONTROLLERS - 1)
	{
		n = MAX_CONTROLLERS - 1;
	}
	return m_controllers[n].state.Gamepad.sThumbLX;
}

SHORT
Input::GetGamepadThumbLY(UINT n)
{
	if (n > MAX_CONTROLLERS - 1)
	{
		n = MAX_CONTROLLERS - 1;
	}
	return m_controllers[n].state.Gamepad.sThumbLY;
}

SHORT
Input::GetGamepadThumbRX(UINT n)
{
	if (n > MAX_CONTROLLERS - 1)
	{
		n = MAX_CONTROLLERS - 1;
	}
	return m_controllers[n].state.Gamepad.sThumbRX;
}

SHORT
Input::GetGamepadThumbRY(UINT n)
{
	if (n > MAX_CONTROLLERS - 1)
	{
		n = MAX_CONTROLLERS - 1;
	}
	return m_controllers[n].state.Gamepad.sThumbRY;
}

void 
Input::GamepadVibrateLeft(UINT n, WORD speed, float sec)
{
	if (n > MAX_CONTROLLERS - 1)
	{
		n = MAX_CONTROLLERS - 1;
	}
	m_controllers[n].vibration.wLeftMotorSpeed = speed;
	m_controllers[n].vibrateTimeLeft = sec;
}

void
Input::GamepadVibrateRight(UINT n, WORD speed, float sec)
{
	if (n > MAX_CONTROLLERS - 1)
	{
		n = MAX_CONTROLLERS - 1;
	}
	m_controllers[n].vibration.wRightMotorSpeed = speed;
	m_controllers[n].vibrateTimeRight = sec;
}

void
Input::VibrateControllers(float deltaTime)
{
	for (int index = 0; index < MAX_CONTROLLERS; index++)
	{
		if (m_controllers[index].connected)
		{
			m_controllers[index].vibrateTimeLeft -= deltaTime;
			if (m_controllers[index].vibrateTimeLeft < 0)
			{
				m_controllers[index].vibrateTimeLeft = 0;
				m_controllers[index].vibration.wLeftMotorSpeed = 0;
			}

			m_controllers[index].vibrateTimeRight -= deltaTime;
			if (m_controllers[index].vibrateTimeRight < 0)
			{
				m_controllers[index].vibrateTimeRight = 0;
				m_controllers[index].vibration.wRightMotorSpeed = 0;
			}

			XInputSetState(index, &m_controllers[index].vibration);
		}
	}
}
