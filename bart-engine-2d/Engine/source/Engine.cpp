#include <Bart2d.h>
#include <Engine.h>
#include <Config.h>
#include <cassert>
#include <tinyxml.h>

using namespace tinyxml2;

Engine& Engine::Get()
{
	static Engine instance;
	return instance;
}

bool Engine::Initialize(const string& configFile)
{
#ifdef _DEBUG
	m_LoggingService = IService::Create<ConsoleLogger>();
#else
	m_LoggingService = IService::Create<FileLogger>();
#endif

	m_GraphicService = IService::Create<SdlGraphics>();

	m_SceneService = IService::Create<SceneService>();

	if (LoadParameters(configFile))
	{
		m_TimerService = IService::Create<SdlTimer>();
		m_InputService = IService::Create<SdlInput>();

		m_MathService = IService::Create<MathService>();

		m_IsInitialized = true;
		return true;
	}

	return false;
}

void Engine::Start(const string& projectFile)
{
	if (m_IsInitialized && !m_IsRunning)
	{
		if (LoadProject(projectFile))
		{
			m_LoggingService->Log("BartEngine2d Version " + string(BART_ENGINE_VERSION_STRING));
			m_IsRunning = true;
			float lastTime = m_TimerService->GetTime();

			while (m_IsRunning)
			{
				const float start = m_TimerService->GetTime();

				ProcessInput();
				Update((start - lastTime) * 0.0001f);
				Render();

				m_TimerService->Sleep(start + FRAME_TARGET_TIME - m_TimerService->GetTime());
				lastTime = start;
			}
		}

		Destroy();
	}
}

void Engine::Stop()
{
	m_IsRunning = false;
}

void Engine::Destroy()
{
	IService::Destroy<IMaths>(m_MathService);
	IService::Destroy<IScene>(m_SceneService);
	IService::Destroy<IInput>(m_InputService);
	IService::Destroy<ITimer>(m_TimerService);
	IService::Destroy<IGraphics>(m_GraphicService);
	IService::Destroy<ILogger>(m_LoggingService);
}

void Engine::ProcessInput()
{
	m_InputService->PoolEvents();

	if (m_InputService->IsKeyDown(KEY_ESCAPE))
	{
		Stop();
	}

#ifdef _DEBUG
	if (m_InputService->IsKeyDown(KEY_F1))
	{
		if (!m_F1Pressed)
		{
			m_F1Pressed = true;
			m_GraphicService->SetWindowState(WINDOWED);
		}
	}
	else
	{
		m_F1Pressed = false;
	}

	if (m_InputService->IsKeyDown(KEY_F2))
	{
		if (!m_F2Pressed)
		{
			m_F2Pressed = true;
			m_GraphicService->SetWindowState(BORDERLESS);
		}
	}
	else
	{
		m_F2Pressed = false;
	}

	if (m_InputService->IsKeyDown(KEY_F3))
	{
		if (!m_F3Pressed)
		{
			m_F3Pressed = true;
			m_GraphicService->SetWindowState(FULLSCREEN);
		}
	}
	else
	{
		m_F3Pressed = false;
	}

	if (m_InputService->IsKeyDown(KEY_F5))
	{
		if (!m_F5Pressed)
		{
			m_F5Pressed = true;
			m_SceneService->Reload();
		}
	}
	else
	{
		m_F5Pressed = false;
	}
#endif
}

void Engine::Update(const float deltaTime) const
{
	m_SceneService->Update(deltaTime);
}

void Engine::Render() const
{
	m_GraphicService->Clear();
	m_SceneService->Render();
	m_GraphicService->Present();
}

bool bart::Engine::LoadParameters(const string & filename)
{
	XMLDocument document;
	if (document.LoadFile(filename.c_str()) == XML_SUCCESS)
	{
		XMLNode* settingNode = document.FirstChild();
		if (settingNode)
		{
			XMLElement* settingElement = settingNode->ToElement();
			const string title = settingElement->Attribute("title");
			m_Width = settingElement->IntAttribute("width");
			m_Height = settingElement->IntAttribute("height");

#ifdef _DEBUG
			const bool result = m_GraphicService->InitWindow(title, m_Width, m_Height, WINDOWED);
#else
			const bool result = m_GraphicService->InitWindow(title, m_Width, m_Height, BORDERLESS);
#endif

			assert(result);

			return true;
		}
	}

	m_LoggingService->LogError(string(document.ErrorStr()));
	return false;
}

bool bart::Engine::LoadProject(const string& filename)
{
	XMLDocument document;
	if (document.LoadFile(filename.c_str()) == XML_SUCCESS)
	{
		XMLNode* projectNode = document.FirstChild();
		if (projectNode)
		{
			XMLNode* node = projectNode->FirstChild();
			while (node)
			{
				string nodeValue = node->Value();
				if (nodeValue.compare("prefabs") == 0)
				{
					m_SceneService->RegisterPrefab(node);
				}
				else if (nodeValue.compare("scenes") == 0)
				{
					m_SceneService->RegisterScene(node);
				}

				node = node->NextSibling();
			}
			return true;
		}
	}

	m_LoggingService->LogError(string(document.ErrorStr()));
	return false;
}
