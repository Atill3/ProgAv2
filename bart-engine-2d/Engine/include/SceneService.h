#pragma once

#include <IScene.h>
#include <map>
#include <vector>
#include <string>
#include <TileMap.h>
#include <Properties.h>
#include <Factory.h>

using namespace std;

namespace bart
{
	class SceneService final : public IScene
	{
	public:
		virtual ~SceneService() = default;

		bool Initialize() override;
		void Destroy() override;
		void Load(const string& name) override;
		void Unload() override;
		void Update(float deltaTime) override;
		void Render() override;
		Entity* AddEntity(const string& name, const string& layer) override;
		Entity* FindEntity(const string& name) override;
		void RegisterScene(XMLNode* node) override;
		void RegisterPrefab(XMLNode* node) override;
		void AddLayer(const string& layer) override;
		void Reload() override;
		Entity* CreateEntity(const string& nameStr, const char* prefab, const string& layer, const RectF& transform, const float angle, const Properties& properties) override;
		void RegisterFactory(const string& key, Factory* factory) override;
		Factory* GetFactory(const string& key) override;
		void RenderLayer(const string& layer) override;
		
	private:

		map<string, string> m_PrefabMap;
		map<string, Factory* > m_FactoryMap;
		map<string, Entity*> m_EntityByNames;
		vector<Entity*> m_RunningEntities;
		vector<Entity*> m_StartingEntities;
		map<string, vector<Entity*>> m_EntityByLayer;
		string m_CurrentScene;
		map<string, string> m_SceneMap;
		TileMap m_TileMap;

		
	};
}
