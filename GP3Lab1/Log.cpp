#include "Log.h"

static int activeLogs = Log::ValidTypes::ERROR | Log::ValidTypes::TRACE | Log::ValidTypes::WARNING;

void Log::Debug(class LogType logType, const std::string message)
{
	if (!IsActive(logType.GetType()))
		return;
	
	//Print file and line
	std::cout << __FILE__ << ", " << __LINE__ << "): " << " ";

	logType.PrintLogType();
	std::cout << "'" << message << "'";
	std::cout << std::endl;
	logType.Functionality();
}

void Log::PrintLogLine(const std::string& msg, const char* file, int line)
{
	std::cout << file << ", " << line << "): " << msg << " " << std::endl;
}

bool Log::CheckGLError(const char* file, int line)
{
	GLenum err;
	bool errorFound = false;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		std::cout << "GL ERROR(" << file << ", " << line << "): " <<
			glewGetErrorString(err) << std::endl;
		errorFound = true;
	}
	return errorFound;
}

void Log::ActivateLogType(ValidTypes logType, bool activate)
{
	if (activeLogs == NULL)
		activeLogs = 0b0000'0000;

	if (activate)
	{
		activeLogs = activeLogs | logType;
	}
	else
	{
		int notLogType = ~logType;
		activeLogs = notLogType & activeLogs;
	}
}

bool Log::IsActive(const int type)
{
	int activeLogsOrType = activeLogs | type;
	if (activeLogsOrType == activeLogs)
		return true;
	return false;
}

int Log::GetActiveLogs()
{
	return activeLogs;
}