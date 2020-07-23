#pragma once
#include <SDL_Mixer.h>
#include <IAudio.h>

using namespace std;

namespace bart
{
	class AudioService final : public IAudio
	{
	public:
		virtual ~AudioService() = default;

		bool Initialize() override;
		void Destroy() override;
		size_t LoadMusic(const string& filename) override;
		size_t LoadSound(const string& filename) override;
		void UnloadMusic(size_t id) override;
		void UnloadSound(size_t id) override;
		void PlayMusic(size_t id) override;
		void PlaySound(size_t id) override;
		void RestartMusic() override;
		void StopMusic() override;


	private:
		typedef map<size_t, _Mix_Music*> Tmusic;
		typedef map<size_t, Mix_Chunk*> Tsound;

		Tmusic m_MusicCache;
		Tsound m_SoundCache;
		
	};


}