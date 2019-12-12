#include "EngineCursor.h"
#include "pch.h"

void EngineCursor::SetVisible(bool visible)
{
	SDL_ShowCursor(SDL_DISABLE);
}

void EngineCursor::SetMode(Mode mode)
{
	if(mode == Mode::RELATIVE)
		SDL_SetRelativeMouseMode(SDL_TRUE);
	else
		SDL_SetRelativeMouseMode(SDL_FALSE);
}

void EngineCursor::UseInvisibleCursor()
{
	SetVisible(false);
	SetMode(EngineCursor::Mode::RELATIVE);
}

void EngineCursor::UseUnboundedCursor()
{
	SetVisible(true);
	SetMode(EngineCursor::Mode::RELATIVE);
}

void EngineCursor::UseDefailtTexture()
{
	SetVisible(true); 
	SetMode(EngineCursor::Mode::ABSOLUTE);
}
