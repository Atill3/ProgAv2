#include <Bart2d.h>
#include <SceneService.h>

bool bart::SceneService::Initialize()
{
	return true;
}

void bart::SceneService::Destroy()
{
	Unload();
}

void bart::SceneService::Load(const string & filename)
{
}

void bart::SceneService::Unload()
{
	for (Entity* entity : m_StartingEntities)
	{
		delete entity;
	}
	m_StartingEntities.clear();

	for (Entity* entity : m_RunningEntities)
	{
		entity->Destroy();
		delete entity;
	}

	m_RunningEntities.clear();
	m_EntityByNames.clear();
}

void bart::SceneService::Update(float deltaTime)
{
	for (Entity* entity : m_RunningEntities)
	{
		entity->Update(deltaTime);
	}

	if (m_StartingEntities.size() > 0)
	{
		vector<Entity*> entities = m_StartingEntities;
		m_StartingEntities.clear();

		for (Entity* entity : entities)
		{
			m_RunningEntities.emplace_back(entity);
			entity->Start();
		}
	}
}

void bart::SceneService::Render()
{
	for (Entity* entity : m_RunningEntities)
	{
		entity->Render();
	}
}

bart::Entity * bart::SceneService::AddEntity(const string & name)
{
	Entity* entity = new Entity();
	m_StartingEntities.emplace_back(entity);
	m_EntityByNames[name] = entity;
	return entity;

}

bart::Entity * bart::SceneService::FindEntity(const string & name)
{
	if (m_EntityByNames.count(name) > 0)
	{
		return m_EntityByNames[name];
	}

	return nullptr;
}
