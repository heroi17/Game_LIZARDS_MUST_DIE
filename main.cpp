#include <windows.h>

#include "first_test_PO.h"
#include "Map.h"
#include "Controller.h"

void MapFillingText();

int main() {
    //test1();

    int width = 5; int height = 5;
    GameLogic::Map map(width, height);
    map.GetRoom(1, 1)->Show();

    return 0;
}

void MapFillingText()
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

