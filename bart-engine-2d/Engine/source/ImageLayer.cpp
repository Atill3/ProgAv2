#include <ImageLayer.h>
#include <Engine.h>
#include <tinyxml.h>

bool ImageLayer::Load(XMLNode* nodePtr)
{
	if (nodePtr && Layer::Load(nodePtr))
	{
		///
		/// Can contain: <properties>, <image>
		///
		XMLNode* tNext = nodePtr->FirstChild();
		while (tNext != nullptr)
		{
			std::string tNextValue = tNext->Value();
			if (tNextValue == "image")
			{
				XMLElement* tSourceElement = tNext->ToElement();
				if (tSourceElement != nullptr)
				{
					const char* tSource = tSourceElement->Attribute("source");
					if (tSource != nullptr)
					{
						const std::string tFilename = m_Path + std::string(tSource);
						const int tWidth = tSourceElement->IntAttribute("width");
						const int tHeight = tSourceElement->IntAttribute("height");

						m_Source.Set(0, 0, tWidth, tHeight);
						m_Destination.Set(m_OffsetX, m_OffsetY, static_cast<float>(tWidth), static_cast<float>(tHeight));
						m_TextureId = Engine::Get().Graphics().LoadTexture(tFilename);
					}
				}
			}
			else if (tNextValue == "properties")
			{
				// TODO: Load image layer properties
			}

			tNext = tNext->NextSibling();
		}

		return true;
	}

	return false;
}

void ImageLayer::Clean()
{
}

void ImageLayer::Draw()
{
	if (m_Visible)
	{
		Engine::Get().Graphics().DrawTexture(m_TextureId, m_Source, m_Destination, 0.0f, m_Flip, m_Color);
	}
}
