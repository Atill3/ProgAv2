#pragma once

namespace tinyxml2
{
	class XMLNode;
}

using namespace tinyxml2;
namespace bart
{
	class Entity;

	class Factory
	{
	public:
		virtual ~Factory() = default;
		virtual void Create(Entity* entity, tinyxml2::XMLNode* id) = 0;
	};
}
