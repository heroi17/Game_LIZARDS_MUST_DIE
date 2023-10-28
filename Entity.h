#ifndef LMD_GAMELOGIC_ENTITY
#define LMD_GAMELOGIC_ENTITY

#include <vector>

namespace GameLogic
{
	class Entity
	{
	public:
		bool SetHealth(int amount);
		bool SetDamage(int amount);
		bool SetMaxHealth(int amount);

		int GetHealth();
		int GetMaxHealth();
		int GetDamage();

	protected:
		int _maxHealth;
		int _health;
		int _damage;

	private:
	};
}
#endif // !LMD_GAMELOGIC_ENTITY