#pragma once

#include <Sprite.h>

namespace bart
{
	class Animation final : public Sprite
	{
	public:
		virtual ~Animation() = default;

		void InitAnimation(int frameInRows, int frameWidth, int frameHeight);
		void Play(int start, int count, float delay, bool loop);
		void Stop();
		void Update(float deltaTime) override;
		void Render() override;

	private:
		void UpdateFrame();

		int m_FrameInRowCount = 0;
		int m_FrameWidth = 0;
		int m_FrameHeight = 0;
		int m_FirstFrame = 0;
		int m_LastFrame = 0;
		float m_Delay = 0.0f;
		float m_Elapsed = 0.0f;
		bool m_Playing = false;
		bool m_Loop = false;
		int m_CurrentFrame = 0;
	};
}
