#include <Bart2d.h>
#include <Transform.h>



void bart::Transform::Translate(float x, float y)
{
	this->x += x;
	this->y += y;
}

void bart::Transform::Rotation(float angle)
{
	this->angle += angle;
}

void bart::Transform::Set(float x, float y, float w, float h)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}
