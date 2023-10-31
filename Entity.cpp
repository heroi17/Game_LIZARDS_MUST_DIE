#include "Entity.h"

bool GameLogic::Entity::SetHealth(int amount)
{
    _health = amount;
    
    if (_health < 0)
    {
        return true;
    }
    return false;
}

bool GameLogic::Entity::SetDamage(int amount)
{
    _damage = amount;

    if (_damage < 0)
    {
        return true;
    }
    return false;
}

bool GameLogic::Entity::SetMaxHealth(int amount)
{
    _maxHealth = amount;

    if (_maxHealth < 0)
    {
        return true;
    }
    return false;
}

bool GameLogic::Entity::SetSpeed(int speed)
{
    _speed = speed;
    return true;
}

bool GameLogic::Entity::SetSize(int size)
{
    _size = size;
    return true;
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

int GameLogic::Entity::GetSpeed()
{
    return _speed;
}

int GameLogic::Entity::GetSize()
{
    return _size;
}
