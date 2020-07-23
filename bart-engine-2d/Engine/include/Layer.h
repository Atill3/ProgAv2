#pragma once

#include <string>
#include <Color.h>

namespace tinyxml2
{
	class XMLNode;
}

using namespace tinyxml2;

namespace bart
{
	class Layer
	{
	public:
		virtual ~Layer() = default;
		virtual bool Load(XMLNode* nodePtr);
		virtual void Clean() = 0;
		virtual void Draw() = 0;
		std::string GetName() const { return m_Name; }

	protected:
		int m_Id{0};
		std::string m_Name;
		int m_X{0};
		int m_Y{0};
		bool m_Visible{true};
		Color m_Color{255, 255, 255, 255};
		float m_OffsetX{255};
		float m_OffsetY{255};
	};
}
