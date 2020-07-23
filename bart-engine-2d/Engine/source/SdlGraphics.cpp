#include <Bart2d.h>
#include <SdlGraphics.h>
#include <SDL.h>
#include <Engine.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

SDL_Texture* g_TextureBuffer;

bool SdlGraphics::Initialize()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		Engine::Get().Logger().LogError("Error with SDL");
		return false;
	}

	TTF_Init();

	m_ClearColor = new SDL_Color{61, 61, 61, 255};
	return true;
}

void SdlGraphics::Destroy()
{
	if (m_ClearColor != nullptr)
	{
		delete m_ClearColor;
		m_ClearColor = nullptr;
	}

	SDL_DestroyRenderer(m_Renderer);
	SDL_DestroyWindow(m_Window);

	m_Renderer = nullptr;
	m_Window = nullptr;

	SDL_Quit();
}

bool SdlGraphics::InitWindow(const string& title, const int w, const int h, const EWindowState state)
{
	m_Window = SDL_CreateWindow(
		title.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		w, h, SDL_WINDOW_BORDERLESS);

	if (m_Window == nullptr)
	{
		Engine::Get().Logger().LogError("Error with SDL Window");
		return false;
	}

	m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);

	if (m_Renderer == nullptr)
	{
		Engine::Get().Logger().LogError("Error with SDL Renderer");
		return false;
	}

	if (state == BORDERLESS)
	{
		SDL_SetWindowFullscreen(m_Window, SDL_WINDOW_FULLSCREEN_DESKTOP);
	}
	else if (state == FULLSCREEN)
	{
		SDL_SetWindowFullscreen(m_Window, SDL_WINDOW_FULLSCREEN);
	}

	GetWindowSize(&m_WindowWidth, &m_WindowHeight);
	m_Viewport.Set(0.0f, 0.0f, static_cast<float>(m_WindowWidth), static_cast<float>(m_WindowHeight));
	m_SavedViewport.Set(0.0f, 0.0f, static_cast<float>(m_WindowWidth), static_cast<float>(m_WindowHeight));
	return true;
}

void SdlGraphics::Clear()
{
	SDL_SetRenderDrawColor(
		m_Renderer,
		m_ClearColor->r,
		m_ClearColor->g,
		m_ClearColor->b,
		255);

	SDL_RenderClear(m_Renderer);
	SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);
}

void SdlGraphics::Present()
{
	SDL_RenderPresent(m_Renderer);
}

void SdlGraphics::SetClearColor(const Color& color)
{
	m_ClearColor->r = color.red;
	m_ClearColor->g = color.green;
	m_ClearColor->b = color.blue;
	m_ClearColor->a = color.alpha;
}

void SdlGraphics::DrawRect(const float x, const float y, const float w, const float h, const Color& color)
{
	SDL_Rect rect = {
		static_cast<int>(x - m_Viewport.x),
		static_cast<int>(y - m_Viewport.y),
		static_cast<int>(w),
		static_cast<int>(h)
	};

	SDL_SetRenderDrawColor(m_Renderer, color.red, color.green, color.blue, color.alpha);
	SDL_RenderDrawRect(m_Renderer, &rect);
}

void SdlGraphics::DrawRect(const RectF& rect, const Color& color)
{
	DrawRect(rect.x, rect.y, rect.width, rect.height, color);
}

void SdlGraphics::FillRect(const float x, const float y, const float w, const float h, const Color& color)
{
	SDL_Rect rect = {
		static_cast<int>(x - m_Viewport.x),
		static_cast<int>(y - m_Viewport.y),
		static_cast<int>(w),
		static_cast<int>(h)
	};

	SDL_SetRenderDrawColor(m_Renderer, color.red, color.green, color.blue, color.alpha);
	SDL_RenderFillRect(m_Renderer, &rect);
}

void SdlGraphics::FillRect(const RectF& rect, const Color& color)
{
	FillRect(rect.x, rect.y, rect.width, rect.height, color);
}

void SdlGraphics::DrawCircle(const float x, const float y, const float radius, const Color& color)
{
	float tX = x;
	float tY = y;

	const double inc = 0.01;
	const double circle = 6.63;
	double angle = 0.0;

	while (angle < circle)
	{
		tX = static_cast<float>(x + radius * cos(angle));
		tY = static_cast<float>(y + radius * sin(angle));
		DrawPoint(tX, tY, color);

		angle += inc;
	}
}

void SdlGraphics::DrawPoint(const float x, const float y, const Color& color)
{
	const int tX = static_cast<int>(x - m_Viewport.x);
	const int tY = static_cast<int>(y - m_Viewport.y);
	SDL_SetRenderDrawColor(m_Renderer, color.red, color.green, color.blue, color.alpha);
	SDL_RenderDrawPoint(m_Renderer, tX, tY);
}

void SdlGraphics::DrawLine(const float x1, const float y1, const float x2, const float y2, const Color& color)
{
	const int tX1 = static_cast<int>(x1 - m_Viewport.x);
	const int tY1 = static_cast<int>(y1 - m_Viewport.y);
	const int tX2 = static_cast<int>(x2 - m_Viewport.x);
	const int tY2 = static_cast<int>(y2 - m_Viewport.y);
	SDL_SetRenderDrawColor(m_Renderer, color.red, color.green, color.blue, color.alpha);
	SDL_RenderDrawLine(m_Renderer, tX1, tY1, tX2, tY2);
}

