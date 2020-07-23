#include <Bart2d.h>
#include <Animation.h>

void bart::Animation::InitAnimation(int rows, int width, int height)
{
	m_ImagePerRow = rows;
	m_ImageWidth = width;
	m_ImageHeight = height;
}

void bart::Animation::Play(int start, int count, float delay, bool loop)
{
	m_CurrentFrame = start;
	m_FirstFrame = start;
	m_LastFrame = start + count - 1;
	m_Delay = delay;
	m_loop = loop;

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
	m_loop = false;;
}

void bart::Animation::Update(float deltaTime)
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
				if (!m_loop)
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
	const int row = m_CurrentFrame / m_ImagePerRow;
	const int col = m_CurrentFrame - (m_ImagePerRow * row);
	const int x = m_ImageWidth * col;
	const int y = m_ImageHeight * row;

	m_SourceX = x;
	m_SourceY = y;
	m_SourceW = m_ImageWidth;
	m_SourceH = m_ImageHeight;
}
