#include <Transform.h>

void bart::Transform::Translate(const float x, const float y)
{
	m_Destination.x += x;
	m_Destination.y += y;
}

void bart::Transform::Rotation(const float angle)
{
	this->angle += angle;
}

void bart::Transform::Set(const float x, const float y, const float w, const float h)
{
	m_Destination.x = x;
	m_Destination.y = y;
	m_Destination.width = w;
	m_Destination.height = h;
}

void bart::Transform::Set(const int x, const int y, const int w, const int h)
{
	Set(
		static_cast<float>(x),
		static_cast<float>(y),
		static_cast<float>(w),
		static_cast<float>(h));
}

void bart::Transform::Set(const RectF& destination)
{
	Set(destination.x, destination.y, destination.width, destination.height);
}

void bart::Transform::SetPosition(const float x, const float y)
{
	m_Destination.x = x;
	m_Destination.y = y;
}

void bart::Transform::SetSize(const float width, const float height)
{
	m_Destination.width = width;
	m_Destination.height = height;
}
