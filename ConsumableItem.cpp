#include "ConsumableItem.h"

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
			entity.Health = entity.MaxHealth;
		}

		case HealingItem_50:
		{
			// Health is up to 50% of it's maximum or set to MaxHealth if raise is higher than MaxHealth
			entity.Health = (entity.Health + entity.MaxHealth * 0.5 > entity.MaxHealth) ? entity.MaxHealth : entity.Health + entity.MaxHealth * 0.3;
		}

		case HealingItem_30:
		{
			// Health is up to 30% of it's maximum or set to MaxHealth if raise is higher than MaxHealth
			entity.Health = (entity.Health + entity.MaxHealth * 0.3 > entity.MaxHealth) ? entity.MaxHealth : entity.Health + entity.MaxHealth * 0.3;
		}
	}
}