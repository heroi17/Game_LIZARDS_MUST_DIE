#include "Lizard.h"

using namespace GameLogic;

Lizard::Lizard()
{
}

GameLogic::Lizard::Lizard(int maxHealth, int damage)
{
	MaxHealth = maxHealth;
	Health = maxHealth;
	Damage = damage;
}
