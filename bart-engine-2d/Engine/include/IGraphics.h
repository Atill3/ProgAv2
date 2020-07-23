#pragma once

#include <IService.h>
#include <EWindowState.h>
#include <string>
#include <Color.h>
#include <Rect.h>
#include <Flip.h>

using namespace std;

namespace bart
{
	class IGraphics : public IService
	{
	public:
		virtual ~IGraphics() = default;

		virtual bool InitWindow(const string& title, int w, int h, EWindowState state) = 0;
		virtual void Clear() = 0;
		virtual void Present() = 0;
		virtual void SetClearColor(const Color& color) = 0;
		virtual void DrawRect(float x, float y, float w, float h, const Color& color) = 0;
		virtual void DrawRect(const RectF& rect, const Color& color) = 0;
		virtual void FillRect(float x, float y, float w, float h, const Color& color) = 0;
		virtual void FillRect(const RectF& rect, const Color& color) = 0;
		virtual void DrawCircle(float x, float y, float radius, const Color& color) = 0;
		virtual void DrawPoint(float x, float y, const Color& color) = 0;
		virtual void DrawLine(float x1, float y1, float x2, float y2, const Color& color) = 0;
		virtual void DrawTexture(size_t id, const RectI& src, const RectF& dst, float angle, const Flip& flip, const Color& color) = 0;
		virtual void DrawString(const string& text, size_t fontId, float x, float y, const Color& color) = 0;
		virtual void SetWindowState(EWindowState state) = 0;
		virtual size_t LoadTexture(const string& filename) = 0;
		virtual size_t LoadFont(const string& filename, int fontSize) = 0;
		virtual void GetTextureSize(size_t id, int* width, int* height) = 0;
		virtual void GetTextSize(const string& text, size_t fontId, int* width, int* height) = 0;
		virtual void SetViewport(const RectF& viewport) = 0;
		virtual void SetViewport(float x, float y, float w, float h) = 0;
		virtual void EnableViewport(bool enable) = 0;
		virtual RectF& GetViewport() = 0;
		virtual void GetWindowSize(int* width, int* height) = 0;
	};
}
