#include <Bart2d.h>
#include <Engine.h>
#include <cassert>
#include <string>
#include <EWindowState.h>
#include <SdlGraphics.h>
#include <SdlTimer.h>
#include <SdlInput.h>
#include <SdlLogFile.h>
#include <SdlLogConsole.h>
#include <SceneService.h>
#include <RandomService.h>
#include <AudioService.h>

bart::Engine& bart::Engine::Get()
{
	static Engine instance;
	return instance;
}

bool bart::Engine::Initialize()
{
	m_LogServiceFile = InitializeService<SdlLogFile>();
	m_LogServiceConsole = InitializeService<SdlLogConsole>();
	m_GraphicService = InitializeService<SdlGraphics>();

#ifdef _DEBUG
	const bool result = m_GraphicService->InitWindow("MyGame", 800, 600, WINDOWED);
	assert(result);
#else
	const bool result = m_GraphicService->InitWindow("MyGame", 800, 600, BORDERLESS);
#endif

	m_TimerService = InitializeService<SdlTimer>();
	m_InputService = InitializeService<SdlInput>();
	m_SceneService = InitializeService<SceneService>();
	m_RandomService = InitializeService<RandomService>();
	m_AudioService = InitializeService<AudioService>();

	m_IsInitialized = true;

	return true;
}

void bart::Engine::Start()
{
	m_LogServiceFile->WriteFile(" Engine Version: " BART_ENGINE_VERSION_STRING);
	m_LogServiceConsole->WriteInConsole(" Engine Version: " BART_ENGINE_VERSION_STRING);
	if (m_IsInitialized && !m_IsRunning)
	{

		m_IsRunning = true;
		float lastTime = m_TimerService->GetTime();
		m_LogServiceFile->WriteFile(" Game is Running");
		m_LogServiceConsole->WriteInConsole(" Game is Running");
		while (m_IsRunning)
		{
			const float start = m_TimerService->GetTime();

			ProcessInput();
			Update((start - lastTime) * 0.0001f);
			Render();

			m_TimerService->Sleep(start + FRAME_TARGET_TIME - m_TimerService->GetTime());
			lastTime = start;
		}

		Destroy();
	}
}

void bart::Engine::Stop()
{
	m_LogServiceFile->WriteFile(" Engine Stopped.");
	m_LogServiceConsole->WriteInConsole(" Engine Stopped.");
	m_IsRunning = false;
	m_LogServiceConsole->CloseConsole();
	m_LogServiceFile->CloseFile();
}

void bart::Engine::Destroy()
{
	DestroyService<IScene>(m_SceneService);
	DestroyService<IInput>(m_InputService);
	DestroyService<IGraphics>(m_GraphicService);
	DestroyService<ILogConsole>(m_LogServiceConsole);
	DestroyService<ILogFile>(m_LogServiceFile);
	DestroyService<ITimer>(m_TimerService);
	DestroyService<IRandom>(m_RandomService);
	DestroyService<IAudio>(m_AudioService);
}

void bart::Engine::ProcessInput()
{
	m_InputService->PoolEvents();


#ifdef  _DEBUG
	if (m_InputService->IsKeyDown(EKeys::KEY_ESCAPE))
	{
		Stop();
	}

	if (m_InputService->IsKeyDown(EKeys::KEY_F1))
	{
		m_LogServiceFile->WriteFile(" Window State: WINDOWED");
		m_LogServiceConsole->WriteInConsole(" Window State: WINDOWED");
		m_GraphicService->SetWindowState(EWindowState::WINDOWED);
	}
	if (m_InputService->IsKeyDown(EKeys::KEY_F2))
	{
		m_LogServiceFile->WriteFile(" Window State: BORDERLESS");
		m_LogServiceConsole->WriteInConsole(" Window State: BORDERLESS");
		m_GraphicService->SetWindowState(EWindowState::BORDERLESS);
	}
	if (m_InputService->IsKeyDown(EKeys::KEY_F3))
	{
		m_LogServiceFile->WriteFile(" Window State: FULLSCREEN");
		m_LogServiceConsole->WriteInConsole(" Window State: FULLSCREEN");
		m_GraphicService->SetWindowState(EWindowState::FULLSCREEN);
	}
#endif

	//TODO input service
}

void bart::Engine::Update(float deltaTime)
{
	
	m_SceneService->Update(deltaTime);
}

void bart::Engine::Render()
{

	//TODO scene service
	m_GraphicService->Clear();
	m_SceneService->Render();
	m_GraphicService->Present();
}
