#include "PowerupItem.h"

using namespace GameLogic;

PowerupItem::PowerupItem(std::string name, std::string discription, PowerupItemType type)
{
	_name = name;
	_discription = discription;
	_type = type;
}

void PowerupItem::ApplyEffect(Entity* entity) 
{
	switch (_type)
	{
		case DamageBoost:
		{
			entity->SetDamage(entity->GetDamage() + 10);
			break;
		}
		case MaxHealthBoost:
		{
			entity->SetMaxHealth(entity->GetMaxHealth() + 20);
			break;
		}
	}
}
