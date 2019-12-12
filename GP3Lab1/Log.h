#pragma once
#include "pch.h"
#include "math.h"

#ifdef _DEBUG
#define LOG_WARNING(msg) Log::Debug(LogType("Warning Message", Log::ValidTypes::WARNING), msg);
#define LOG_ERROR(msg) Log::Debug(LogType("Error Occured", Log::ValidTypes::ERROR), msg);
#define LOG_DEBUG(msg) Log::Debug(LogType("", Log::ValidTypes::TRACE), msg);

#define GL_ATTEMPT(func) func; \
if(Log::CheckGLError(__FILE__, __LINE__)) __debugbreak()
#define CHECK_GL_ERROR() Log::CheckGLError(__FILE__, __LINE__)
#else //shouldn't really be outputting to console if this is a release build
#define LOG_DEBUG(msg)
#define GL_ATTEMPT(func) func
#define CHECK_GL_ERROR()
#endif

class Log
{
private:
	Log();
public:

	enum ValidTypes
	{
		NONE = 0b0000'0000,
		TRACE = 0b0000'0001,
		WARNING = 0b0000'0010,
		ERROR = 0b0000'0100
	};

	static void ActivateLogType(ValidTypes logType, bool activate);

	static void Debug(class LogType logType, const std::string message);
	static void PrintLogLine(const std::string& msg, const char* file, int line);
	static bool IsActive(const int type);
	static bool CheckGLError(const char* file, int line);
	static int GetActiveLogs();
};

class LogType
{
private:
	const char* logTypeMessage = "";
	Log::ValidTypes type = Log::ValidTypes::NONE;

public:

	LogType(const char* logMessage, Log::ValidTypes type) :
		logTypeMessage(logMessage),
		type(type)
	{
		
	}

	int GetType()
	{
		return this->type;
	}

	void PrintLogType()
	{
		std::cout << logTypeMessage << " ";
	}

	virtual void Functionality() {}// Provide Extra functionality after we display the message, eg, pause application
};