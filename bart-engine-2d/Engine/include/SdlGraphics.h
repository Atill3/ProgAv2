#pragma once

#include <IGraphics.h>
#include <map>

struct SDL_Renderer;
struct SDL_Window;
struct SDL_Color;
struct SDL_Texture;
typedef struct _TTF_Font TTF_Font;

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
		void SetClearColor(const Color& color) override;
		void DrawRect(float x, float y, float w, float h, const Color& color) override;
		void DrawRect(const RectF& rect, const Color& color) override;
		void FillRect(float x, float y, float w, float h, const Color& color) override;
		void FillRect(const RectF& rect, const Color& color) override;
		void DrawCircle(float x, float y, float radius, const Color& color) override;
		void DrawPoint(float x, float y, const Color& color) override;
		void DrawLine(float x1, float y1, float x2, float y2, const Color& color) override;
		void DrawTexture(size_t id, const RectI& src, const RectF& dst, float angle, const Flip& flip, const Color& color) override;
		void DrawString(const string& text, size_t fontId, float x, float y, const Color& color) override;
		void SetWindowState(EWindowState state) override;
		size_t LoadTexture(const string& filename) override;
		size_t LoadFont(const string& filename, int fontSize) override;
		void GetTextureSize(size_t id, int* width, int* height) override;
		void GetTextSize(const string& text, size_t fontId, int* width, int* height) override;
		void SetViewport(const RectF& viewport) override;
		void SetViewport(float x, float y, float w, float h) override;
		void EnableViewport(bool enable) override;
		RectF& GetViewport() override;
		void GetWindowSize(int* width, int* height) override;

	private:
		typedef map<size_t, SDL_Texture*> TTextureMap;
		typedef map<size_t, TTF_Font*> TFontMap;

		SDL_Renderer* m_Renderer = nullptr;
		SDL_Window* m_Window = nullptr;
		SDL_Color* m_ClearColor = nullptr;
		TTextureMap m_TextureCache;
		TFontMap m_FontCache;
		RectF m_Viewport{0.0f, 0.0f, 0.0f, 0.0f};
		RectF m_SavedViewport{0.0f, 0.0f, 0.0f, 0.0f};
		int m_WindowWidth = 0;
		int m_WindowHeight = 0;
	};
}
