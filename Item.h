#ifndef LMD_GAMELOGIC_ITEM
#define LMD_GAMELOGIC_ITEM

#include <string>

#include "Player.h"

namespace GameLogic
{
	class Item
	{
	public:
		virtual void ApplyEffect(Entity& entity);

	protected:
		std::string _name;
		std::string _discription;

	private:

	};
}

#endif // !LMD_GAMELOGIC_ITEM
