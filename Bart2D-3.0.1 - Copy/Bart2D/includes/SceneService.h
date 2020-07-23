#pragma once

#include <IScene.h>
#include <map>
#include <vector>

using namespace std;
namespace bart
{
	class SceneService final : public IScene
	{
	public:
		virtual ~SceneService() = default;

		bool Initialize() override;
		void Destroy() override;
		void Load(const string& filename) override;
		void Unload() override;
		void Update(float deltatime) override;
		void Render() override;
		Entity* AddEntity(const string& name) override;
		Entity* FindEntity(const string& name) override;

	private:
		map<string, Entity*> m_EntityByNames;
		vector<Entity*> m_RunningEntities;
		vector<Entity*> m_StartingEntities;
	};
}