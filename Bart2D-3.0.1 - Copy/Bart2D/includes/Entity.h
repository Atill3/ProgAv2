#pragma once

#include <vector>
#include <Component.h>
#include <typeinfo>
#include <map>

using namespace std;
namespace bart
{
	class Entity final
	{
	public:
		void Update(float deltatime);
		void Render();
		void Destroy();
		void Start();
		void SetActive(bool active);

		template<typename T>
		T* AddComponent()
		{
			T* component = new T();
			component->SetOwner(this);
			m_Components.emplace_back(component);

			const type_info* type = &typeid(*component);
			m_ComponentByType.emplace(type, component);

			component->Awake();
			return component;
		}


		template<typename T>
		T* GetComponent()
		{
			const type_info* type = &typeid(T);
			if (m_ComponentByType.count(type) > 0)
			{
				return static_cast<T*>(m_ComponentByType[type]);
			}

			return nullptr;
		}
	private:
		vector<Component*> m_Components;
		map<const type_info*, Component*> m_ComponentByType;
		bool m_IsActive = true;

	};
}