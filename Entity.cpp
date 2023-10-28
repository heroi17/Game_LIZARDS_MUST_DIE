#include "Entity.h"

bool GameLogic::Entity::SetHealth(int amount)
{
    _health = _health + amount;
    
    if (_health < 0)
    {
        return true;
    }
    return false;
}

bool GameLogic::Entity::SetDamage(int amount)
{
    _damage = _damage + amount;

    if (_damage < 0)
    {
        return true;
    }
    return false;
}

bool GameLogic::Entity::SetMaxHealth(int amount)
{
    _maxHealth = _maxHealth + amount;

    if (_maxHealth < 0)
    {
        return true;
    }
    return false;
}

int GameLogic::Entity::GetHealth()
{
    return _health;
}

int GameLogic::Entity::GetMaxHealth()
{
    return _maxHealth;
}

int GameLogic::Entity::GetDamage()
{
    return _damage;
}
