#ifndef LMD_GAMELOGIC_ITEM
#define LMD_GAMELOGIC_ITEM

#include <string>

class Item
{
public:
	std::string Name;
	std::string Discription;

	virtual void ApplyEffect();
private:

};

#endif // !LMD_GAMELOGIC_ITEM
