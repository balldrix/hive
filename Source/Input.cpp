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