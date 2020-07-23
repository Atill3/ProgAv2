#pragma once

#include <Component.h>
#include <string>

using namespace std;

namespace  bart
{
	class Sound final : public Component
	{
	public:
		virtual ~Sound() = default;

		void Load(const string& filename);
		void Play();

	protected:
		size_t m_SoundId;
	};
}
