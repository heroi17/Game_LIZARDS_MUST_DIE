#include "Item.h"

using namespace GameLogic;

std::string GameLogic::Item::GetName()
{
	return _name;
}

std::string GameLogic::Item::GetDiscription()
{
	return _discription;
}

void Item::ApplyEffect(Entity& entity)
{
	// None
}
