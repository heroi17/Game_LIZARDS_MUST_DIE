#ifndef LMD_GAMELOGIC_POWERUPITEM
#define LMD_GAMELOGIC_POWERUPITEM

#include "Item.h"

class PowerupItem : Item
{
public:
	enum PowerupItemType;
	PowerupItem(std::string name, std::string discription, PowerupItem type);
private:

};

#endif // !LMD_GAMELOGIC_POWERUPITEM
