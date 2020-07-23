#pragma once

#include <IGraphics.h>
#include <ITimer.h>
#include <IInput.h>
#include <ILog.h>
#include <IScene.h>
#include <cassert>
#include <string>
#include <IRandom.h>
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
		ILog& ILogger() const { return *m_LogService; }
		IScene& Scene() const { return *m_SceneService; }
		IRandom& Random() const { return *m_RandomService; }

	private:
		


		Engine() = default;
		~Engine() = default;

		void Destroy();
		void ProcessInput();
		void Update(float deltatime);
		void Render();

		bool m_IsInitialized = false;
		bool m_IsRunning = false;

		IGraphics* m_GraphicService = nullptr;
		ITimer* m_TimerService = nullptr;
		IInput* m_InputService = nullptr;
		ILog* m_LogService = nullptr;
		IScene* m_SceneService = nullptr;
		IRandom* m_RandomService = nullptr;

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
			S* service = new S();
			assert(service);

			const bool result = service->Initialize();
			assert(result);

			return service;
		}
	};
}
