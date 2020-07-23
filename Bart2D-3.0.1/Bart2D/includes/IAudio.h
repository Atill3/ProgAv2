#pragma once

#include <IService.h>
#include <string>

using namespace std;

namespace bart
{
	class IAudio : public IService
	{
	public:
		virtual ~IAudio() = default;

		
		virtual size_t LoadMusic(const string& filename) = 0;
		virtual size_t LoadSound(const string& filename) = 0;
		virtual void UnloadMusic(size_t id) = 0;
		virtual void UnloadSound(size_t id) = 0;
		virtual void PlayMusic(size_t id) = 0;
		virtual void PlaySound(size_t id) = 0;
		virtual void RestartMusic() = 0;
		virtual void StopMusic() = 0;
	};

}

