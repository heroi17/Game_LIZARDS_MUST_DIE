#include "ConsumableItem.h"

using namespace GameLogic;

ConsumableItem::ConsumableItem(std::string name, std::string discription, ConsumableItemType type)
{
	_name = name;
	_discription = discription;
	_type = type;
}

void ConsumableItem::ApplyEffect(Entity& entity)
{
	switch (_type)
	{
		case HealingItem_100:
		{
			entity._health = entity._maxHealth;
		}

		case HealingItem_50:
		{
			// Health is up to 50% of it's maximum or set to MaxHealth if raise is higher than MaxHealth
			entity._health = (entity._health + entity._maxHealth * 0.5 > entity._maxHealth) ? entity._maxHealth : entity._health + entity._maxHealth * 0.5;
		}

		case HealingItem_30:
		{
			// Health is up to 30% of it's maximum or set to MaxHealth if raise is higher than MaxHealth
			entity._health = (entity._health + entity._maxHealth * 0.3 > entity._maxHealth) ? entity._maxHealth : entity._health + entity._maxHealth * 0.3;
		}
	}
}