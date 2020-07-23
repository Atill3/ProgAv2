#include <Bart2d.h>
#include <SceneService.h>
#include <tinyxml.h>
#include <Engine.h>
#include <Transform.h>
#include <SpriteFactory.h>

bool SceneService::Initialize()
{
	RegisterFactory("sprite", new SpriteFactory());
	return true;
}

void SceneService::Destroy()
{
	delete m_FactoryMap["sprite"];
	m_FactoryMap.clear();
	Unload();
}

void SceneService::Load(const string& name)
{
	if (m_SceneMap.count(name) > 0)
	{
		const string targetScene = name;
		if (!m_CurrentScene.empty())
		{
			Unload();
		}

		m_CurrentScene = targetScene;
		const string path = m_SceneMap[targetScene];
		m_TileMap.Load(path);

		const Color bgColor = m_TileMap.GetBackgroundColor();
		Engine::Get().Graphics().SetClearColor(bgColor);
	}
	else
	{
		Engine::Get().Logger().LogError("Cannot load scene" + name);
	}
}

void SceneService::Unload()
{
	m_CurrentScene.clear();

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
	m_TileMap.Clean();
	m_EntityByLayer.clear();
}

void SceneService::Update(const float deltaTime)
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
			string layer = entity->GetLayer();
			if (m_EntityByLayer.count(layer) > 0)
			{
				m_EntityByLayer[layer].emplace_back(entity);
			}
			entity->Start();
		}
	}
}

void SceneService::Render()
{
	m_TileMap.Draw();
}

Entity* SceneService::AddEntity(const string& name, const string& layer)
{
	Entity* entity = new Entity();
	m_StartingEntities.emplace_back(entity);
	entity->SetLayer(layer);
	m_EntityByNames[name] = entity;
	return entity;
}

Entity* SceneService::FindEntity(const string& name)
{
	if (m_EntityByNames.count(name) > 0)
	{
		return m_EntityByNames[name];
	}

	return nullptr;
}

void bart::SceneService::RegisterScene(XMLNode * node)
{
	if (node)
	{
		XMLNode* sceneNode = node->FirstChild();
		while (sceneNode)
		{
			XMLElement* sceneElement = sceneNode->ToElement();
			string name = sceneElement->Attribute("name");
			string filename = sceneElement->Attribute("filename");
			if (!name.empty() && !filename.empty())
			{
				m_SceneMap.emplace(name, filename);
				if (m_CurrentScene.empty())
				{
					Load(name);
				}
			}
			sceneNode = sceneNode->NextSibling();
		}
	}
}

void SceneService::RegisterPrefab(XMLNode* node)
{
	if (node)
	{
		XMLNode* prefabNode = node->FirstChild();
		while (prefabNode)
		{
			XMLElement* sceneElement = prefabNode->ToElement();
			string name = sceneElement->Attribute("name");
			string filename = sceneElement->Attribute("filename");
			if (!name.empty() && !filename.empty())
			{
				m_PrefabMap.emplace(name, filename);
			}
			prefabNode = prefabNode->NextSibling();
		}
	}
}

void bart::SceneService::AddLayer(const string & layer)
{
	if (m_EntityByLayer.count(layer) == 0)
	{
		m_EntityByLayer.emplace(layer, vector<Entity*>());
	}
}

void bart::SceneService::Reload()
{
	if (!m_CurrentScene.empty())
	{
		const string savedSceneName = m_CurrentScene;
		Unload();
		Load(savedSceneName);
	}
}

Entity * bart::SceneService::CreateEntity(const string & nameStr, const char * prefab, const string & layer, 
	const RectF & transform, const float angle, const Properties & properties)
{
	//Map de prefab [string, string]
	string filename = m_PrefabMap[prefab];
	Entity* entity = AddEntity(nameStr, layer);
	Transform* transformComponent = entity->AddComponent<Transform>();
	transformComponent->Set(transform.x, transform.y, transform.width, transform.height);
	transformComponent->angle = angle;
	entity->LoadFromFile(filename, entity);

	return entity;
}

void SceneService::RegisterFactory(const string& key, Factory* factory)
{
	m_FactoryMap.emplace(key, factory);
}

Factory* SceneService::GetFactory(const string& key)
{
	return m_FactoryMap[key];
}

void bart::SceneService::RenderLayer(const string & layer)
{
	for (Entity* entity : m_EntityByLayer[layer])
	{
		entity->Render();
	}
}
