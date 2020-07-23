#pragma once

#include <Services.h>
#include <string>

using namespace std;

namespace bart
{
	class Engine
	{
	public:
		static Engine& Get();

		bool Initialize(const string& configFile);
		void Start(const string& projectFile);
		void Stop();
		IGraphics& Graphics() const { return *m_GraphicService; }
		ITimer& Timer() const { return *m_TimerService; }
		IInput& Input() const { return *m_InputService; }
		ILogger& Logger() const { return *m_LoggingService; }
		IScene& Scene() const { return *m_SceneService; }
		IMaths& Maths() const { return *m_MathService; }

	private:
		Engine() = default;
		~Engine() = default;

		void Destroy();
		void ProcessInput();
		void Update(float deltaTime) const;
		void Render() const;
		bool LoadParameters(const string& filename);
		bool LoadProject(const string& filename);

		bool m_IsInitialized = false;
		bool m_IsRunning = false;
		int m_Width = 800;
		int m_Height = 600;
		bool m_F1Pressed = false;
		bool m_F2Pressed = false;
		bool m_F3Pressed = false;
		bool m_F5Pressed = false;
		IGraphics* m_GraphicService = nullptr;
		ITimer* m_TimerService = nullptr;
		IInput* m_InputService = nullptr;
		ILogger* m_LoggingService = nullptr;
		IScene* m_SceneService = nullptr;
		IMaths* m_MathService = nullptr;
	};
}
