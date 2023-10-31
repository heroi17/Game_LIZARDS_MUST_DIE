#include "Lizard.h"

using namespace GameLogic;

Lizard::Lizard()
{
}

GameLogic::Lizard::Lizard(LizzardType type)
{
	_type = type;

	switch (type)
	{
		case Leader:
		{
			_maxHealth = 100;
			_health = 100;
			_damage = 20;
			_speed = 10;
			_size = 30;
		}
		case RegularWarrior:
		{
			_maxHealth = 30;
			_health = 30;
			_damage = 5;
			_speed = 15;
			_size = 10;
		}
	}
}

LizzardType GameLogic::Lizard::GetType()
{
	return _type;
}

