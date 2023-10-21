#ifndef LMD_GAMELOGIC_INFORMATIONITEM
#define LMD_GAMELOGIC_INFORMATIONITEM

#include "Item.h"

class InformationItem : Item
{
public:
	enum InformationItemType;
	InformationItem(std::string name, std::string discription, InformationItemType type);
private:

};

#endif // !LMD_GAMELOGIC_INFORMATIONITEM