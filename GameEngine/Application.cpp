#include "Application.h"
#include "Quad.h"
#include "Entity.h"
#include "Mesh.h"
#include "MeshRenderer.h"
#include "CameraComp.h"
#include "Resources.h"
#include "FirstPersonCamera.h"

#include "Physics.h"
#include "BoxShape.h"
#include "RigidBody.h"
#include "HeightMap.h"
#include "VectorHelper.h"
#include "PointLight.h"

#include "SphereShape.h"
#include "CapsuleShape.h"
#include "CylinderShape.h"
#include "ConeShape.h"

#include "BoxPush.h"

#include "DebugMotionComponent.h"

Application* Application::m_application = nullptr;

Application::Application()
{
}

void Application::Init()
{
	//performing initialization
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		LOG_DEBUG(SDL_GetError());
		exit(-1);
	}
	//setting openGL version to 4.2
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	//setting openGL context to core, not compatibility
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
		SDL_GL_CONTEXT_PROFILE_CORE);
	//creating window
	m_window = SDL_CreateWindow("GP3-GAME", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, m_windowWidth, m_windowHeight,
		SDL_WINDOW_OPENGL);
	SDL_CaptureMouse(SDL_TRUE);
	OpenGlInit();
	GameInit();

	//Set bullet's internal tick call back method ref
	Physics::GetInstance()->GetWorld()->setInternalTickCallback(&Physics::PhysicsTickCallBack);
}

void Application::OpenGlInit()
{
	//creating context (our opengl statemachine in which all our GL calls will refer to)
	m_glContext = SDL_GL_CreateContext(m_window);
	CHECK_GL_ERROR();
	SDL_GL_SetSwapInterval(1);
	//initialsing glew (do this after establishing context!)
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		std::cout << "GLEW Error: " << glewGetErrorString(err) << std::endl;
		exit(-1);
	}
	glViewport(0, 0, (GLsizei)m_windowWidth, (GLsizei)m_windowHeight);

	//Smooth shading
	GL_ATTEMPT(glShadeModel(GL_SMOOTH));
	//enable depth testing
	GL_ATTEMPT(glEnable(GL_DEPTH_TEST));
	//set less or equal func for depth testing
	GL_ATTEMPT(glDepthFunc(GL_LEQUAL));
	//enabling blending
	glEnable(GL_BLEND);
	GL_ATTEMPT(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	//turn on back face culling
	GL_ATTEMPT(glEnable(GL_CULL_FACE));
	GL_ATTEMPT(glCullFace(GL_BACK));
	glViewport(0, 0, (GLsizei)m_windowWidth, (GLsizei)m_windowHeight);
}

