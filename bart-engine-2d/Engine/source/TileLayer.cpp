#include <Bart2d.h>
#include <TileLayer.h>
#include <Engine.h>
#include <sstream>
#include <tinyxml.h>

/// Bits on the far end of the 32-bit global tile ID are used for tile flags
const unsigned FLIPPED_HORIZONTALLY_FLAG = 0x80000000;
const unsigned FLIPPED_VERTICALLY_FLAG = 0x40000000;
const unsigned FLIPPED_DIAGONALLY_FLAG = 0x20000000;

void TileLayer::ParseTileData(const char* data)
{
	std::string tCurrentToken;
	std::istringstream tInput(data);

	int tX = 0;
	int tY = 0;

	m_LayerData.push_back(std::vector<TileInfo*>(m_Width));

	while (std::getline(tInput, tCurrentToken, ','))
	{
		if (!tCurrentToken.empty())
		{
			TileInfo* tInfo = new TileInfo();

			try
			{
				tInfo->Index = std::stoul(tCurrentToken);
				tInfo->HorizontalFlip = tInfo->Index & FLIPPED_HORIZONTALLY_FLAG;
				tInfo->VerticalFlip = tInfo->Index & FLIPPED_VERTICALLY_FLAG;
				tInfo->DiagonalFlip = tInfo->Index & FLIPPED_DIAGONALLY_FLAG;
				tInfo->Index &= ~(FLIPPED_HORIZONTALLY_FLAG | FLIPPED_VERTICALLY_FLAG | FLIPPED_DIAGONALLY_FLAG);
			}
			catch (const std::exception& exp)
			{
				Engine::Get().Logger().LogError("Corrupted map detected " + m_Name);
				Engine::Get().Logger().LogError("Error: " + string(exp.what()));
			}

			m_LayerData[tY][tX] = tInfo;
			tX++;

			if (tX >= m_Width && tY < m_Height - 1)
			{
				tX = 0;
				tY++;

				m_LayerData.push_back(std::vector<TileInfo*>(m_Width));
			}
		}
		else
		{
			Engine::Get().Logger().Log("Invalid map detected " + m_Name);
		}
	}
}

bool TileLayer::Load(XMLNode* node)
{
	if (Layer::Load(node))
	{
		XMLElement* tLayerElement = node->ToElement();

		///
		/// The width of the layer in tiles. Always the same as the map width
		/// for fixed-size maps.
		///
		m_Width = tLayerElement->IntAttribute("width");

		///
		/// The height of the layer in tiles. Always the same as the map
		/// height for fixed-size maps.
		///
		m_Height = tLayerElement->IntAttribute("height");

		///
		/// Can contain: <properties>, <data>
		///
		XMLNode* tNext = node->FirstChild();
		while (tNext != nullptr)
		{
			std::string tNextValue = tNext->Value();
			if (tNextValue == "data")
			{
				XMLElement* tDataElement = tNext->ToElement();
				const char* tEncoding = tDataElement->Attribute("encoding");

				if (tEncoding == nullptr || strcmp(tEncoding, "csv") != 0)
				{
					Engine::Get().Logger().Log("Only CSV encoding is supported\n");
					return false;
				}

				const char* tData = tDataElement->GetText();
				ParseTileData(tData);
			}
			else if (tNextValue == "properties")
			{
				//TODO: Load properties
			}

			tNext = tNext->NextSibling();
		}

		return true;
	}

	return false;
}

void TileLayer::Clean()
{
	for (TTileMap::iterator itr = m_LayerData.begin(); itr != m_LayerData.end(); ++itr)
	{
		for (TileInfo* tInfo : *itr)
		{
			delete tInfo;
		}
	}

	m_LayerData.clear();
}

float TileLayer::Clamp(const float value, const float min, const float max) const
{
	float tValue = value;

	if (tValue < min)
	{
		tValue = min;
	}
	else if (tValue > max)
	{
		tValue = max;
	}

	return tValue;
}

void TileLayer::Draw()
{
	if (m_Visible)
	{
		float tTileWidth, tTileHeight;
		m_TilesetPtr->GetTileSize(&tTileWidth, &tTileHeight);

		const RectF viewport = Engine::Get().Graphics().GetViewport();
		const int tFromX = static_cast<int>(Clamp(viewport.x / tTileWidth, 0.0f, static_cast<float>(m_Width)));
		const int tFromY = static_cast<int>(Clamp(viewport.y / tTileHeight, 0.0f, static_cast<float>(m_Height)));
		const int tToX = static_cast<int>(Clamp((viewport.x + viewport.width) / tTileWidth, static_cast<float>(tFromX), static_cast<float>(m_Width)));
		const int tToY = static_cast<int>(Clamp((viewport.y + viewport.height) / tTileHeight, static_cast<float>(tFromY), static_cast<float>(m_Height)));

		if (tFromX < tToX && tFromY < tToY)
		{
			IGraphics& tGraphic = Engine::Get().Graphics();
			RectF tDest;
			const size_t tDataSize = m_LayerData.size();

			if (tDataSize > 0)
			{
				for (int y = tFromY; y < tToY; y++)
				{
					const int tY = y * static_cast<int>(tTileHeight);
					for (int x = tFromX; x < tToX; x++)
					{
						tDest.x = x * tTileWidth + m_OffsetX;
						tDest.y = tY + m_OffsetY;

						const int tIndex = m_LayerData[y][x]->Index;
						bool tInvalidTile = false;

						if (tIndex > 0)
						{
							Tile* tTile = m_TilesetPtr->GetTile(tIndex);

							if (tTile != nullptr)
							{
								tDest.width = static_cast<float>(tTile->Bounds.width);
								tDest.height = static_cast<float>(tTile->Bounds.height);

								if (m_LayerData[y][x]->DiagonalFlip)
								{
									if (m_LayerData[y][x]->HorizontalFlip && m_LayerData[y][x]->VerticalFlip)
									{
										tGraphic.DrawTexture(tTile->Texture, tTile->Bounds, tDest, -90.0f, {false, true}, m_Color);
									}
									else if (m_LayerData[y][x]->VerticalFlip)
									{
										tGraphic.DrawTexture(tTile->Texture, tTile->Bounds, tDest, -90.0f, {false, false}, m_Color);
									}
									else if (m_LayerData[y][x]->HorizontalFlip)
									{
										tGraphic.DrawTexture(tTile->Texture, tTile->Bounds, tDest, 90.0f, {false, false}, m_Color);
									}
									else
									{
										tGraphic.DrawTexture(tTile->Texture, tTile->Bounds, tDest, -90.0f, {true, false}, m_Color);
									}
								}
								else
								{
									tGraphic.DrawTexture(tTile->Texture, tTile->Bounds, tDest, 0.0f, {m_LayerData[y][x]->HorizontalFlip, m_LayerData[y][x]->VerticalFlip}, m_Color);
								}
							}
							else
							{
								tInvalidTile = true;
							}
						}
						else if (tIndex < 0)
						{
							tInvalidTile = true;
						}

						if (tInvalidTile)
						{
							/// Unsupported map is a red rectangle in game:
							tGraphic.FillRect(tDest, Color::Red);
						}
					}
				}
			}
		}
	}
}
