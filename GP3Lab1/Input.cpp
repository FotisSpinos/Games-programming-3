#include "pch.h"
#include "Input.h"

Input* Input::m_instance = nullptr;

Input::Input()
{
}

Input* Input::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new Input();
	}
	return m_instance;
}

void Input::SetKey(SDL_Keycode key, bool state)
{
	int index = key;
	if (key >= SDLK_CAPSLOCK)
	{
		index = (key - SDLK_SCANCODE_MASK) + 128;
	}
	if (index < m_curState.keys.size())
	{
		m_curState.keys[index] = state;
	}
}

bool Input::GetKey(SDL_Keycode key)
{
	int index = key;
	if (key >= SDLK_CAPSLOCK)
	{
		index = (key - SDLK_SCANCODE_MASK) + 128;
	}
	if (index < m_curState.keys.size())
	{
		return m_curState.keys[index];
	}
	else return false;
}

bool Input::GetKeyDown(SDL_Keycode key)
{
	int index = key;

	if (key >= SDLK_CAPSLOCK)
	{
		index = (key - SDLK_SCANCODE_MASK) + 128;
	}
	
	return (m_curState.keys[index] == true &&
		m_prevState.keys[index] == false);
}

bool Input::GetKeyUp(SDL_Keycode key)
{
	int index = key;

	if (key >= SDLK_CAPSLOCK)
	{
		index = (key - SDLK_SCANCODE_MASK) + 128;
	}

	return (m_curState.keys[index] == false &&
		m_prevState.keys[index] == true);
}

glm::ivec2 Input::GetMouseDelta()
{
	return m_curState.mousePos - m_prevState.mousePos;
}

void Input::ResetMousePos()
{
	m_curState.mousePos = glm::vec2(0.0f, 0.0f);
}

Input::~Input()
{
	delete m_instance;
}
