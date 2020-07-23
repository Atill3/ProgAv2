#include <Bart2d.h>
#include <TileSet.h>
#include <Engine.h>
#include <tinyxml.h>

bool Tileset::Load(XMLNode* nodePtr, const std::string& path)
{
	XMLDocument tDoc;
	XMLElement* tTileElement = nullptr;
	XMLNode* tImageNode = nodePtr->FirstChild();

	///
	/// The first global tile ID of this tile-set (this global ID maps to the
	/// first tile in this tile-set).
	///
	m_FirstGid = nodePtr->ToElement()->IntAttribute("firstgid");

	///
	/// If this tile-set is stored in an external TSX (Tile Set XML) file, this
	/// attribute refers to that file. That TSX file has the same structure as
	/// the <tileset> element described here. (There is the firstgid attribute
	/// missing and this source attribute is also not there. These two
	/// attributes are kept in the TMX map, since they are map specific.)
	///
	const char* tSourcePtr = nodePtr->ToElement()->Attribute("source");

	if (tImageNode != nullptr)
	{
		tTileElement = nodePtr->ToElement();
	}
	else
	{
		m_Source = tSourcePtr;

		const std::string tFileName = path + m_Source;
		if (tDoc.LoadFile(tFileName.c_str()) == XML_SUCCESS)
		{
			tTileElement = tDoc.FirstChild()->NextSibling()->ToElement();
		}
	}

	if (tTileElement != nullptr)
	{
		///
		/// The name of this tile-set.
		///
		const char* tNamePtr = tTileElement->Attribute("name");
		if (tNamePtr != nullptr)
		{
			m_Name = tNamePtr;
		}

		///
		/// The (maximum) width of the tiles in this tile-set.
		///
		m_TileWidth = tTileElement->FloatAttribute("tilewidth");

		///
		/// The (maximum) height of the tiles in this tile-set.
		///
		m_TileHeight = tTileElement->FloatAttribute("tileheight");

		///
		/// The spacing in pixels between the tiles in this tile-set
		/// (applies to the tile-set image).
		///
		m_Spacing = tTileElement->IntAttribute("spacing");

		///
		/// The margin around the tiles in this tile-set (applies to the
		/// tile-set image).
		///
		m_Margin = tTileElement->IntAttribute("margin");

		///
		/// The number of tiles in this tile-set (since 0.13)
		///
		m_TileCount = tTileElement->IntAttribute("tilecount");

		///
		/// The number of tile columns in the tile-set. For image collection
		/// tile-set it is editable and
		/// is used when displaying the tile-set. (since 0.15)
		///
		m_Columns = tTileElement->IntAttribute("columns");

		///
		/// Can contain: <tileoffset>, <grid> (since 1.0), <properties>,
		/// <image>, <terraintypes>, <tile>, <wangsets> (since 1.1)
		///
		XMLNode* tNext = tTileElement->FirstChild();
		while (tNext != nullptr)
		{
			std::string tNextValue = tNext->Value();
			if (tNextValue == "image")
			{
				XMLElement* tAtlasElement = tNext->ToElement();

				const char* tFilepath = tAtlasElement->Attribute("source");
				if (tFilepath == nullptr)
				{
					Engine::Get().Logger().Log("Cannot load tileset image\n");
					return false;
				}

				PrepareTileSources(path + std::string(tFilepath));
			}
			else if (tNextValue == "tileoffset")
			{
				// TODO: support tile offset
			}
			else if (tNextValue == "grid")
			{
				// TODO: support grid
			}
			else if (tNextValue == "properties")
			{
				// TODO: load properties
			}
			else if (tNextValue == "terraintypes")
			{
				// TODO: load terrain types
			}
			else if (tNextValue == "tile")
			{
				// TODO: load tile
			}
			else if (tNextValue == "wangsets")
			{
				// TODO: load wangsets
			}

			tNext = tNext->NextSibling();
		}

		return true;
	}

	Engine::Get().Logger().LogError("Couldn't load tileset " + m_Name);
	return false;
}

void Tileset::Clean()
{
	for (TTileMap::iterator i = m_TileSource.begin(); i != m_TileSource.end(); ++i)
	{
		delete i->second;
	}

	m_TileSource.clear();
}

void Tileset::GetTileSize(float* width, float* height) const
{
	*width = m_TileWidth;
	*height = m_TileHeight;
}

Tile* Tileset::GetTile(const int index)
{
	if (m_TileSource.count(index) > 0)
	{
		return m_TileSource[index];
	}

	return nullptr;
}

void Tileset::PrepareTileSources(const std::string& filename)
{
	const size_t id = Engine::Get().Graphics().LoadTexture(filename);
	m_TextureIds.push_back(id);

	int tTileNumber = m_FirstGid;
	int tY = 0;
	int tX = 0;

	for (int i = 0; i < m_TileCount; i++, tTileNumber++)
	{
		tY = i / m_Columns;
		tX = i - tY * m_Columns;

		m_TileSource[tTileNumber] = new Tile();
		m_TileSource[tTileNumber]->Texture = id;
		m_TileSource[tTileNumber]->Bounds = {
			tX * static_cast<int>(m_TileWidth),
			tY * static_cast<int>(m_TileHeight),
			static_cast<int>(m_TileWidth),
			static_cast<int>(m_TileHeight)
		};
	}
}
