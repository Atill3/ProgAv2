#include <SpriteFactory.h>
#include <Sprite.h>
#include <Entity.h>
#include <tinyxml.h>

void bart::SpriteFactory::Create(Entity* entity, tinyxml2::XMLNode* id)
{
	Sprite* sprite = entity->AddComponent<Sprite>();
	XMLElement* element = id->ToElement();
	const string title = element->Attribute("filename");
	entity->GetComponent<Sprite>()->Load(title);
}
