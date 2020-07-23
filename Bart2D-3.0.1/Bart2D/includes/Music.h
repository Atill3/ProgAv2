#pragma once

#include <Component.h>
#include <string>

using namespace std;

namespace  bart
{
	class Music final : public Component
	{
	public:
		virtual ~Music() = default;

		void Load(const string& filename);
		void Play();
		void Stop();
		void Restart();
		void Update(float deltatime) override;
	

	protected:
		size_t m_MusicId;

		bool IsPlaying;
		bool IsPress = false;


	};
}