void Application::GameInit()
{	
	// Use Invisible Cursor
	EngineCursor::UseInvisibleCursor();

	//Loading all resources
	Resources::GetInstance()->AddModel("Crate1.obj");
	Resources::GetInstance()->AddModel("spider.obj");
	Resources::GetInstance()->AddModel("Box.obj");
	Resources::GetInstance()->AddModel("SimpleCube.obj");
	Resources::GetInstance()->AddModel("Suzanne.obj");
	Resources::GetInstance()->AddModel("SimpleSphere.obj");
	Resources::GetInstance()->AddModel("SimpleCylinder.obj");


	Resources::GetInstance()->AddTexture("crate_1 texture.jpg");

	Resources::GetInstance()->AddShader(std::make_shared<ShaderProgram>(std::string(ASSET_PATH) + std::string("simple_VERT.glsl"),
		std::string(ASSET_PATH) + std::string("simple_FRAG.glsl")),	"simple");
	Resources::GetInstance()->AddShader(std::make_shared<ShaderProgram>(std::string(ASSET_PATH) + std::string("light_VERT.glsl"),
		std::string(ASSET_PATH) + std::string("light_FRAG.glsl")), "light");
	Resources::GetInstance()->AddShader(std::make_shared<ShaderProgram>(std::string(ASSET_PATH) + std::string("simpleColor_VERT.glsl"),
		std::string(ASSET_PATH) + std::string("simpleColor_FRAG.glsl")), "simpleColor");

	Resources::GetInstance()->AddHeightMap(std::string("HeightMap.bmp"));	//HeightMap.bmp

	//Create Camera
	std::shared_ptr<Entity> fpsCamera= std::make_shared<Entity>();
	m_entities.push_back(fpsCamera);
	std::shared_ptr<FirstPersonCamera> fpsc = std::make_shared<FirstPersonCamera>(3.0, 0.015f);
	fpsCamera->AddComponent(fpsc);
	fpsCamera->GetTransform()->SetPosition(glm::vec3(0, 0, 10));

	//Load Spider Model
	std::shared_ptr<Entity> spiderEntity = std::make_shared<Entity>();
	m_entities.push_back(spiderEntity);
	spiderEntity->GetTransform()->SetScale(glm::vec3(0.1f, 0.1f, 0.1f));
	spiderEntity->GetTransform()->SetPosition(glm::vec3(-20, 0, -10));

	spiderEntity->AddComponent(
		std::make_shared<MeshRenderer>(
			Resources::GetInstance()->GetModel("spider.obj"),
			Resources::GetInstance()->GetShader("light"),
			Resources::GetInstance()->GetTexture("crate_1 texture.jpg"))
	);
	
	//Creates light 1
	std::shared_ptr<Entity> pointLight1 = std::make_shared<Entity>();
	m_entities.push_back(pointLight1);
	pointLight1->GetTransform()->SetPosition(glm::vec3(50.f, 15.f, 50.0f));

	std::shared_ptr<PointLight> plc = std::make_shared<PointLight>(1.0f, glm::vec3(0.0001f, 0.1f, 0.1f), glm::vec3(0.f, 0.f, 1.0f), glm::vec3(0.0f, 0.5f, 0.0f));
	plc->m_attenuation = 0.001f;
	plc->m_specularExponent = 25.0f;

	pointLight1->AddComponent(plc);

	// Spider model Light 5
	std::shared_ptr<Entity> pointLight5 = std::make_shared<Entity>();
	m_entities.push_back(pointLight5);
	pointLight5->GetTransform()->SetPosition(glm::vec3(-30, 10, -20));

	std::shared_ptr<PointLight> pl5 = std::make_shared<PointLight>(1.0f, glm::vec3(0.0001f, 0.01f, 0.01f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f));
	pl5->m_attenuation = 0.0001f;
	pl5->m_specularExponent = 112.0f;

	pointLight5->AddComponent(pl5);
	
	//Create Terrain
	std::shared_ptr<Terrain> terrainComp = std::make_shared<Terrain>(Resources::GetInstance()->GetHeightMap("HeightMap.bmp"), 1000, 1000);
	terrainComp->SetHeight(10.0f);
	terrainComp->SetResolutionX(10000);
	terrainComp->SetResolutionY(10000);

	std::shared_ptr<Entity> terrainEntity = std::make_shared<Entity>();
	m_entities.push_back(terrainEntity);
	terrainEntity->GetTransform()->SetPosition(glm::vec3(0, 0, -10));
	terrainEntity->AddComponent(terrainComp);

	// Create Debug Move Object
	std::shared_ptr<Entity> motionObject = std::make_shared<Entity>();
	m_entities.push_back(motionObject);
	motionObject->GetTransform()->SetPosition(glm::vec3(-15.f, 5.f, -50.0f));
	motionObject->GetTransform()->SetScale(glm::vec3(2.5f, 2.5f, 2.5f));

	motionObject->AddComponent(
		std::make_shared<MeshRenderer>(
			Resources::GetInstance()->GetModel("Suzanne.obj"),
			Resources::GetInstance()->GetShader("light"),
			Resources::GetInstance()->GetTexture("Box_Texture.jpg"))
	);

	std::shared_ptr<DebugMotionComponent> dmc = std::make_shared<DebugMotionComponent>(0.5f, 0.5f);
	motionObject->AddComponent(dmc);

	//Create ground
	std::shared_ptr <Entity> physicsInstance = std::make_shared<Entity>();
	m_entities.push_back(physicsInstance);
	physicsInstance->AddComponent(
		std::make_shared<MeshRenderer>(
			Resources::GetInstance()->GetModel("Box.obj"),
			Resources::GetInstance()->GetShader("light"),
			Resources::GetInstance()->GetTexture("Box_Texture.jpg"))
	);

	// Init transform and set name
	physicsInstance->GetTransform()->SetPosition(glm::vec3(0, -10.f, -120.f));
	physicsInstance->GetTransform()->SetScale(glm::vec3(100.f, 1.f, 100.f));
	physicsInstance->name = std::string("Collision Ground");

	// Init rig
	auto rig = physicsInstance->AddComponent<RigidBody>();
	rig->Init(new BoxShape(glm::vec3(100.f, 1.f, 100.f)));
	rig ->Get()->setMassProps(0.0f, btVector3());

	// Create physics boxes
	for (int i = 0; i < 50; i++)
	{
		std::shared_ptr <Entity> physicsBox = std::make_shared<Entity>();
		m_entities.push_back(physicsBox);
		physicsBox->AddComponent(
			std::make_shared<MeshRenderer>(
				Resources::GetInstance()->GetModel("Box.obj"),
				Resources::GetInstance()->GetShader("light"),
				Resources::GetInstance()->GetTexture("Box_Texture.jpg"))
		);
		
		// Init transform and set name
		physicsBox->GetTransform()->SetPosition(glm::vec3(0, 15.f * i, -120.f));
		physicsBox->GetTransform()->SetScale(glm::vec3(1.f, 1.f, 1.f));
		physicsBox->name = std::string("box") + std::to_string(i);

		// init RigidBody
		auto rig = physicsBox->AddComponent<RigidBody>();
		rig->Init(new BoxShape(glm::vec3(1.0f, 1.0f, 1.0f)));

		// Add BoxPush component
		physicsBox->AddComponent<BoxPush>();
	}
}

