#pragma once
//#pragma comment(lib, "dinput8.lib")
//#pragma comment(lib, "dxguid.lib")
#include <dinput.h>

class InputManager
{
public:
	static InputManager* Instance();
	void Update();
	bool IsKeyDown(int);

private:
	InputManager(void);
	~InputManager(void);

	static InputManager* m_Instance;

	/// INPUTS
	IDirectInput8			*m_pDirectInput;
	IDirectInputDevice8		*m_pKeyboard;
	IDirectInputDevice8		*m_pMouse;

	unsigned char m_KeyboardState[256];
	DIMOUSESTATE m_MouseState;
	int m_MouseX;
	int m_MouseY;

	char m_MouseXString[16];
	char m_MouseYString[16];
};

