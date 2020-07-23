#pragma once

#include <IScene.h>
#include <map>
#include <vector>

namespace bart
{
	class SceneService final : public IScene
	{
	public:
		virtual  ~SceneService() = default;

		// Inherited via IScene
		virtual bool Initialize() override;
		virtual void Destroy() override;
		virtual void Load(const string & filename) override;
		virtual void Unload() override;
		virtual void Update(float deltaTime) override;
		virtual void Render() override;
		virtual Entity * AddEntity(const string & name) override;
		virtual Entity * FindEntity(const string & name) override;

	private:
		map<string, Entity*> m_EntityByNames;
		vector<Entity*> m_RunningEntities;
		vector<Entity*> m_StartingEntities;
	};
}