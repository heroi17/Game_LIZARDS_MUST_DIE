#ifndef LMD_GAMELOGIC_INFORMATIONITEM
#define LMD_GAMELOGIC_INFORMATIONITEM

#include "Item.h"

enum InformationItemType
{
	LeaderLocation,
	PowerUpLocation
};

class InformationItem : Item
{
public:
	InformationItem(std::string name, std::string discription, InformationItemType type);
private:
	InformationItemType _type;
};



#endif // !LMD_GAMELOGIC_INFORMATIONITEM