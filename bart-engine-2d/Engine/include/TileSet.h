#pragma once

#include <Tile.h>
#include <string>
#include <map>
#include <vector>

namespace tinyxml2
{
	class XMLNode;
}

using namespace tinyxml2;

namespace bart
{
	class Tileset
	{
	public:
		bool Load(XMLNode* nodePtr, const std::string& path);
		void Clean();
		void GetTileSize(float* width, float* height) const;
		Tile* GetTile(int index);
		int GetTileCount() const { return m_TileCount; }

	private:
		void PrepareTileSources(const std::string& filename);

		typedef std::map<int, Tile*> TTileMap;
		TTileMap m_TileSource;
		std::vector<size_t> m_TextureIds;
		int m_FirstGid{0};
		std::string m_Source;
		std::string m_Name;
		float m_TileWidth{0};
		float m_TileHeight{0};
		int m_Spacing{0};
		int m_Margin{0};
		int m_TileCount{0};
		int m_Columns{0};
	};
}
