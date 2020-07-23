#pragma once

#include <string>
#include <Color.h>
#include <TileSet.h>
#include <Layer.h>

using namespace std;

namespace bart
{
	enum MapOrientation
	{
		MO_ORTHOGONAL,
		MO_ISOMETRIC,
		MO_STAGGERED,
		MO_HEXAGONAL
	};

	enum MapRenderOrder
	{
		RO_RIGHT_DOWN,
		RO_RIGHT_UP,
		RO_LEFT_DOWN,
		RO_LEFT_UP
	};

	enum MapStaggerAxis
	{
		SA_NONE,
		SA_X,
		SA_Y
	};

	enum MapStaggerIndex
	{
		SI_NONE,
		SI_EVEN,
		SI_ODD
	};

	class TileMap
	{
	public:
		bool Load(const string& filename);
		void Clean();
		void Draw();
		Color& GetBackgroundColor() { return m_BackgroundColor; }
		Tileset* GetTileset() { return &m_TileSet; }

	private:
		typedef std::map<std::string, Layer*> TLayerMap;
		std::map<std::string, Layer*> m_layers;
		std::vector<Layer*> m_layerDepth;

		MapOrientation ParseOrientation(const char* value) const;
		MapRenderOrder ParseRenderOrder(const char* value) const;
		MapStaggerAxis ParseStaggerAxis(const char* value) const;
		MapStaggerIndex ParseStaggerIndex(const char* value) const;
		Color ParseBgColor(const char* value) const;

		string m_Filename;
		string m_Filepath;
		string m_Version;
		string m_TiledVersion;
		MapOrientation m_Orientation{MO_ORTHOGONAL};
		MapRenderOrder m_RenderOrder{RO_RIGHT_DOWN};
		int m_Width{0};
		int m_Height{0};
		int m_Tilewidth{0};
		int m_Tileheight{0};
		int m_HexSideLength{0};
		MapStaggerAxis m_StaggerAxis{SA_NONE};
		MapStaggerIndex m_StaggerIndex{SI_NONE};
		Color m_BackgroundColor{0, 0, 0};
		int m_NextLayerId{0};
		int m_NextObjectId{0};
		Tileset m_TileSet;
	};
}
