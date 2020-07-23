#pragma once
namespace bart
{
	class Entity;

	class Component
	{
	public:
		virtual ~Component() = default;

		virtual void Awake() {}
		virtual void Start() {}
		virtual void Update(float deltaTime) {}
		virtual void Render() {}
		virtual void Destroy() {}
		virtual void OnEnable() {}
		virtual void OnDisable() {}

		void SetOwner(Entity* owner)
		{
			m_Owner = owner;
		}

	protected:
		Entity* m_Owner = nullptr;
	};
}