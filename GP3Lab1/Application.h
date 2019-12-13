#pragma once

#include "pch.h"
#include "Log.h"
#include "vector"
#include "Entity.h"
#include "Input.h"
#include "Terrain.h"


#define WINDOW_W Application::GetInstance()->GetWindowWidth()
#define WINDOW_H Application::GetInstance()->GetWindowHeight()

#define ASSET_PATH "../assets/"


enum AppState
{
	INITILISING, RUNNING, QUITTING
};

class Camera; //forward declaration

class Application
{
private:
	//private variables
	static Application* m_application;

	SDL_Window* m_window = nullptr;
	SDL_GLContext m_glContext = nullptr;
	int m_windowWidth = 1280;
	int m_windowHeight = 720;
	AppState m_appState = AppState::INITILISING;
	float m_worldDeltaTime = 0.f;
	//private functions
	Application();
	void Init();
	void OpenGlInit();
	void Loop();
	void Quit();
	void GameInit();
	void Update(float deltaTime);
	void CollisionUpdate();
	void Render();
	
	std::shared_ptr<Camera> m_mainCamera = nullptr;
public:
	//public functions
	~Application();
	static Application* GetInstance();
	void Run();

	std::vector<std::shared_ptr<Entity>> m_entities;

	inline int GetWindowHeight() { return m_windowHeight; }
	inline int GetWindowWidth() { return m_windowWidth; }

	std::shared_ptr<Camera> GetCamera() { return m_mainCamera;}
	void SetCamera(std::shared_ptr<Camera> camera);
};

//Sources
/*
https://www.turbosquid.com/FullPreview/Index.cfm/ID/994235
https://www.mapzen.com/blog/tangram-heightmapper/
https://image.online-convert.com/convert-to-bmp/url
https://www.3dgep.com/multi-textured-terrain-in-opengl/#Introduction
https://www.tomdalling.com/blog/modern-opengl/07-more-lighting-ambient-specular-attenuation-gamma/
http://www.lighthouse3d.com/tutorials/glsl-tutorial/uniform-variables/
https://www.turbosquid.com/3d-models/free-max-model-box/503112
https://www.turbosquid.com/FullPreview/Index.cfm/ID/1403146

Crate
https://free3d.com/3d-model/crate-86737.html
https://www.filterforge.com/filters/9546-bump.html
https://pybullet.org/Bullet/phpBB3/viewtopic.php?t=4513
SEARCH THIS METHOD
finite difference method
*/