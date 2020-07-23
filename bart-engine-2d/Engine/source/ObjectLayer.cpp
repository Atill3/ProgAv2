#include <ObjectLayer.h>
#include <Engine.h>
#include <Properties.h>
#include <string>
#include <sstream>
#include <tinyxml.h>

bool ObjectLayer::Load(XMLNode* nodePtr)
{
	if (Layer::Load(nodePtr))
	{
		Engine::Get().Scene().AddLayer(m_Name);
		XMLElement* tLayerElement = nodePtr->ToElement();

		///
		/// The width of the layer in tiles. Always the same as the map width
		/// for fixed-size maps.
		///
		m_Width = tLayerElement->IntAttribute("width");

		///
		/// The height of the layer in tiles. Always the same as the map height
		/// for fixed-size maps.
		///
		m_Height = tLayerElement->IntAttribute("height");

		///
		/// Whether the objects are drawn according to the order of appearance
		/// ("index") or sorted by their y-coordinate ("topdown"). Defaults
		/// to "topdown".
		///
		const char* tDrawOrderPtr = tLayerElement->Attribute("draworder");
		m_DrawOrder = ParseDrawOrder(tDrawOrderPtr);

		///
		/// The color used to display the objects in this group.
		///
		const char* tColorPtr = tLayerElement->Attribute("color");
		m_Color = ParseColor(tColorPtr);

		///
		/// Can contain: <properties>, <object>
		///
		LoadObjects(nodePtr);

		return true;
	}

	return false;
}

void ObjectLayer::LoadObjects(XMLNode* node) const
{
	XMLNode* tNext = node->FirstChild();
	while (tNext != nullptr)
	{
		std::string tNextValue = tNext->Value();
		if (tNextValue == "object")
		{
			XMLElement* tObjectElement = tNext->ToElement();
			const char* tName = tObjectElement->Attribute("name");
			const char* tType = tObjectElement->Attribute("type");
			const bool visible = tObjectElement->BoolAttribute("visible", true);

			if (tName != nullptr && tType != nullptr)
			{
				std::string nameStr(tName);
				std::string typeStr(tType);

				RectF transform;
				transform.x = tObjectElement->FloatAttribute("x");
				transform.y = tObjectElement->FloatAttribute("y");
				transform.width = tObjectElement->FloatAttribute("width");
				transform.height = tObjectElement->FloatAttribute("height");
				const float tAngle = tObjectElement->FloatAttribute("rotation");

				XMLNode* tParamNode = tNext->FirstChild();
				Properties properties;
				if (tParamNode != nullptr)
				{
					properties.Load(tParamNode);
				}

				Entity* entity = Engine::Get().Scene().CreateEntity(nameStr, tType, m_Name, transform, tAngle, properties);
				entity->SetActive(visible);
				properties.Clear();
			}
		}

		tNext = tNext->NextSibling();
	}
}

void ObjectLayer::Clean()
{
	/// NOTE that for now, all the objects are managed by the Engine and we
	/// don't need to clean the entities here.
}

void ObjectLayer::Draw()
{
	Engine::Get().Scene().RenderLayer(m_Name);
}

ELayerDrawOrder ObjectLayer::ParseDrawOrder(const char* value) const
{
	if (value)
	{
		if (strcmp(value, "orthogonal") == 0)
		{
			return DO_INDEX;
		}
		if (strcmp(value, "isometric") == 0)
		{
			return DO_TOPDOWN;
		}
	}

	return DO_TOPDOWN;
}

Color ObjectLayer::ParseColor(const char* value) const
{
	if (value != nullptr)
	{
		string color(value);
		if (!color.empty())
		{
			std::string tColor = color.substr(1);
			const size_t tColorLen = tColor.size();

			int tIdx = 0;
			int tR, tG, tB, tA;
			std::stringstream tStringStream;

			if (tColorLen == 8)
			{
				tStringStream << std::hex << tColor.substr(tIdx, 2);
				tStringStream >> tA;
				tStringStream.clear();

				tIdx += 2;
			}
			else
			{
				tA = 255;
			}

			tStringStream << std::hex << tColor.substr(tIdx, 2);
			tStringStream >> tR;
			tStringStream.clear();

			tIdx += 2;

			tStringStream << std::hex << tColor.substr(tIdx, 2);
			tStringStream >> tG;
			tStringStream.clear();

			tIdx += 2;

			tStringStream << std::hex << tColor.substr(tIdx, 2);
			tStringStream >> tB;
			tStringStream.clear();

			return {
				static_cast<unsigned char>(tR),
				static_cast<unsigned char>(tG),
				static_cast<unsigned char>(tB),
				static_cast<unsigned char>(tA)
			};
		}
	}

	return {137, 137, 137, 255};
}
