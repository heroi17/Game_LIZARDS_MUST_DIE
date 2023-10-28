#ifndef LMD_GAMELOGIC_ENTITY
#define LMD_GAMELOGIC_ENTITY

#include <vector>

namespace GameLogic
{
	class Entity
	{
	public:
		bool SetHealth(int amount); // Returns true if Health is set to below zero value (Death)
		bool SetDamage(int amount);	// Returns true if MaxHealth is set to below zero value (Also death)
		bool SetMaxHealth(int amount); // Returns true if Damage is set to below zero value (Exhaustion and eventual death)

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