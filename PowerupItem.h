#ifndef LMD_GAMELOGIC_POWERUPITEM
#define LMD_GAMELOGIC_POWERUPITEM

#include "Item.h"

namespace GameLogic
{
	enum PowerupItemType
	{
		DamageBoost,
		MaxHealthBoost,
	};

	class PowerupItem : public Item
	{
	public:
		PowerupItem(std::string name, std::string discription, PowerupItemType type);
		void ApplyEffect(Entity& entity);
	private:
		PowerupItemType _type;
	};
}

#endif // !LMD_GAMELOGIC_POWERUPITEM
