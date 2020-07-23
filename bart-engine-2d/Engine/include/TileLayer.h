#pragma once

#include <Layer.h>
#include <TileSet.h>
#include <vector>
#include <TileInfo.h>

namespace bart
{
	class TileLayer final : public Layer
	{
	public:
		TileLayer() = default;
		explicit TileLayer(Tileset* tileset) { m_TilesetPtr = tileset; }
		virtual ~TileLayer() = default;
		void ParseTileData(const char* data);
		bool Load(XMLNode* node) override;
		void Clean() override;
		void Draw() override;

	private:
		float Clamp(float value, float min, float max) const;

		typedef std::vector<std::vector<TileInfo*>> TTileMap;
		TTileMap m_LayerData;
		int m_Width{0};
		int m_Height{0};
		Tileset* m_TilesetPtr{nullptr};
	};
}