void Application::Loop()
{
	m_appState = AppState::RUNNING;
	auto prevTicks = std::chrono::high_resolution_clock::now();
	SDL_Event event;

	while (m_appState != AppState::QUITTING)
	{
		//poll SDL events
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				m_appState = AppState::QUITTING;
				break;
			case SDL_WINDOWEVENT_CLOSE:
				m_appState = AppState::QUITTING;
				break;
			case SDL_KEYDOWN:
				INPUT->SetKey(event.key.keysym.sym, true);
				break;
			case SDL_KEYUP:
				INPUT->SetKey(event.key.keysym.sym, false);
				break;
			case SDL_MOUSEMOTION:
				INPUT->MoveMouse(glm::ivec2(event.motion.xrel,
					event.motion.yrel));
				break;
			case SDL_MOUSEBUTTONDOWN:
				INPUT->SetKey((int)event.button.button, true);
				break;
			case SDL_MOUSEBUTTONUP:
				INPUT->SetKey((int)event.button.button, false);
				break;
			}
		}

		if (INPUT->GetKeyDown(SDLK_ESCAPE))
			m_appState = AppState::QUITTING;

		auto currentTicks = std::chrono::high_resolution_clock::now();
		float deltaTime = (float)std::chrono::duration_cast<std::chrono::microseconds>(currentTicks - prevTicks).count() / 100000;
		m_worldDeltaTime = deltaTime;
		prevTicks = currentTicks;

		Physics::GetInstance()->Update(deltaTime);
		//update and render all entities
		Update(deltaTime);
		Render();
		CollisionUpdate();
		SDL_GL_SwapWindow(m_window);

		// record current state
		INPUT->SetPrevState();

		//TODO: print delta time using log
		std::string deltaString = std::to_string(deltaTime);

		// Release unsused resources
		Resources::GetInstance()->ReleaseUnusedResources();
	}
}

void Application::Update(float deltaTime)
{
	for (auto& a : m_entities)
	{
		a->OnUpdate(deltaTime);
	}
}
void Application::CollisionUpdate()
{
	for (auto& a : m_entities)
	{
		a->CollisionUpdate();
	}
}

void Application::Render()
{
	//Check if main camera is being set
	if (m_mainCamera == nullptr)
		return;

	/* Clear context */
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_mainCamera->Recalculate();
	for (auto& a : m_entities)
	{
		a->OnRender();
	}
}

void Application::Quit()
{
	//Close SDL
	SDL_GL_DeleteContext(m_glContext);
	SDL_DestroyWindow(m_window);
	SDL_QuitSubSystem(SDL_INIT_EVERYTHING);
	SDL_Quit();

	// Close Physics
	Physics::GetInstance()->Quit();
}

Application::~Application()
{
	delete m_application;
}

Application* Application::GetInstance()
{
	if (m_application == nullptr)
	{
		m_application = new Application();
	}
	return m_application;
}

void Application::Run()
{
	Init();
	Loop();
	Quit();
}

void Application::SetCamera(std::shared_ptr<Camera> camera)
{
	if (camera != nullptr)
	{
		m_mainCamera = camera;
	}
}