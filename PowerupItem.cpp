#include "PowerupItem.h"

PowerupItem::PowerupItem(std::string name, std::string discription, PowerupItemType type)
{
	_name = name;
	_discription = discription;
	_type = type;
}

void PowerupItem::ApplyEffect(Entity& entity)
{
	switch (_type)
	{
		case DamageBoost:
		{
			entity.Damage += 5;
		}
		case MaxHealthBoost:
		{
			entity.MaxHealth += 5;
		}
	}
}
