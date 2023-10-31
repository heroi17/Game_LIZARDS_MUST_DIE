#ifndef LMD_GAMELOGIC_ENTITY
#define LMD_GAMELOGIC_ENTITY

#include <vector>

namespace GameLogic
{
	class Entity
	{
	public:
		bool SetHealth(int health); // Returns true if Health is set to below zero value (Death)
		bool SetDamage(int damage);	// Returns true if MaxHealth is set to below zero value (Also death)
		bool SetMaxHealth(int maxHealth); // Returns true if Damage is set to below zero value (Exhaustion and eventual death)
		bool SetSpeed(int speed);
		bool SetSize(int size);

		int GetHealth();
		int GetMaxHealth();
		int GetDamage();
		int GetSpeed();
		int GetSize();

	protected:
		int _maxHealth;
		int _health;
		int _damage;
		int _speed;
		int _size;

	private:
	};
}
#endif // !LMD_GAMELOGIC_ENTITY