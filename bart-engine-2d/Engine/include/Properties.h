#pragma once

#include <string>
#include <Color.h>
#include <Property.h>
#include <map>

namespace tinyxml2
{
	class XMLNode;
}

using namespace tinyxml2;

namespace bart
{
	class Properties
	{
	public:
		void Load(XMLNode* node);
		bool GetBool(const std::string& name);
		Color GetColor(const std::string& name);
		float GetFloat(const std::string& name);
		std::string GetString(const std::string& name);
		int GetInt(const std::string& name);
		void Add(const std::string& name, Property* poperty);
		void Clear();

	private:
		typedef std::map<std::string, Property*> TPropertyMap;
		TPropertyMap m_PropertyMap;
	};
}