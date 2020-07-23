#pragma once

#include <Transform.h>
#include <component.h>
#include <Animation.h>

using namespace bart;

class HeliControl : public Component
{
public:
	virtual ~HeliControl();
	void Start() override;
	void Update(float deltatime) override;

private:
	float m_Speed = 5;

	void CheckInput();
	void ChangeAnim(int start, int count, float delay, bool loop);
	void CurrentAnim();
	bool hasChangedA = false;
	bool hasChangedD = false;
	bool hasChangedS = false;
	bool hasChangedW = false;

	int m_CurrentStart = 0;
	int m_CurrentCount = 0;
	float m_CurrentDelay = 0;
	bool m_CurrentLoop = 0;

	Transform* m_Transform = nullptr;
	Animation* m_Animation = nullptr;
};