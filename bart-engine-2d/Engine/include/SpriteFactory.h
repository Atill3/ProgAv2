#pragma once
#include <Factory.h>

namespace bart
{
	class SpriteFactory final : public Factory
	{
	public:
		virtual ~SpriteFactory() = default;
		void Create(Entity* entity, tinyxml2::XMLNode* id) override;
	};

}