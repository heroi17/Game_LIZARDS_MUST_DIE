#ifndef LMD_GAMELOGIC_ITEM
#define LMD_GAMELOGIC_ITEM

#include <string>

class Item
{
public:
	std::string Name;
	std::string Discription;

	Item();
	Item(std::string name, std::string discription);
	virtual void ApplyEffect();

private:

};

#endif // !LMD_GAMELOGIC_ITEM
