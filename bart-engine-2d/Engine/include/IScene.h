#pragma once

#include <IService.h>
#include <Entity.h>
#include <string>
#include <Properties.h>
#include <Factory.h>

namespace tinyxml2
{
	class XMLNode;
}

using namespace tinyxml2;
using namespace bart;

namespace bart
{
	class RectF;

	class IScene : public IService
	{
	public:
		virtual ~IScene() = default;
		virtual void Load(const string& name) = 0;
		virtual void Unload() = 0;
		virtual void Update(float deltaTime) = 0;
		virtual void Render() = 0;
		virtual Entity* AddEntity(const string& name, const string& layer) = 0;
		virtual Entity* FindEntity(const string& name) = 0;
		virtual void AddLayer(const string& layer) = 0;
		
		virtual void RegisterScene(XMLNode* node) = 0;
		virtual void RegisterPrefab(XMLNode* node) = 0;
		virtual void Reload() = 0;
		virtual Entity* CreateEntity(const string& nameStr, const char* prefab, const string& layer, const RectF& transform, const float angle, const Properties& properties) = 0;
		virtual void RegisterFactory(const string& key, Factory* factory) = 0;
		virtual Factory* GetFactory(const string& key) = 0;
		virtual void RenderLayer(const string& layer) = 0;
	};
}
