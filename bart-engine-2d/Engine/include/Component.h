#pragma once

namespace bart
{
	class Entity;

	class Component
	{
	public:
		virtual ~Component() = default;

		virtual void Awake()
		{
			/** Override this if you need something to happen here **/
		}

		virtual void Start()
		{
			/** Override this if you need something to happen here **/
		}

		virtual void Update(float deltaTime)
		{
			/** Override this if you need something to happen here **/
		}

		virtual void Render()
		{
			/** Override this if you need something to happen here **/
		}

		virtual void Destroy()
		{
			/** Override this if you need something to happen here **/
		}

		virtual void OnEnable()
		{
			/** Override this if you need something to happen here **/
		}

		virtual void OnDisable()
		{
			/** Override this if you need something to happen here **/
		}

		void SetOwner(Entity* owner)
		{
			m_Owner = owner;
		}

	protected:
		Entity* m_Owner = nullptr;
	};
}
