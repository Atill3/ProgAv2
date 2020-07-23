#pragma once


#include <IService.h>
#include <string>
#include <Entity.h>
using namespace std;

namespace bart
{
	class IScene : public IService
	{
	public:
		virtual ~IScene() = default;

		virtual void Load(const string& filename) = 0;
		virtual void Unload() = 0;
		virtual void Update(float deltaTime) = 0;
		virtual void Render() = 0;

		virtual Entity* AddEntity(const string& name) = 0;
		virtual Entity* FindEntity(const string& name) = 0;

	};
}