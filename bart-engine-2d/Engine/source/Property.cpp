#include <Bart2d.h>
#include <Property.h>
#include <Properties.h>
#include <Color.h>
#include <string>
#include <sstream>
#include <tinyxml.h>

bart::BoolProperty::BoolProperty()
{
	m_Type = PT_BOOL;
}

bart::ColorProperty::ColorProperty()
{
	m_Type = PT_COLOR;
}

void bart::ColorProperty::SetFromHex(const std::string& aHexValue)
{
	if (!aHexValue.empty())
	{
		std::string tColor = aHexValue.substr(1);
		const size_t tColorLen = tColor.size();

		int tIdx = 0;
		int tR, tG, tB, tA;
		std::stringstream tStringStream;

		if (tColorLen == 8)
		{
			tStringStream << std::hex << tColor.substr(tIdx, 2);
			tStringStream >> tA;
			tStringStream.clear();

			tIdx += 2;
		}
		else
		{
			tA = 255;
		}

		tStringStream << std::hex << tColor.substr(tIdx, 2);
		tStringStream >> tR;
		tStringStream.clear();

		tIdx += 2;

		tStringStream << std::hex << tColor.substr(tIdx, 2);
		tStringStream >> tG;
		tStringStream.clear();

		tIdx += 2;

		tStringStream << std::hex << tColor.substr(tIdx, 2);
		tStringStream >> tB;
		tStringStream.clear();

		Value.Set(
			static_cast<unsigned char>(tR),
			static_cast<unsigned char>(tG),
			static_cast<unsigned char>(tB),
			static_cast<unsigned char>(tA));
	}
	else
	{
		Value.Set(137, 137, 137, 255);
	}
}

bart::FloatProperty::FloatProperty()
{
	m_Type = PT_FLOAT;
}

bart::StringProperty::StringProperty()
{
	m_Type = PT_STRING;
}

bart::IntProperty::IntProperty()
{
	m_Type = PT_INT;
}

void bart::Properties::Load(XMLNode* node)
{
	XMLNode* tPropNode = node->FirstChild();
	while (tPropNode != nullptr)
	{
		XMLElement* tParamElement = tPropNode->ToElement();
		const char* tName = tParamElement->Attribute("name");
		const char* tType = tParamElement->Attribute("type");

		if (tName != nullptr)
		{
			std::string tKey = std::string(tName);
			std::string tTypeStr;

			if (tType == nullptr)
			{
				tTypeStr = "string";
			}
			else
			{
				tTypeStr = std::string(tType);
			}

			if (tTypeStr == "bool")
			{
				BoolProperty* tBoolProperty = new BoolProperty();
				tBoolProperty->Value = tParamElement->BoolAttribute("value");
				Add(tName, tBoolProperty);
			}
			else if (tTypeStr == "color")
			{
				const char* tColorHex = tParamElement->Attribute("value");

				if (tColorHex != nullptr)
				{
					ColorProperty* tColorProperty = new ColorProperty();
					tColorProperty->SetFromHex(std::string(tColorHex));
					Add(tName, tColorProperty);
				}
			}
			else if (tTypeStr == "float")
			{
				FloatProperty* tFloatProperty = new FloatProperty();
				tFloatProperty->Value = tParamElement->FloatAttribute("value");
				Add(tName, tFloatProperty);
			}
			else if (tTypeStr == "file")
			{
				const char* tFileName = tParamElement->Attribute("value");

				if (tFileName != nullptr)
				{
					StringProperty* tFileProperty = new StringProperty();
					tFileProperty->Value = std::string(tFileName);
					Add(tName, tFileProperty);
				}
			}
			else if (tTypeStr == "int")
			{
				IntProperty* tIntProperty = new IntProperty();
				tIntProperty->Value = tParamElement->IntAttribute("value");
				Add(tName, tIntProperty);
			}
			else if (tTypeStr == "string")
			{
				const char* tString = tParamElement->Attribute("value");

				if (tString != nullptr)
				{
					StringProperty* tStringProperty = new StringProperty();
					tStringProperty->Value = std::string(tString);
					Add(tName, tStringProperty);
				}
			}
		}

		tPropNode = tPropNode->NextSibling();
	}
}

bool bart::Properties::GetBool(const std::string& name)
{
	if (m_PropertyMap.count(name) > 0)
	{
		if (m_PropertyMap[name]->GetType() == PT_BOOL)
		{
			return static_cast<BoolProperty*>(m_PropertyMap[name])->Value;
		}
	}

	return "";
}

bart::Color bart::Properties::GetColor(const std::string& name)
{
	if (m_PropertyMap.count(name) > 0)
	{
		if (m_PropertyMap[name]->GetType() == PT_COLOR)
		{
			return static_cast<ColorProperty*>(m_PropertyMap[name])->Value;
		}
	}

	return Color::Black;
}

float bart::Properties::GetFloat(const std::string& name)
{
	if (m_PropertyMap.count(name) > 0)
	{
		if (m_PropertyMap[name]->GetType() == PT_FLOAT)
		{
			return static_cast<FloatProperty*>(m_PropertyMap[name])->Value;
		}
	}

	return 0.0f;
}

std::string bart::Properties::GetString(const std::string& name)
{
	if (m_PropertyMap.count(name) > 0)
	{
		if (m_PropertyMap[name]->GetType() == PT_STRING)
		{
			return static_cast<StringProperty*>(m_PropertyMap[name])->Value;
		}
	}

	return "";
}

int bart::Properties::GetInt(const std::string& name)
{
	if (m_PropertyMap.count(name) > 0)
	{
		if (m_PropertyMap[name]->GetType() == PT_INT)
		{
			return static_cast<IntProperty*>(m_PropertyMap[name])->Value;
		}
	}

	return 0;
}

void bart::Properties::Add(const std::string& name, Property* poperty)
{
	if (m_PropertyMap.count(name) == 0)
	{
		m_PropertyMap[name] = poperty;
	}
}

void bart::Properties::Clear()
{
	for (TPropertyMap::iterator i = m_PropertyMap.begin(); i != m_PropertyMap.end(); ++i)
	{
		delete i->second;
	}

	m_PropertyMap.clear();
}
