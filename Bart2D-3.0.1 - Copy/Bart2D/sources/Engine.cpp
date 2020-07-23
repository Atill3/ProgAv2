#include <Bart2d.h>
#include <Engine.h>
#include <cassert>
#include <EWindowState.h>
#include <SdlGraphics.h>
#include <SdlTimer.h>
#include <SdlInput.h>
#include <SceneService.h>
#include <RandomService.h>

#include <FileLogger.h>
#include <ConsoleLogger.h>

bart::Engine& bart::Engine::Get()
{
	static Engine instance;
	return instance;
}

bool bart::Engine::Initialize()
{

	m_LogService = InitializeService<ConsoleLogger>();
	m_GraphicService = InitializeService<SdlGraphics>();
	const bool result = m_GraphicService->InitWindow("MyGame", 800, 600, WINDOWED);
	m_TimerService = InitializeService<SdlTimer>();
	m_InputService = InitializeService<SdlInput>();
	m_SceneService = InitializeService<SceneService>();	
	m_RandomService = InitializeService<RandomService>();

	m_IsInitialized = true;

	return true;
}

void bart::Engine::Start()
{
	if(m_IsInitialized && !m_IsRunning)
	{

		m_LogService->Log("BartEngine2D Version: " + string(BART_ENGINE_VERSION_STRING));
		m_IsRunning = true;
		float lastTime = m_TimerService->GetTime();
		while(m_IsRunning)
		{
			const float start = m_TimerService->GetTime();

			ProcessInput();
			Update((start - lastTime)* 0.0001f);
			Render();

			m_TimerService->Sleep(start + FRAME_TARGET_TIME - m_TimerService->GetTime());
			lastTime = start;
		}

		Destroy();
	}
}

void bart::Engine::Stop()
{
	m_IsRunning = false;
}

void bart::Engine::Destroy()
{
	DestroyService<IRandom>(m_RandomService);
	DestroyService<IScene>(m_SceneService);
	DestroyService<IInput>(m_InputService);
	DestroyService<ITimer>(m_TimerService);
	DestroyService<IGraphics>(m_GraphicService);
	DestroyService<ILog>(m_LogService);
}

void bart::Engine::ProcessInput()
{
	m_InputService->PoolEvents();
#ifdef _DEBUG
	if (m_InputService->IsKeyDown(EKeys::KEY_ESCAPE)) 
	{
		Stop();
	}

	if (m_InputService->IsKeyDown(EKeys::KEY_F1))
	{
		m_GraphicService->SetWindowState(EWindowState::WINDOWED);
	}	
	if (m_InputService->IsKeyDown(EKeys::KEY_F2))
	{
		m_GraphicService->SetWindowState(EWindowState::BORDERLESS);
	}	
	if (m_InputService->IsKeyDown(EKeys::KEY_F3))
	{
		m_GraphicService->SetWindowState(EWindowState::FULLSCREEN);
	}
#endif
}

void bart::Engine::Update(float deltatime)
{
	m_SceneService->Update(deltatime);
}

void bart::Engine::Render()
{
	m_GraphicService->Clear();
	m_SceneService->Render();
	
	//m_GraphicService->SetColor(255, 0, 0);
	//m_GraphicService->DrawCircle(400.0f, 300.0f, 50.0f);
	//m_GraphicService->SetColor(0, 255, 0);
	//m_GraphicService->DrawRect(10.0f, 10.0f, 50.0f, 50.0f);
	//m_GraphicService->SetColor(0, 0, 255);;
	//m_GraphicService->FillRect(100.0f, 10.0f, 50.0f, 50.0f);
	//m_GraphicService->SetColor(255, 255, 0);;
	//m_GraphicService->DrawLine(0.0f, 0.0f, 800.0f, 600.0f);
	//m_GraphicService->SetColor(255, 255, 0);;
	//m_GraphicService->DrawLine(800.0f, 0.0f, 0.0f, 600.0f);
	m_GraphicService->Present();
}
