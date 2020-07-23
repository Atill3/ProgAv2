#pragma once
#include <Component.h>
#include <Transform.h>
#include <Square.h>

using namespace bart;

class Controler : public Component
{
public:
	virtual ~Controler();
	void Start() override;
	void Update(float deltatime) override;


private:
	bool m_Pressed;
	bart::Transform* m_Transform = nullptr;
	bart::Square* m_Color = nullptr;
	//template<typename C>
		
};

