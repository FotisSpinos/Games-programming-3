#pragma once
#include "Common.h"
#include "InputState.h"
#define INPUT Input::GetInstance()

class Input
{
private:
	Input();
	static Input* m_instance;
	InputState m_curState;
	InputState m_prevState;

public:
	static Input* GetInstance();
	void SetKey(SDL_Keycode key, bool state);
	bool GetKey(SDL_Keycode key); 
	bool GetKeyDown(SDL_Keycode key);
	bool GetKeyUp(SDL_Keycode key);
	glm::ivec2 GetMouseDelta();
	glm::ivec2 GetMousePos() { return m_curState.mousePos; }
	void MoveMouse(glm::ivec2 delta) { m_curState.mousePos += delta; }
	void ResetMousePos();

	void SetPrevState() { m_prevState = m_curState; }
	~Input();
};