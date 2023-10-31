#ifndef LMD_GAMELOGIC_INFORMATIONITEM
#define LMD_GAMELOGIC_INFORMATIONITEM

#include "Item.h"
#include "Map.h"


namespace GameLogic
{
	enum InformationItemType
	{
		LeaderLocation
	};

	class InformationItem : public Item
	{
	public:
		InformationItem(std::string name, std::string discription, InformationItemType type, Map* map);
		void ApplyEffect(Entity& entity) override;

	private:
		InformationItemType _type;
		Map* _map;

	};
}


#endif // !LMD_GAMELOGIC_INFORMATIONITEM