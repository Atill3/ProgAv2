#include <Bart2d.h>
#include <TileMap.h>
#include <Engine.h>
#include <TileLayer.h>
#include <ObjectLayer.h>
#include <ImageLayer.h>
#include <string>
#include <sstream>
#include <tinyxml.h>

bool TileMap::Load(const string& filename)
{
	XMLDocument tDocument;
	if (tDocument.LoadFile(filename.c_str()) == XML_SUCCESS)
	{
		m_Filename = filename;

		m_Filepath = "";
		const size_t tIdx = filename.find_last_of("/\\");
		if (tIdx > 0)
		{
			m_Filepath = filename.substr(0, tIdx + 1);
		}

		XMLNode* tNode = tDocument.FirstChild();
		while (tNode != nullptr)
		{
			std::string tNodeValue = tNode->Value();
			if (tNodeValue == "map")
			{
				XMLElement* tMapElement = tNode->ToElement();

				//
				// The TMX format version. Was "1.0" so far, and will be
				// incremented to match minor Tiled releases.
				//
				const char* tVersionPtr = tMapElement->Attribute("version");
				if (tVersionPtr != nullptr)
				{
					m_Version = tVersionPtr;

					if (m_Version != "1.2")
					{
						Engine::Get().Logger().Log("ERROR: Unsupported Tiled version");
					}
				}

				//
				// The Tiled version used to save the file (since Tiled 1.0.1).
				// May be a date (for snapshot builds).
				//
				const char* tTiledVersionPtr = tMapElement->Attribute("tiledversion");
				if (tTiledVersionPtr != nullptr)
				{
					m_TiledVersion = tTiledVersionPtr;
				}

				//
				// Map orientation. Tiled supports “orthogonal”, “isometric”,
				// “staggered” and “hexagonal” (since 0.11). The staggered
				// orientation refers to an isometric map using staggered axes.
				//
				const char* tOrientationPtr = tMapElement->Attribute("orientation");
				m_Orientation = ParseOrientation(tOrientationPtr);

				//
				// The order in which tiles on tile layers are rendered. Valid
				// values are right-down (the default), right-up, left-down and
				// left-up. In all cases, the map is drawn row-by-row. (only
				// supported for orthogonal maps at the moment)
				//
				const char* tRenderOrderPtr = tMapElement->Attribute("renderorder");
				m_RenderOrder = ParseRenderOrder(tRenderOrderPtr);

				//
				// The map width in tiles.
				//
				m_Width = tMapElement->IntAttribute("width", 0);

				//
				// The map height in tiles.
				//
				m_Height = tMapElement->IntAttribute("height", 0);

				//
				// The width of a tile. The tilewidth properties determine the
				// general grid size of the map. The individual tiles may have
				// different sizes. Larger tiles will extend at the top and
				// right (anchored to the bottom left).
				//
				m_Tilewidth = tMapElement->IntAttribute("tilewidth", 0);

				//
				// The height of a tile. The tileheight properties determine
				// the general grid size of the map. The individual tiles may
				// have different sizes. Larger tiles will extend at the top
				// and right (anchored to the bottom left).
				//
				m_Tileheight = tMapElement->IntAttribute("tileheight", 0);

				//
				// Only for hexagonal maps. Determines the width or height
				// (depending on the staggered axis) of the tile’s edge, in
				// pixels.
				//
				m_HexSideLength = tMapElement->IntAttribute("hexsidelength", 0);

				//
				// For staggered and hexagonal maps, determines which axis
				// (“x” or “y”) is staggered. (since 0.11)
				//
				const char* tStaggerAxisPtr = tMapElement->Attribute("staggeraxis");
				m_StaggerAxis = ParseStaggerAxis(tStaggerAxisPtr);

				//
				// For staggered and hexagonal maps, determines whether the
				// “even” or “odd” indexes along the staggered axis are
				// shifted. (since 0.11)
				//
				const char* tStaggerIndexPtr = tMapElement->Attribute("staggerindex");
				m_StaggerIndex = ParseStaggerIndex(tStaggerIndexPtr);

				//
				// The background color of the map. (optional, may include
				// alpha value since 0.15 in the form #AARRGGBB)
				//
				const char* tBackgroundColor = tMapElement->Attribute("backgroundcolor");
				m_BackgroundColor = ParseBgColor(tBackgroundColor);

				//
				// Stores the next available ID for new layers. This number is
				// stored to prevent reuse of the same ID after layers have
				// been removed. (since 1.2)
				//
				m_NextLayerId = tMapElement->IntAttribute("nextlayerid");

				//
				// Stores the next available ID for new objects. This number is
				// stored to prevent reuse of the same ID after objects have
				// been removed. (since 0.11)
				//
				m_NextObjectId = tMapElement->IntAttribute("nextobjectid");

				//
				// Can contain: <properties>, <tileset>, <layer>,
				// <objectgroup>, <imagelayer>, <group> (since 1.0)
				//
				XMLNode* tMapChild = tNode->FirstChild();
				while (tMapChild != nullptr)
				{
					std::string tChildValue = tMapChild->Value();
					if (tChildValue == "properties")
					{
						// TODO: load map properties
					}
					else if (tChildValue == "tileset")
					{
						m_TileSet.Load(tMapChild, m_Filepath);
					}
					else if (tChildValue == "layer")
					{
						TileLayer* tTileLayer = new TileLayer(&m_TileSet);
						if (tTileLayer && tTileLayer->Load(tMapChild))
						{
							string tName = tTileLayer->GetName();
							if (m_layers.count(tName) == 0)
							{
								m_layers[tName] = tTileLayer;
								m_layerDepth.push_back(tTileLayer);
							}
						}
					}
					else if (tChildValue == "objectgroup")
					{
						// TODO: set factory to object layer
						ObjectLayer* tObjectLayer = new ObjectLayer();
						if (tObjectLayer && tObjectLayer->Load(tMapChild))
						{
							string tName = tObjectLayer->GetName();
							if (m_layers.count(tName) == 0)
							{
								m_layers[tName] = tObjectLayer;
								m_layerDepth.push_back(tObjectLayer);
							}
						}
					}
					else if (tChildValue == "imagelayer")
					{
						ImageLayer* tImageLayer = new ImageLayer(m_Filepath);
						if (tImageLayer && tImageLayer->Load(tMapChild))
						{
							string tName = tImageLayer->GetName();
							if (m_layers.count(tName) == 0)
							{
								m_layers[tName] = tImageLayer;
								m_layerDepth.push_back(tImageLayer);
							}
						}
					}
					else if (tChildValue == "group")
					{
						// TODO: load groups (what are groups?)
					}
					else
					{
						Engine::Get().Logger().LogWarning("Not supported : " + tChildValue);
					}

					tMapChild = tMapChild->NextSibling();
				}
			}

			tNode = tNode->NextSibling();
		}

		return true;
	}

	Engine::Get().Logger().LogError(string(tDocument.ErrorStr()));
	return false;
}

