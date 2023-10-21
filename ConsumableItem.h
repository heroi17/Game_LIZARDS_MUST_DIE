#ifndef LMD_GAMELOGIC_CONSUMABLEITEM
#define LMD_GAMELOGIC_CONSUMABLEITEM

#include "Item.h"

class ConsumableItem : Item
{
public:

	enum ConsumableItemType;
	ConsumableItem(std::string name, std::string discription, ConsumableItemType type);

private:
	
};

#endif // !LMD_GAMELOGIC_CONSUMABLEITEM
