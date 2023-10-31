#ifndef LMD_GAMELOGIC_LIZARD
#define LMD_GAMELOGIC_LIZARD

#include "Item.h"

namespace GameLogic
{
	enum LizzardType
	{
		RegularWarrior,
		Leader
	};

	class Lizard : public Entity
	{
	public:
		Lizard();
		Lizard(LizzardType type);

		LizzardType GetType();
	private:
		LizzardType _type;
	};
}
#endif // !LMD_GAMELOGIC_LIZARD
