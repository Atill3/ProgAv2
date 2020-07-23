#pragma once

#include <Layer.h>
#include <string>
#include <Rect.h>
#include <Flip.h>

namespace tinyxml2
{
	class XMLNode;
}

using namespace tinyxml2;

namespace bart
{
	class ImageLayer final : public Layer
	{
	public:
		explicit ImageLayer(const std::string& path) { m_Path = path; }
		virtual ~ImageLayer() = default;
		bool Load(XMLNode* nodePtr) override;
		void Clean() override;
		void Draw() override;

	private:
		std::string m_Path;
		RectI m_Source{0, 0, 0, 0};
		RectF m_Destination{0.0f, 0.0f, 0.0f, 0.0f};
		size_t m_TextureId{0};
		Flip m_Flip{false, false};
	};
}
