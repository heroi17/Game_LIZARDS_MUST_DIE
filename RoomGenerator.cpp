#include "RoomGenerator.h"

#include <random>
#include <vector>

#include "Item.h"
#include "PowerupItem.h"
#include "ConsumableItem.h"
#include "InformationItem.h"
#include "Entity.h"
#include "Lizard.h"

using namespace GameLogic;


GameLogic::RoomGenerator::RoomGenerator(Map* map)
{
    _map = map;
}

Room* GameLogic::RoomGenerator::GetRandomRoomPreset(std::pair<size_t, size_t> coordinates) 
{
    int randomRoomStructureId = rand() % 3;

    switch (randomRoomStructureId)
    {
        case 0: // a room without enemies
        {
            std::vector<Entity*> enemies = {};
            Item* item = GetRandomItemPreset();
            return new Room(enemies, item);
        }

        case 1: // a room with lizards
        {
            std::vector<Entity*> enemies = {};
            for (int i = 0; i < 5; i++)
            {
                Entity* lizard = new Lizard(RegularWarrior);
                enemies.push_back(lizard);
            }
            Item* item = GetRandomItemPreset();
            return new Room(enemies, item);

        }

        case 2: // a room with the boss
        {
            if (isLeaderSpawned)
            {
                return GetRandomRoomPreset(coordinates); // sturtion recurtion if leader location is already spawned
            }
            std::vector<Entity*> enemies = {};

            Entity* lizard = new Lizard(Leader);
            enemies.push_back(lizard);

            Item* item = GetRandomItemPreset();

            isLeaderSpawned = true;
            _map->SetLeaderLocation(coordinates);

            return new Room(enemies, item);

        }
        default: // a room without anything ( 0 in 100 percent chance of appearing )
        {
            return new Room();
        }
    }
    return nullptr;
}

Item* GameLogic::RoomGenerator::GetRandomItemPreset()
{
    int k = 6;
    int randomItemId = rand() % k;

    switch (randomItemId)
    {
        case 0:
        {
            Item* item = new ConsumableItem("Heal 30%", "You are healed by 30% of your maximum HP", HealingItem_30);
            return item;
        }

        case 1:
        {
            Item* item = new ConsumableItem("Heal 50%", "You are healed by 50% of your maximum HP", HealingItem_50);
            return item;
        }

        case 2:
        {
            Item* item = new ConsumableItem("Heal 100%", "You are fully healed ", HealingItem_100);
            return item;
        }

        case 3:
        {
            Item* item = new InformationItem("Boss location", "You aptained an information about boss location", LeaderLocation, _map);
            return item;
        }

        case 4:
        {
            Item* item = new PowerupItem("Damage up", "Your damage is incresed", DamageBoost);
            return item;
        }

        case 5:
        {
            Item* item = new PowerupItem("HP up", "Your max heath is incresed", MaxHealthBoost);
            return item;
        }

    }
}

Lizard* GameLogic::RoomGenerator::GetRandomLizardPreset()
{
    return nullptr;
}

bool GameLogic::RoomGenerator::isLeaderSpawned = false;

