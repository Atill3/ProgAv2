#pragma once

#include <Layer.h>
#include <ELayerDrawOrder.h>
#include <Color.h>

namespace tinyxml2
{
	class XMLNode;
}

using namespace tinyxml2;

namespace bart
{
	class Entity;

	class ObjectLayer final : public Layer
	{
	public:
		virtual ~ObjectLayer() = default;
		bool Load(XMLNode* nodePtr) override;
		void Clean() override;
		void Draw() override;

	private:
		ELayerDrawOrder ParseDrawOrder(const char* value) const;
		Color ParseColor(const char* value) const;
		void LoadObjects(XMLNode* node) const;

		Color m_Color{255, 255, 255};
		int m_Width{0};
		int m_Height{0};
		ELayerDrawOrder m_DrawOrder{DO_TOPDOWN};
	};
}
