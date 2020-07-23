#include <Bart2d.h>
#include <SdlGraphics.h>
#include <SDL.h>
#include <SDL_image.h>
#include <Engine.h>

bool bart::SdlGraphics::Initialize()
{
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		Engine::Get().ILogger().LogError("Error with SDL");
		return false;
	}

	m_ClearColor = new SDL_Color{ 61, 61, 61, 255 };
	return true;
}

void bart::SdlGraphics::Destroy()
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

bool bart::SdlGraphics::InitWindow(const string& title, int w, int h, EWindowState state)
{
	m_Window = SDL_CreateWindow(
		title.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		w, h, SDL_WINDOW_BORDERLESS);

	if(m_Window == nullptr)
	{
		Engine::Get().ILogger().LogError("Error with SDL Window");
		return false;
	}

	m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);

	if(m_Renderer == nullptr)
	{
		Engine::Get().ILogger().LogError("Error with SDL Renderer");
		return false;
	}

	if(state == EWindowState::BORDERLESS)
	{
		SDL_SetWindowFullscreen(m_Window, SDL_WINDOW_FULLSCREEN_DESKTOP);
	}
	else if(state == EWindowState::FULLSCREEN)
	{
		SDL_SetWindowFullscreen(m_Window, SDL_WINDOW_FULLSCREEN);
	}

	return true;
}

void bart::SdlGraphics::Clear()
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

void bart::SdlGraphics::Present()
{
	SDL_RenderPresent(m_Renderer);
}

void bart::SdlGraphics::SetColor(unsigned char r, unsigned char g, unsigned char b)
{
	SetColor(r, g, b, 255);
}

void bart::SdlGraphics::SetColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	SDL_SetRenderDrawColor(m_Renderer, r, g, b, a);
}

void bart::SdlGraphics::SetClearColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	m_ClearColor->r = r;
	m_ClearColor->g = g;
	m_ClearColor->b = b;
	m_ClearColor->a = a;
}

void bart::SdlGraphics::DrawRect(float x, float y, float w, float h)
{
	SDL_Rect rect = {
		static_cast<int>(x),
		static_cast<int>(y),
		static_cast<int>(w),
		static_cast<int>(h)
	};

	SDL_RenderDrawRect(m_Renderer, &rect);
}

void bart::SdlGraphics::FillRect(float x, float y, float w, float h)
{
	SDL_Rect rect = {
		static_cast<int>(x),
		static_cast<int>(y),
		static_cast<int>(w),
		static_cast<int>(h)
	};

	SDL_RenderFillRect(m_Renderer, &rect);
}

void bart::SdlGraphics::DrawCircle(float x, float y, float r)
{
	float tX = x;
	float tY = y;

	const double inc = 0.01;
	const double circle = 6.63;
	double angle = 0.0;

	while(angle < circle)
	{
		tX = static_cast<float>(x + r * cos(angle));
		tY = static_cast<float>(y + r * sin(angle));
		DrawPoint(tX, tY);

		angle += inc;
	}
}

void bart::SdlGraphics::DrawPoint(float x, float y)
{
	const int tX = static_cast<int>(x);
	const int tY = static_cast<int>(y);
	SDL_RenderDrawPoint(m_Renderer, tX, tY);
}

void bart::SdlGraphics::DrawLine(float x1, float y1, float x2, float y2)
{
	const int tX1 = static_cast<int>(x1);
	const int tY1 = static_cast<int>(y1);
	const int tX2 = static_cast<int>(x2);
	const int tY2 = static_cast<int>(y2);
	SDL_RenderDrawLine(m_Renderer, tX1, tY1, tX2, tY2);
}

void bart::SdlGraphics::SetWindowState(EWindowState state)
{
	switch (state)
	{
	case EWindowState::BORDERLESS:
		SDL_SetWindowFullscreen(m_Window, SDL_WINDOW_FULLSCREEN_DESKTOP);	
		break;
	case EWindowState::FULLSCREEN:
		SDL_SetWindowFullscreen(m_Window, SDL_WINDOW_FULLSCREEN);
		break;
	
	default:
		SDL_SetWindowFullscreen(m_Window, 0);
		break;

	}
}

size_t bart::SdlGraphics::LoadTexture(const string& filename)
{
	const size_t texturedId = std::hash<std::string>()(filename);
	if (m_TextureChache.count(texturedId) > 0)
	{
		return texturedId;
	}

	SDL_Texture* texture = IMG_LoadTexture(m_Renderer, filename.c_str());
	if (texture) 
	{
		m_TextureChache.emplace(texturedId, texture);
		return texturedId;
	}

	Engine::Get().ILogger().LogError("Cannot load Texutre" + filename);
	return 0;

}

void bart::SdlGraphics::UnloadTexture(size_t id)
{
	if (m_TextureChache.count(id) > 0)
	{
		SDL_DestroyTexture(m_TextureChache[id]);
		m_TextureChache.erase(id);
	}
}

void bart::SdlGraphics::DrawTexture(size_t id, int srcX, int srcY, int srcW, int srcH, float dstX, 
	float dstY, float dstW, float dstH, float angle, bool hflip, bool vflip, unsigned char alpha)
{
	SDL_Rect src = {
		srcX,
		srcY,
		srcW,
		srcH
	};

	SDL_Rect dst = {
		static_cast<int>(dstX),
		static_cast<int>(dstY),
		static_cast<int>(dstW),
		static_cast<int>(dstH)
	};

	int flipValue = SDL_FLIP_NONE;
	if (hflip)
	{
		flipValue = SDL_FLIP_HORIZONTAL;
	}	
	if (vflip)
	{
		flipValue = SDL_FLIP_VERTICAL;
	}

	const SDL_RendererFlip flip = static_cast<SDL_RenderFlip>(flipValue);
	SDL_Texture* texture = m_TextureChache[id];
	SDL_SetTextureAlphaMod;
}

void bart::SdlGraphics::GetTextureSize(size_t id, int* width, int* height)
{

}
