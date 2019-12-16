#include <iostream>
#include "pch.h"
#include "Application.h"
#include "Log.h"

int main(int argc, char** argv)
{
	Application* app = Application::GetInstance();
	app->Run();

	// prints memory leaks to the Output -> Debug window
	_CrtDumpMemoryLeaks();
	return 0;
}