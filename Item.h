#ifndef LMD_GAMELOGIC_ITEM
#define LMD_GAMELOGIC_ITEM

#include <string>

class Item
{
public:
	
	Item();
	Item(std::string name, std::string discription);
	virtual void ApplyEffect();

private:
	std::string _name;
	std::string _discription;
};

#endif // !LMD_GAMELOGIC_ITEM
