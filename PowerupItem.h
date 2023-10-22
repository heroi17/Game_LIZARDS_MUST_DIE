#ifndef LMD_GAMELOGIC_POWERUPITEM
#define LMD_GAMELOGIC_POWERUPITEM

#include "Item.h"

enum PowerupItemType
{
	DamageBoost,
	MaxHealthBoost,
};

class PowerupItem : Item
{
public:
	PowerupItem(std::string name, std::string discription, PowerupItemType type);
private:
	PowerupItemType _type;
};


#endif // !LMD_GAMELOGIC_POWERUPITEM