void TileMap::Clean()
{
	for (TLayerMap::iterator tItr = m_layers.begin(); tItr != m_layers.end(); ++tItr)
	{
		if (tItr->second != nullptr)
		{
			tItr->second->Clean();
			delete tItr->second;
		}
	}

	m_layers.clear();
	m_layerDepth.clear();
	m_TileSet.Clean();
}

void TileMap::Draw()
{
	for (size_t i = 0; i < m_layerDepth.size(); i++)
	{
		m_layerDepth[i]->Draw();
	}
}

MapOrientation TileMap::ParseOrientation(const char* value) const
{
	if (value)
	{
		if (strcmp(value, "orthogonal") == 0)
		{
			return MO_ORTHOGONAL;
		}
		if (strcmp(value, "isometric") == 0)
		{
			return MO_ISOMETRIC;
		}
		if (strcmp(value, "staggered") == 0)
		{
			return MO_STAGGERED;
		}
		if (strcmp(value, "hexagonal") == 0)
		{
			return MO_HEXAGONAL;
		}
	}

	return MO_ORTHOGONAL;
}

MapRenderOrder TileMap::ParseRenderOrder(const char* value) const
{
	if (value)
	{
		if (strcmp(value, "right-down") == 0)
		{
			return RO_RIGHT_DOWN;
		}

		if (strcmp(value, "right-up") == 0)
		{
			return RO_RIGHT_UP;
		}

		if (strcmp(value, "left-down") == 0)
		{
			return RO_LEFT_DOWN;
		}

		if (strcmp(value, "left-up") == 0)
		{
			return RO_LEFT_UP;
		}
	}

	return RO_RIGHT_DOWN;
}

MapStaggerAxis TileMap::ParseStaggerAxis(const char* value) const
{
	if (value)
	{
		if (strcmp(value, "x") == 0)
		{
			return SA_X;
		}
		if (strcmp(value, "y") == 0)
		{
			return SA_X;
		}
		return SA_NONE;
	}

	return SA_NONE;
}

MapStaggerIndex TileMap::ParseStaggerIndex(const char* value) const
{
	if (value)
	{
		if (strcmp(value, "even") == 0)
		{
			return SI_EVEN;
		}
		if (strcmp(value, "odd") == 0)
		{
			return SI_ODD;
		}
		return SI_NONE;
	}

	return SI_NONE;
}

Color TileMap::ParseBgColor(const char* value) const
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