void SdlGraphics::DrawTexture(const size_t id, const RectI& src, const RectF& dst, const float angle, const Flip& flip, const Color& color)
{
	SDL_Rect source = {
		src.x,
		src.y,
		src.width,
		src.height
	};

	SDL_Rect destination = {
		static_cast<int>(dst.x - m_Viewport.x),
		static_cast<int>(dst.y - m_Viewport.y),
		static_cast<int>(dst.width),
		static_cast<int>(dst.height)
	};

	int flipValue = SDL_FLIP_NONE;
	if (flip.horizontal)
	{
		flipValue = SDL_FLIP_HORIZONTAL;
	}

	if (flip.vertical)
	{
		flipValue |= SDL_FLIP_VERTICAL;
	}

	const SDL_RendererFlip renderFlip = static_cast<SDL_RendererFlip>(flipValue);
	SDL_Texture* texture = m_TextureCache[id];
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(texture, color.alpha);
	SDL_SetTextureColorMod(texture, color.red, color.green, color.blue);
	SDL_RenderCopyEx(m_Renderer, texture, &source, &destination, angle, nullptr, renderFlip);
}

void SdlGraphics::DrawString(const string& text, const size_t fontId, const float x, const float y, const Color& color)
{
	TTF_Font* font = m_FontCache[fontId];
	const SDL_Color sdlColor = {
		static_cast<Uint8>(color.red),
		static_cast<Uint8>(color.green),
		static_cast<Uint8>(color.blue),
		static_cast<Uint8>(color.alpha)
	};

	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), sdlColor);
	SDL_Rect destination{
		static_cast<int>(x - m_Viewport.x),
		static_cast<int>(y - m_Viewport.y),
		surface->w,
		surface->h
	};

	g_TextureBuffer = SDL_CreateTextureFromSurface(m_Renderer, surface);
	SDL_RenderCopy(m_Renderer, g_TextureBuffer, nullptr, &destination);
	SDL_FreeSurface(surface);
}

void SdlGraphics::SetWindowState(const EWindowState state)
{
	switch (state)
	{
	case BORDERLESS:
		SDL_SetWindowFullscreen(m_Window, SDL_WINDOW_FULLSCREEN_DESKTOP);
		break;

	case FULLSCREEN:
		SDL_SetWindowFullscreen(m_Window, SDL_WINDOW_FULLSCREEN);
		break;

	default:
		SDL_SetWindowFullscreen(m_Window, 0);
		break;
	}
}

size_t SdlGraphics::LoadTexture(const string& filename)
{
	const size_t textureId = std::hash<std::string>()(filename);
	if (m_TextureCache.count(textureId) > 0)
	{
		return textureId;
	}

	SDL_Texture* texture = IMG_LoadTexture(m_Renderer, filename.c_str());
	if (texture)
	{
		m_TextureCache.emplace(textureId, texture);
		return textureId;
	}

	Engine::Get().Logger().LogError("Cannot load texture: " + filename);
	return 0;
}

size_t SdlGraphics::LoadFont(const string& filename, const int fontSize)
{
	// You can have the same font loaded twice with different fontSize
	const size_t fontId = std::hash<std::string>()(filename + to_string(fontSize));
	if (m_FontCache.count(fontId) > 0)
	{
		return fontId;
	}

	TTF_Font* font = TTF_OpenFont(filename.c_str(), fontSize);
	if (font)
	{
		m_FontCache.emplace(fontId, font);
		return fontId;
	}

	Engine::Get().Logger().LogError("Cannot load font: " + filename);
	return 0;
}

void SdlGraphics::GetTextureSize(const size_t id, int* width, int* height)
{
	if (m_TextureCache.count(id) > 0)
	{
		SDL_Texture* texture = m_TextureCache[id];
		SDL_QueryTexture(texture, nullptr, nullptr, width, height);
	}
	else
	{
		*width = 0;
		*height = 0;
	}
}

void SdlGraphics::GetTextSize(const string& text, const size_t fontId, int* width, int* height)
{
	if (m_FontCache.count(fontId) > 0)
	{
		TTF_SizeText(m_FontCache[fontId], text.c_str(), width, height);
	}
	else
	{
		*width = 0;
		*height = 0;
	}
}

void SdlGraphics::SetViewport(const RectF& viewport)
{
	m_Viewport.Set(viewport);
	m_SavedViewport.Set(m_Viewport);
}

void SdlGraphics::SetViewport(const float x, const float y, const float w, const float h)
{
	m_Viewport.Set(x, y, w, h);
	m_SavedViewport.Set(m_Viewport);
}

void SdlGraphics::EnableViewport(const bool enable)
{
	if (enable)
	{
		m_Viewport.Set(m_SavedViewport);
	}
	else
	{
		m_Viewport.Set(0.0f, 0.0f, 0.0f, 0.0f);
	}
}

RectF& SdlGraphics::GetViewport()
{
	return m_Viewport;
}

void SdlGraphics::GetWindowSize(int* width, int* height)
{
	SDL_GetWindowSize(m_Window, width, height);
}
