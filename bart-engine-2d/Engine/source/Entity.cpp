#include <Entity.h>
#include <tinyxml.h>
#include <Engine.h>
#include <Factory.h>

void Entity::Update(const float deltaTime)
{
	if (m_IsActive)
	{
		for (Component* component : m_Components)
		{
			component->Update(deltaTime);
		}
	}
}

void Entity::Render()
{
	if (m_IsActive)
	{
		for (Component* component : m_Components)
		{
			component->Render();
		}
	}
}

void Entity::Destroy()
{
	m_IsActive = false;
	for (Component* component : m_Components)
	{
		component->Destroy();
		delete component;
	}
	m_Components.clear();
}

void Entity::Start()
{
	if (m_IsActive)
	{
		for (Component* component : m_Components)
		{
			component->Start();
		}
	}
}

void Entity::SetActive(const bool active)
{
	if (m_IsActive != active)
	{
		m_IsActive = active;
		if (m_IsActive)
		{
			for (Component* component : m_Components)
			{
				component->OnEnable();
			}
		}
		else
		{
			for (Component* component : m_Components)
			{
				component->OnDisable();
			}
		}
	}
}

void bart::Entity::LoadFromFile(const string& prefabFile, Entity* entity)
{
	XMLDocument document;
	if(document.LoadFile(prefabFile.c_str()) == XML_SUCCESS)
	{
		XMLNode* prefabNode = document.FirstChild();
		if(prefabNode)
		{
			XMLNode* node = prefabNode->FirstChild();
			while(node)
			{
				string nodeValue = node->Value();
				Factory* factory = Engine::Get().Scene().GetFactory(nodeValue);

				factory->Create(entity, node);

				node = node->NextSibling();
			}
		}
	}
}
