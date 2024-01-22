#include <windows.h>
#include "testinput.h"
#include "first_test_PO.h"
#include "test_Game_engine.h"

#include "Map.h"
#include "Controller.h"
#include "PowerupItem.h"
#include "InformationItem.h"
#include "ConsumableItem.h"

void MapFillingTest();
void ItemEffectTest();

int main() {
    test1GE();
    //int k = testinput();
    //ItemEffectTest();
    //MapFillingTest();
    return 0;
}















void MapFillingTest()
{
    int width = 5; int height = 5;
    GameLogic::Map map(width, height);
    for (int i = 1; i <= width; i++)
    {
        for (int j = 1; j <= height; j++)
        {
            GameLogic::Room* room = map.GetRoom(i, j);
            std::cout << '(' << i << ',' << j << ')' << endl;
            std::cout << "Item : " << room->GetRewardItem()->GetName() << endl;
            std::cout << "Enemies : [";
            for (int k = 0; k < room->GetEnemies().size(); k++)
            {
                std::cout << room->GetEnemies()[k]->GetMaxHealth() << ' ' << room->GetEnemies()[k]->GetDamage() << ' ';
            }
            std::cout << ']' << endl;
        }
    }
}

void ItemEffectTest()
{
    GameLogic::Player* player = new GameLogic::Player();
    GameLogic::Map map(5, 5);

    GameLogic::Item* DgmUp = new GameLogic::PowerupItem("DMG Up", "Damage is increesed", GameLogic::PowerupItemType::DamageBoost);
    GameLogic::Item* MaxHealthUP = new GameLogic::PowerupItem("HP up", "HP is increesed", GameLogic::PowerupItemType::MaxHealthBoost);
    GameLogic::Item* HealthUp = new GameLogic::ConsumableItem("Healed by 50 %", "you've been healed by 50 %", GameLogic::ConsumableItemType::HealingItem_50);
    GameLogic::Item* Information = new GameLogic::InformationItem("Leader Location", "You know where leader is located", GameLogic::InformationItemType::LeaderLocation, &map);

    player->SetHealth(player->GetHealth() / 3); // Damaging player to see if healing is working right

    std::cout << "Max health: " << player->GetMaxHealth() << "\nHealth: " << player->GetHealth() << "\nDamage :" << player->GetDamage() << '\n' << std::endl;
    
    DgmUp->ApplyEffect(player);
    std::cout << "Max health: " << player->GetMaxHealth() << "\nHealth: " << player->GetHealth() << "\nDamage :" << player->GetDamage() << '\n' << std::endl;

    MaxHealthUP->ApplyEffect(player);
    std::cout << "Max health: " << player->GetMaxHealth() << "\nHealth: " << player->GetHealth() << "\nDamage :" << player->GetDamage() << '\n' << std::endl;

    HealthUp->ApplyEffect(player);
    std::cout << "Max health: " << player->GetMaxHealth() << "\nHealth: " << player->GetHealth() << "\nDamage :" << player->GetDamage() << '\n' << std::endl;

    Information->ApplyEffect(player);

}