#pragma once

#include <Transform.h>
#include <component.h>

using namespace bart;

class PlayerController : public Component
{
public:
	virtual ~PlayerController();
	void Start() override;
	void Update(float deltatime) override;

private:
	bool Pressed = false;

	float m_Speed = 5;

	void CheckInput();

	Transform* m_Transform = nullptr;
};