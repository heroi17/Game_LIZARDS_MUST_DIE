#ifndef LMD_GAMELOGIC_ENTITY
#define LMD_GAMELOGIC_ENTITY

#include <vector>

class Entity
{
public:
	int Speed;
	int MaxHealth;
	int Health;
	int Damage;
	std::vector<int> Velocity;

private:
};

#endif // !LMD_GAMELOGIC_ENTITY