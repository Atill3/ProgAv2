#include <Layer.h>
#include <tinyxml.h>

bool bart::Layer::Load(XMLNode* nodePtr)
{
	XMLElement* tLayerElement = nodePtr->ToElement();

	///
	/// Unique ID of the layer. Each layer that added to a map gets a unique
	/// id. Even if a layer is deleted, no layer ever gets the same ID. Can
	/// not be changed in Tiled. (since Tiled 1.2)
	///
	m_Id = tLayerElement->IntAttribute("id");

	///
	/// The name of the layer.
	///
	const char* tNamePtr = tLayerElement->Attribute("name");
	if (tNamePtr != nullptr)
	{
		m_Name = tNamePtr;
	}

	///
	/// The x coordinate of the layer in tiles. Defaults to 0 and can not be
	/// changed in Tiled.
	///
	m_X = tLayerElement->IntAttribute("x");

	///
	/// The y coordinate of the layer in tiles. Defaults to 0 and can not be
	/// changed in Tiled.
	///
	m_Y = tLayerElement->IntAttribute("y");

	///
	/// Whether the layer is shown (true) or hidden (false). Defaults to true.
	///
	m_Visible = tLayerElement->BoolAttribute("visible", true);

	///
	/// The opacity of the layer as a value from 0 to 1. Defaults to 1.
	///
	const float tOpacity = tLayerElement->FloatAttribute("opacity", 1.0f);
	m_Color.alpha = static_cast<unsigned char>(255.0f * tOpacity);

	///
	/// Rendering offset for this layer in pixels. Defaults to 0. (since 0.14)
	///
	m_OffsetX = tLayerElement->FloatAttribute("offsetx", 0.0f);

	///
	/// Rendering offset for this layer in pixels. Defaults to 0. (since 0.14)
	///
	m_OffsetY = tLayerElement->FloatAttribute("offsety", 0.0f);

	return true;
}
