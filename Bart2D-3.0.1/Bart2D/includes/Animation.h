#pragma once

#include <Sprite.h>

namespace bart
{
	class Animation final : public Sprite
	{
	public:
		virtual ~Animation() = default;
		void InitAnimation(int rows, int width, int height);
		void Play(int start, int count, float delay, bool loop);
		void Stop();

		void Update(float deltaTime) override;
		void Render() override;

	private:
		void UpdateFrame();

		int m_ImagePerRow = 0;
		int m_ImageWidth = 0;
		int m_ImageHeight = 0;
		int m_FirstFrame = 0;
		int m_LastFrame = 0;
		float m_Delay = 0.0f;
		float m_Elapsed = 0.0f;
		bool m_Playing = false;
		bool m_loop = false;
		int m_CurrentFrame = 0;

	};
}