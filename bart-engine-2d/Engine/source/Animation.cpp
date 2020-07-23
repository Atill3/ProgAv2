#include <Animation.h>

void bart::Animation::InitAnimation(const int frameInRows, const int frameWidth, const int frameHeight)
{
	m_FrameInRowCount = frameInRows;
	m_FrameWidth = frameWidth;
	m_FrameHeight = frameHeight;
}

void bart::Animation::Play(const int start, const int count, const float delay, const bool loop)
{
	m_CurrentFrame = start;
	m_FirstFrame = start;
	m_LastFrame = start + count - 1;
	m_Delay = delay;
	m_Loop = loop;

	UpdateFrame();
	m_Playing = true;
}

void bart::Animation::Stop()
{
	m_Playing = false;
	m_CurrentFrame = 0;
	m_FirstFrame = 0;
	m_LastFrame = 0;
	m_Delay = 0.0f;
	m_Loop = false;
}

void bart::Animation::Update(const float deltaTime)
{
	Sprite::Update(deltaTime);

	if (m_Playing)
	{
		m_Elapsed += deltaTime;
		if (m_Elapsed >= m_Delay)
		{
			m_Elapsed = 0.0f;
			m_CurrentFrame++;
			if (m_CurrentFrame > m_LastFrame)
			{
				m_CurrentFrame = m_FirstFrame;
				if (!m_Loop)
				{
					m_Playing = false;
				}
			}

			UpdateFrame();
		}
	}
}

void bart::Animation::Render()
{
	if (m_Playing)
	{
		Sprite::Render();
	}
}

void bart::Animation::UpdateFrame()
{
	const int row = m_CurrentFrame / m_FrameInRowCount;
	const int col = m_CurrentFrame - m_FrameInRowCount * row;
	const int x = m_FrameWidth * col;
	const int y = m_FrameHeight * row;
	m_Source.Set(x, y, m_FrameWidth, m_FrameHeight);
}
