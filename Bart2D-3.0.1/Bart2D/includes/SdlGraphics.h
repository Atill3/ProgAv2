#pragma once

#include <IGraphics.h>
#include <map>

struct SDL_Renderer;
struct SDL_Window;
struct SDL_Color;
struct SDL_Texture;

using namespace std;

namespace bart
{
	class SdlGraphics final : public IGraphics
	{
	public:
		virtual ~SdlGraphics() = default;

		bool Initialize() override;
		void Destroy() override;
		bool InitWindow(const string& title, int w, int h, EWindowState state) override;
		void Clear() override;
		void Present() override;
		void SetColor(unsigned char r, unsigned char g, unsigned char b) override;
		void SetColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a) override;
		void SetClearColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a) override;
		void DrawRect(float x, float y, float w, float h) override;
		void FillRect(float x, float y, float w, float h) override;
		void DrawCircle(float x, float y, float r) override;
		void DrawPoint(float x, float y) override;
		void DrawLine(float x1, float y1, float x2, float y2) override;
		void SetWindowState(EWindowState state) override;

		size_t LoadTexture(const string & filename) override;
		void UnloadTexture(size_t id) override;
		void DrawTexture(size_t id, int srcX, int srcY, int srcW, int srcH,
			float dstX, float dstY, float dstW, float dstH,
			float angle, bool hFlip, bool vFlip,
			unsigned char r, unsigned char g, unsigned char b, unsigned char alpha) override;

		void GetTextureSize(size_t id, int * widht, int * height) override;

	private:
		typedef map<size_t, SDL_Texture*> TTextureMap;

		SDL_Renderer* m_Renderer = nullptr;
		SDL_Window* m_Window = nullptr;
		SDL_Color* m_ClearColor = nullptr;
		TTextureMap m_TextureCache;

	};
}