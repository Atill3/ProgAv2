#pragma once

#include <cassert>
#include <IGraphics.h>
#include <ITimer.h>
#include <IInput.h>
#include <ILogFile.h>
#include <ILogConsole.h>
#include <IScene.h>
#include <IRandom.h>
#include <IAudio.h>

using namespace std;

namespace bart
{
	class Engine
	{
	public:
		static Engine& Get();

		bool Initialize();
		void Start();
		void Stop();

		IGraphics& Graphics() const { return *m_GraphicService; }
		ITimer& Timer() const { return *m_TimerService; }
		IInput& Input() const { return *m_InputService; }
		ILogFile& LogFile() const { return *m_LogServiceFile; }
		ILogConsole& LogConsole() const { return *m_LogServiceConsole; }
		IScene& Scene() const { return *m_SceneService;  }
		IRandom& Random() const { return *m_RandomService; }
		IAudio& Audio() const { return *m_AudioService; }

	private:
		Engine() = default;
		~Engine() = default;

		void Destroy();
		void ProcessInput();
		void Update(float deltaTime);
		void Render();

		bool m_IsInitialized = false;
		bool m_IsRunning = false;

		IGraphics* m_GraphicService = nullptr;
		ITimer* m_TimerService = nullptr;
		IInput* m_InputService = nullptr;
		ILogFile* m_LogServiceFile = nullptr;
		ILogConsole* m_LogServiceConsole = nullptr;
		IScene* m_SceneService = nullptr;
		IRandom* m_RandomService = nullptr;
		IAudio* m_AudioService = nullptr;
		
		


		template<typename S>
		void DestroyService(S* service)
		{
			if (service != nullptr)
			{
				service->Destroy();
				delete service;
				service = nullptr;
			}
		}

		template<typename S>
		S* InitializeService()
		{
			S* Service = new S();
			assert(Service);

			const bool result = Service->Initialize();
			assert(result);

			return Service;
		}

	};
}
