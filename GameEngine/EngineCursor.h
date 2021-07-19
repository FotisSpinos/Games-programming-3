#pragma once

#define E_DEFAULT_CURSOR EngineCursor::UseDefailtTexture();
#define E_UNBOUNDED_CURSOR EngineCursor::UseUnboundedCursor();
#define E_INVISIBLE_CURSOR EngineCursor::UseInvisibleCursor();

class EngineCursor
{
public:
	enum Mode
	{
		ABSOLUTE,
		RELATIVE
	};
	EngineCursor() = delete;

	static void SetVisible(bool visible);
	static void SetMode(Mode mode);

	static void UseInvisibleCursor();
	static void UseUnboundedCursor();
	static void UseDefailtTexture();
};