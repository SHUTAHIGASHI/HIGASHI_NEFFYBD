#include "InputState.h"
#include <EffekseerForDXLib.h>
#include "SoundManager.h"

void InputState::Update()
{
	// 前のフレームのキー状況をコピー
	for (int i = 0; i < _countof(lastKeyState); ++i)
	{
		lastKeyState[i] = keyState[i];
	}
	for (int i = 0; i < _countof(lastKeyMouseState); ++i)
	{
		lastKeyMouseState[i] = keyMouseState[i];
		keyMouseState[i] = GetMouseInput();
	}

	lastPadState = padState;
	padState = GetJoypadInputState(DX_INPUT_PAD1);

	GetHitKeyStateAll(keyState);
}

bool InputState::IsTriggered(InputType type)const
{
	if (type == InputType::all)
	{
		return !(lastPadState) &&
			(padState);
	}
	else if (type == InputType::pause)
	{
		return !lastKeyState[KEY_INPUT_ESCAPE] &&
			keyState[KEY_INPUT_ESCAPE] ||
			!(lastPadState & PAD_INPUT_8) &&
			(padState & PAD_INPUT_8) ||
			!(lastPadState & PAD_INPUT_3) &&
			(padState & PAD_INPUT_3);
	}
	else if (type == InputType::enter)
	{
		return !lastKeyState[KEY_INPUT_RETURN] &&
			keyState[KEY_INPUT_RETURN] ||
			!(lastPadState & PAD_INPUT_2) &&
			(padState & PAD_INPUT_2);
	}
	else if (type == InputType::back)
	{
		return !lastKeyState[KEY_INPUT_ESCAPE] &&
			keyState[KEY_INPUT_ESCAPE] ||
			!(lastPadState & PAD_INPUT_1) &&
			(padState & PAD_INPUT_1);
	}
	else if (type == InputType::right)
	{
		return !lastKeyState[KEY_INPUT_RIGHT] &&
			keyState[KEY_INPUT_RIGHT] ||
			!(lastPadState & PAD_INPUT_RIGHT) &&
			(padState & PAD_INPUT_RIGHT);;
	}
	else if (type == InputType::left)
	{
		return !lastKeyState[KEY_INPUT_LEFT] &&
			keyState[KEY_INPUT_LEFT] ||
			!(lastPadState & PAD_INPUT_LEFT) &&
			(padState & PAD_INPUT_LEFT);
	}
	else if (type == InputType::up)
	{
		return !lastKeyState[KEY_INPUT_UP] &&
			keyState[KEY_INPUT_UP] ||
			!(lastPadState & PAD_INPUT_UP) &&
			(padState & PAD_INPUT_UP);
	}
	else if (type == InputType::down)
	{
		return !lastKeyState[KEY_INPUT_DOWN] &&
			keyState[KEY_INPUT_DOWN] ||
			!(lastPadState & PAD_INPUT_DOWN) &&
			(padState & PAD_INPUT_DOWN);
	}
	else if (type == InputType::boost)
	{
		return !lastKeyState[KEY_INPUT_LSHIFT] &&
			keyState[KEY_INPUT_LSHIFT];
	}
	else if (type == InputType::space)
	{
		return !lastKeyState[KEY_INPUT_SPACE] &&
			keyState[KEY_INPUT_SPACE];
	}

	return false;
}

bool InputState::IsPressed(InputType type)const
{
	if (type == InputType::enter)
	{
		return keyState[KEY_INPUT_RETURN] ||
			(padState & PAD_INPUT_2);
	}
	else if (type == InputType::right)
	{
		return keyState[KEY_INPUT_RIGHT] ||
			keyState[KEY_INPUT_D] ||
			(padState & PAD_INPUT_RIGHT);;
	}
	else if (type == InputType::left)
	{
		return keyState[KEY_INPUT_LEFT] ||
			keyState[KEY_INPUT_A] ||
			(padState & PAD_INPUT_LEFT);
	}
	else if (type == InputType::up)
	{
		return keyState[KEY_INPUT_UP] ||
			keyState[KEY_INPUT_W] ||
			(padState & PAD_INPUT_UP);
	}
	else if (type == InputType::down)
	{
		return keyState[KEY_INPUT_DOWN] ||
			keyState[KEY_INPUT_S] ||
			(padState & PAD_INPUT_DOWN);
	}
	else if (type == InputType::space)
	{
		return keyState[KEY_INPUT_SPACE];
	}
	return false;
}