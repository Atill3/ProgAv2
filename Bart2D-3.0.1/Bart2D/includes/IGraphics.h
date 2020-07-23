#pragma once

#include <IService.h>
#include <EWindowState.h>
#include <string>

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
		virtual void SetColor(unsigned char r, unsigned char g, unsigned char b) = 0;
		virtual void SetColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a) = 0;
		virtual void SetClearColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a) = 0;
		virtual void DrawRect(float x, float y, float w, float h) = 0;
		virtual void FillRect(float x, float y, float w, float h) = 0;
		virtual void DrawCircle(float x, float y, float r) = 0;
		virtual void DrawPoint(float x, float y) = 0;
		virtual void DrawLine(float x1, float y1, float x2, float y2) = 0;
		virtual void SetWindowState(EWindowState state) = 0;

		virtual size_t LoadTexture(const string& filename) = 0;
		virtual void UnloadTexture(size_t id) = 0;
		virtual void DrawTexture(size_t id, int srcX, int srcY, int srcW, int srcH,
			float dstX, float dstY, float dstW, float dstH,
			float angle, bool hFlip, bool vFlip,
			unsigned char r, unsigned char g, unsigned char b, unsigned char alpha) = 0;
		virtual void GetTextureSize(size_t id, int* widht, int* height) = 0;
	};
}