#include "Lizard.h"

using namespace GameLogic;

Lizard::Lizard()
{
}

GameLogic::Lizard::Lizard(int maxHealth, int damage)
{
	_maxHealth = maxHealth;
	_health = maxHealth;
	_damage = damage;
}
