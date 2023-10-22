#ifndef LMD_GAMELOGIC_ITEM
#define LMD_GAMELOGIC_ITEM

#include <string>

#include "Entity.h"

class Item
{
public:
	virtual void ApplyEffect();

protected:
	std::string _name;
	std::string _discription;

private:

};

#endif // !LMD_GAMELOGIC_ITEM
